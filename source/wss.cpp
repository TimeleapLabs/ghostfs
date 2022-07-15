
#include <fmt/format.h>
#include <fuse_lowlevel.h>
#include <ghostfs/fs.h>
#include <ghostfs/wss.h>

// Cap'n'Proto

#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <getattr.capnp.h>
#include <getattr.response.capnp.h>
#include <lookup.capnp.h>
#include <lookup.response.capnp.h>
#include <open.capnp.h>
#include <open.response.capnp.h>
#include <read.capnp.h>
#include <read.response.capnp.h>
#include <readdir.capnp.h>
#include <readdir.response.capnp.h>
#include <setattr.capnp.h>
#include <setattr.response.capnp.h>

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

template <class T> std::string send_error(T &response, ::capnp::MallocMessageBuilder &message,
                                          int res, ix::WebSocket& webSocket, std::string opcode) {
  response.setRes(res);

  const auto response_data = capnp::messageToFlatArray(message);
  const auto bytes = response_data.asBytes();
  std::string response_payload(bytes.begin(), bytes.end());

  webSocket.send(opcode + response_payload, true);

  return response_payload;
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

        // std::cout << "st_dev " << attr.st_dev << " " << attributes.getStDev() << std::endl;
        // std::cout << "st_ino " << attr.st_ino << " " << attributes.getStIno() << std::endl;
        // std::cout << "st_mode " << attr.st_mode << " " << attributes.getStMode() << std::endl;
        // std::cout << "st_nlink " << attr.st_nlink << " " << attributes.getStNlink() << std::endl;
        // std::cout << "st_uid " << attr.st_uid << " " << attributes.getStUid() << std::endl;
        // std::cout << "st_gid " << attr.st_gid << " " << attributes.getStGid() << std::endl;
        // std::cout << "st_rdev " << attr.st_rdev << " " << attributes.getStRdev() << std::endl;
        // std::cout << "st_size " << attr.st_size << " " << attributes.getStSize() << std::endl;
        // std::cout << "st_atime " << attr.st_atime << " " << attributes.getStAtime() << std::endl;
        // std::cout << "st_mtime " << attr.st_mtime << " " << attributes.getStMtime() << std::endl;
        // std::cout << "st_ctime " << attr.st_ctime << " " << attributes.getStCtime() << std::endl;
        // std::cout << "st_blksize " << attr.st_blksize << " " << attributes.getStBlksize() <<
        // std::endl; std::cout << "st_blocks " << attr.st_blocks << " " << attributes.getStBlocks()
        // << std::endl;

        const auto response_data = capnp::messageToFlatArray(message);
        const auto bytes = response_data.asBytes();
        std::string response_payload(bytes.begin(), bytes.end());

        webSocket.send("1" + response_payload, true);

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
          uint64_t ino;

          if (path_to_ino.find(file_path) == path_to_ino.end()) {
            ino = ++current_ino;
            ino_to_path[ino] = file_path;
            path_to_ino[file_path] = ino;
          } else {
            ino = path_to_ino[file_path];
          }

          lookup_response.setIno(ino);

          // e.attr_timeout = 1.0;
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

        webSocket.send("2" + response_payload, true);

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

          webSocket.send("3" + response_payload, true);

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

        webSocket.send("3" + response_payload, true);

        std::cout << "readdir_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case '4': {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Open::Reader open = data.getRoot<Open>();

        std::cout << "open: Received UUID: " << open.getUuid().cStr() << std::endl;

        ::capnp::MallocMessageBuilder message;
        OpenResponse::Builder open_response = message.initRoot<OpenResponse>();

        open_response.setUuid(open.getUuid());

        if (ino_to_path.find(open.getIno()) == ino_to_path.end()) {
          // File is unknown
          open_response.setRes(-1);
        } else {
          open_response.setIno(open.getIno());

          Open::FuseFileInfo::Reader fi = open.getFi();

          uint64_t fh = ::open(ino_to_path[open.getIno()].c_str(), fi.getFlags());

          OpenResponse::FuseFileInfo::Builder fi_response = open_response.initFi();

          fi_response.setCacheReaddir(fi.getCacheReaddir());
          fi_response.setDirectIo(fi.getDirectIo());
          fi_response.setFh(fh);
          fi_response.setFlags(fi.getFlags());
          fi_response.setFlush(fi.getFlush());
          fi_response.setKeepCache(fi.getKeepCache());
          fi_response.setLockOwner(fi.getLockOwner());
          fi_response.setNoflush(fi.getNoflush());
          fi_response.setNonseekable(fi.getNonseekable());
          fi_response.setPadding(fi.getPadding());
          fi_response.setPollEvents(fi.getPollEvents());
          fi_response.setWritepage(fi.getWritepage());
        }

        const auto response_data = capnp::messageToFlatArray(message);
        const auto bytes = response_data.asBytes();
        std::string response_payload(bytes.begin(), bytes.end());

        webSocket.send("4" + response_payload, true);

        std::cout << "open_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case '5': {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Read::Reader read = data.getRoot<Read>();

        std::cout << "read: Received UUID: " << read.getUuid().cStr() << std::endl;

        ::capnp::MallocMessageBuilder message;
        ReadResponse::Builder read_response = message.initRoot<ReadResponse>();

        read_response.setUuid(read.getUuid());

        if (ino_to_path.find(read.getIno()) == ino_to_path.end()) {
          // File is unknown
          read_response.setRes(-1);
        } else {
          size_t size = read.getSize();
          off_t off = read.getOff();

          char buf[size];

          Read::FuseFileInfo::Reader fi = read.getFi();

          ::lseek(fi.getFh(), off, SEEK_SET);
          ::read(fi.getFh(), &buf, size);

          kj::ArrayPtr<kj::byte> buf_ptr = kj::arrayPtr((unsigned char*)buf, size);
          capnp::Data::Reader buf_reader(buf_ptr);

          read_response.setBuf(buf_reader);
          read_response.setRes(0);
        }

        const auto response_data = capnp::messageToFlatArray(message);
        const auto bytes = response_data.asBytes();
        std::string response_payload(bytes.begin(), bytes.end());

        webSocket.send("5" + response_payload, true);

        std::cout << "read_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case '6': {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Setattr::Reader setattr = data.getRoot<Setattr>();

        std::cout << "setattr: Received UUID: " << setattr.getUuid().cStr() << std::endl;

        ::capnp::MallocMessageBuilder message;
        SetattrResponse::Builder setattr_response = message.initRoot<SetattrResponse>();

        setattr_response.setUuid(setattr.getUuid());

        uint64_t ino = setattr.getIno();

        if (ino_to_path.find(ino) == ino_to_path.end()) {
          // Parent is unknown
          std::string response_payload = send_error(setattr_response, message, -1, webSocket, "6");

          std::cout << "setattr_response sent error: " << response_payload << std::endl;

          return;
        }

        int err;
        std::string file_path = ino_to_path[ino];

        Setattr::Attr::Reader attr = setattr.getAttr();
        uint64_t to_set = setattr.getToSet();

        if (to_set & FUSE_SET_ATTR_MODE) {
          err = chmod(file_path.c_str(), attr.getStMode());
          if (err == -1) {
            std::string response_payload
                = send_error(setattr_response, message, -1, webSocket, "6");

            std::cout << "setattr_response sent error: " << response_payload << std::endl;

            return;
          }
        }

        if (to_set & (FUSE_SET_ATTR_UID | FUSE_SET_ATTR_GID)) {
          uid_t uid = (to_set & FUSE_SET_ATTR_UID) ? attr.getStUid() : (uid_t)-1;
          gid_t gid = (to_set & FUSE_SET_ATTR_GID) ? attr.getStGid() : (gid_t)-1;

          err = lchown(file_path.c_str(), uid, gid);
          if (err == -1) {
            std::string response_payload
                = send_error(setattr_response, message, -1, webSocket, "6");

            std::cout << "setattr_response sent error: " << response_payload << std::endl;
            return;
          }
        }

        if (to_set & FUSE_SET_ATTR_SIZE) {
          err = truncate(file_path.c_str(), attr.getStSize());
          if (err == -1) {
            std::string response_payload
                = send_error(setattr_response, message, -1, webSocket, "6");

            std::cout << "setattr_response sent error: " << response_payload << std::endl;
            return;
          }
        }

        // todo from here

        if (to_set & (FUSE_SET_ATTR_ATIME | FUSE_SET_ATTR_MTIME)) {
          struct timespec tv[2];

          tv[0].tv_sec = 0;
          tv[1].tv_sec = 0;
          tv[0].tv_nsec = UTIME_OMIT;
          tv[1].tv_nsec = UTIME_OMIT;

          if (to_set & FUSE_SET_ATTR_ATIME_NOW) {
            tv[0].tv_nsec = UTIME_NOW;
          } else if (to_set & FUSE_SET_ATTR_ATIME) {  // clang-format off
      // #if defined(__APPLE__)
      //   tv[0] = attr->st_atimespec;
      // #else
      //   tv[0] = attr->st_atim;
      // #endif  // clang-format on
            tv[0] = attr.getStAtime();
          }

          if (to_set & FUSE_SET_ATTR_MTIME_NOW) {
            tv[1].tv_nsec = UTIME_NOW;
          } else if (to_set & FUSE_SET_ATTR_MTIME) {  // clang-format off
      // #if defined(__APPLE__)
      //   tv[1] = attr->st_mtimespec;
      // #else
      //   tv[1] = attr->st_mtim;
      // #endif  // clang-format on
            tv[1] = attr.getStMtime();
          }

          err = utimensat(AT_FDCWD, file_path.c_str(), tv, 0);

          if (err == -1) {
            std::string response_payload = send_error(setattr_response, message, -1, webSocket, "6");

            std::cout << "setattr_response sent error: " << response_payload << std::endl;
            return;
          }
        }

        SetattrResponse::Attr::Builder attributes = setattr_response.initAttr();

        setattr_response.setRes(0);
        setattr_response.setIno(ino);

        const auto response_data = capnp::messageToFlatArray(message);
        const auto bytes = response_data.asBytes();
        std::string response_payload(bytes.begin(), bytes.end());

        webSocket.send("6" + response_payload, true);

        std::cout << "setattr_response sent correctly: " << response_payload << std::endl;

        break;
      }

      default:
        break;
    }
  }
}