
#include <fmt/format.h>
#include <ghostfs/fs.h>
#include <ghostfs/wss.h>

// Cap'n'Proto

#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <getattr.capnp.h>
#include <getattr.response.capnp.h>
#include <readdir.response.capnp.h>
#include <lookup.capnp.h>
#include <readdir.capnp.h>

#include <iostream>

using namespace wsserver;

WSServer::WSServer(int _port) : port(std::move(_port)) {}

void WSServer::start() {
  // Start the server on port
  ix::WebSocketServer server(port);

  std::cout << "Starting the server on port " << port << "..." << std::endl;

  // Setup a callback to be fired (in a background thread, watch out for race conditions !)
  // when a message or an event (open, close, error) is received
  server.setOnClientMessageCallback(
      [this](std::shared_ptr<ix::ConnectionState> connectionState, ix::WebSocket& webSocket,
             const ix::WebSocketMessagePtr& msg) { onMessage(connectionState, webSocket, msg); });

  auto res = server.listen(); /*
   if (!res.first) {
     // Error handling
     return 1;
   } */

  // Per message deflate connection is enabled by default. It can be disabled
  // which might be helpful when running on low power devices such as a Rasbery Pi
  server.disablePerMessageDeflate();

  // Run the server in the background. Server can be stoped by calling server.stop()
  server.start();

  // Block until server.stop() is called.
  server.wait();
}

void WSServer::onMessage(std::shared_ptr<ix::ConnectionState> connectionState,
                         ix::WebSocket& webSocket, const ix::WebSocketMessagePtr& msg) {
  // std::cout << "Remote ip: " << connectionState->getRemoteIp() << std::endl;

  if (msg->type == ix::WebSocketMessageType::Open) {
    // std::cout << "New connection" << std::endl;

    // // A connection state object is available, and has a default id
    // // You can subclass ConnectionState and pass an alternate factory
    // // to override it. It is useful if you want to store custom
    // // attributes per connection (authenticated bool flag, attributes, etc...)
    // std::cout << "id: " << connectionState->getId() << std::endl;

    // // The uri the client did connect to.
    // std::cout << "Uri: " << msg->openInfo.uri << std::endl;

    // std::cout << "Headers:" << std::endl;
    // for (auto it : msg->openInfo.headers) {
    //   std::cout << "\t" << it.first << ": " << it.second << std::endl;
    // }
  } else if (msg->type == ix::WebSocketMessageType::Message) {
    // For an echo server, we just send back to the client whatever was received by the server
    // All connected clients are available in an std::set. See the broadcast cpp example.
    // Second parameter tells whether we are sending the message in binary or text mode.
    // Here we send it in the same mode as it was received.
    // std::cout << "Received: " << msg->str << std::endl;

    // webSocket.send(msg->str, msg->binary);

    const char command = msg->str[0];
    std::string payload = msg->str.substr(1);

    switch (command) {
      case '1': {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Getattr::Reader getattr = data.getRoot<Getattr>();

        // std::cout << "Received UUID: " << getattr.getUuid().cStr() << std::endl;

        struct stat attr;

        memset(&attr, 0, sizeof(attr));
        int res = hello_stat(getattr.getIno(), &attr);

        ::capnp::MallocMessageBuilder message;
        GetattrResponse::Builder getattr_response = message.initRoot<GetattrResponse>();
        GetattrResponse::Attr::Builder attributes = getattr_response.initAttr();

        getattr_response.setUuid(getattr.getUuid());
        getattr_response.setRes(res);

        attributes.setStDev(attr.st_dev);
        attributes.setStIno(attr.st_ino);
        attributes.setStMode(attr.st_mode);
        attributes.setStNlink(attr.st_nlink);
        attributes.setStUid(attr.st_uid);
        attributes.setStGid(attr.st_gid);
        attributes.setStRdev(attr.st_rdev);
        attributes.setStSize(attr.st_size);
        attributes.setStAtime(attr.st_atime);
        attributes.setStMtime(attr.st_mtime);
        attributes.setStCtime(attr.st_ctime);
        attributes.setStBlksize(attr.st_blksize);
        attributes.setStBlocks(attr.st_blocks);

        const auto response_data = capnp::messageToFlatArray(message);
        const auto bytes = response_data.asBytes();
        std::string response_payload(bytes.begin(), bytes.end());

        webSocket.send("1" + response_payload, true);

        break;
      }

      case '3': {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Readdir::Reader readdir = data.getRoot<Readdir>();
        uint64_t ino = readdir.getIno();

        struct stat stbuf;

        // char msg[] = {3, ino};
        // ws->sendBinary(msg);

        std::string path;

        // Root
        if (ino == 1) {
          path = ROOT;
        } else if (ino_to_path.find(ino) != ino_to_path.end()) {
          path = ino_to_path[ino];
        } else {
          ::capnp::MallocMessageBuilder message;
          ReaddirResponse::Builder readdir_response = message.initRoot<ReaddirResponse>();

          readdir_response.setUuid(readdir.getUuid());
          readdir_response.setRes(-1);

          const auto response_data = capnp::messageToFlatArray(message);
          const auto bytes = response_data.asBytes();
          std::string response_payload(bytes.begin(), bytes.end());

          webSocket.send("3" + response_payload, true);

          return;
        }

        struct dirbuf b;

        memset(&b, 0, sizeof(b));
        dirbuf_add(req, &b, ".", 1);
        dirbuf_add(req, &b, "..", 1);

        for (const auto& entry : std::filesystem::directory_iterator(path)) {
          std::string file_path = entry.path();
          std::string file_name = std::filesystem::path(file_path).filename();

          uint64_t file_ino;

          if (path_to_ino.find(file_path) == path_to_ino.end()) {
            file_ino = ++current_ino;
            ino_to_path[file_ino] = file_path;
            path_to_ino[file_path] = file_ino;
          } else {
            file_ino = path_to_ino[file_path];
          }

          // std::cout << "Filename: " << file_name << ", INO: " << file_ino << std::endl;
          dirbuf_add(req, &b, file_name.c_str(), file_ino);
        }

        ::capnp::MallocMessageBuilder message;
        ReaddirResponse::Builder readdir_response = message.initRoot<ReaddirResponse>();
        ReaddirResponse::Dirbuf::Builder _dirbuf = readdir_response.initDirbuf();


        readdir_response.setUuid(readdir.getUuid());
        readdir_response.setRes(0);
        _dirbuf.setP(b.p);
        _dirbuf.setSize(b.size);

        const auto response_data = capnp::messageToFlatArray(message);
        const auto bytes = response_data.asBytes();
        std::string response_payload(bytes.begin(), bytes.end());

        webSocket.send("3" + response_payload, true);

        free(b.p);
      }

      default:
        break;
    }
  }
}