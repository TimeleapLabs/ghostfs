
#include <fmt/format.h>
#include <ghostfs/fs.h>
#include <ghostfs/wss.h>

// Cap'n'Proto

#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <getattr.capnp.h>
#include <getattr.response.capnp.h>
#include <lookup.capnp.h>
#include <lookup.response.capnp.h>
#include <readdir.capnp.h>
#include <readdir.response.capnp.h>

#include <filesystem>
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

        std::cout << "getattr: Received UUID: " << getattr.getUuid().cStr() << std::endl;

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

        std::cout << "st_dev " << attr.st_dev << " " << attributes.getStDev() << std::endl;
        std::cout << "st_ino " << attr.st_ino << " " << attributes.getStIno() << std::endl;
        std::cout << "st_mode " << attr.st_mode << " " << attributes.getStMode() << std::endl;
        std::cout << "st_nlink " << attr.st_nlink << " " << attributes.getStNlink() << std::endl;
        std::cout << "st_uid " << attr.st_uid << " " << attributes.getStUid() << std::endl;
        std::cout << "st_gid " << attr.st_gid << " " << attributes.getStGid() << std::endl;
        std::cout << "st_rdev " << attr.st_rdev << " " << attributes.getStRdev() << std::endl;
        std::cout << "st_size " << attr.st_size << " " << attributes.getStSize() << std::endl;
        std::cout << "st_atime " << attr.st_atime << " " << attributes.getStAtime() << std::endl;
        std::cout << "st_mtime " << attr.st_mtime << " " << attributes.getStMtime() << std::endl;
        std::cout << "st_ctime " << attr.st_ctime << " " << attributes.getStCtime() << std::endl;
        std::cout << "st_blksize " << attr.st_blksize << " " << attributes.getStBlksize() << std::endl;
        std::cout << "st_blocks " << attr.st_blocks << " " << attributes.getStBlocks() << std::endl;

        const auto response_data = capnp::messageToFlatArray(message);
        const auto bytes = response_data.asBytes();
        std::string response_payload(bytes.begin(), bytes.end());

        webSocket.sendBinary("1" + response_payload);

        std::cout << "getattr_response sent correctly: " << response_payload << std::endl;

        break;
      }

      case '2': {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Lookup::Reader lookup = data.getRoot<Lookup>();

        std::cout << "lookup: Received UUID: " << lookup.getUuid().cStr() << std::endl;

        // char msg[] = {2, parent, *name};
        // ws->sendBinary(msg);

        ::capnp::MallocMessageBuilder message;
        LookupResponse::Builder lookup_response = message.initRoot<LookupResponse>();

        lookup_response.setUuid(lookup.getUuid());

        uint64_t parent = lookup.getParent();
        std::string name = lookup.getName();

        std::string parent_path_name = parent == 1 ? ROOT : ino_to_path[parent];
        std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
        std::filesystem::path file_path = parent_path / std::filesystem::path(name);

        if (!std::filesystem::exists(file_path)) {
          lookup_response.setRes(-1);
        } else {
          uint64_t ino = path_to_ino[file_path];
          lookup_response.setIno(ino);

          //e.attr_timeout = 1.0;
         // e.entry_timeout = 1.0;

          struct stat attr;

          memset(&attr, 0, sizeof(attr));

          int res = hello_stat(ino, &attr);

          LookupResponse::Attr::Builder attributes = lookup_response.initAttr();

          lookup_response.setRes(res);

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
        }

        const auto response_data = capnp::messageToFlatArray(message);
        const auto bytes = response_data.asBytes();
        std::string response_payload(bytes.begin(), bytes.end());

        webSocket.sendBinary("2" + response_payload);

        std::cout << "lookup_response sent correctly: " << response_payload << std::endl;

        break;
      }

      case '3': {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Readdir::Reader readdir = data.getRoot<Readdir>();
        uint64_t ino = readdir.getIno();

        std::cout << "readdir: Received UUID: " << readdir.getUuid().cStr() << std::endl;

        struct stat stbuf;

        // char msg[] = {3, ino};
        // ws->sendBinary(msg);

        std::string path;

        ::capnp::MallocMessageBuilder message;
        ReaddirResponse::Builder readdir_response = message.initRoot<ReaddirResponse>();
        readdir_response.setUuid(readdir.getUuid());

        // Root
        if (ino == 1) {
          path = ROOT;
        } else if (ino_to_path.find(ino) != ino_to_path.end()) {
          path = ino_to_path[ino];
        } else {
          readdir_response.setRes(-1);

          const auto response_data = capnp::messageToFlatArray(message);
          const auto bytes = response_data.asBytes();
          std::string response_payload(bytes.begin(), bytes.end());

          webSocket.sendBinary("3" + response_payload);

          std::cout << "readdir_response sent error: " << response_payload << std::endl;

          return;
        }

        uint64_t length = 0;

        /**
         * TODO: Find a better way
         */
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
          length++;
        }

        ::capnp::List<ReaddirResponse::Entry>::Builder entries
            = readdir_response.initEntries(length);

        uint64_t index = 0;

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

          entries[index].setName(file_name);
          entries[index].setIno(file_ino);

          index++;
        }

        readdir_response.setRes(0);

        const auto response_data = capnp::messageToFlatArray(message);
        const auto bytes = response_data.asBytes();
        std::string response_payload(bytes.begin(), bytes.end());

        webSocket.sendBinary("3" + response_payload);

        std::cout << "readdir_response sent correctly: " << response_payload<< std::endl;

        break;
      }

      default:
        break;
    }
  }
}