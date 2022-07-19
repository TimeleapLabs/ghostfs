
#include <fmt/format.h>
#include <fuse_lowlevel.h>
#include <ghostfs/fs.h>
#include <ghostfs/wss.h>
#include <sys/xattr.h>

// Cap'n'Proto

#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <create.capnp.h>
#include <create.response.capnp.h>
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
#include <setxattr.capnp.h>
#include <setxattr.response.capnp.h>
#include <write.capnp.h>
#include <write.response.capnp.h>

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

template <class T> std::string send_message(T& response, ::capnp::MallocMessageBuilder& message,
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

        std::string response_payload = send_message(getattr_response, message, res, webSocket, "1");

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

        std::cout << "LOOKUP name: " << name << std::endl;

        std::string parent_path_name = parent == 1 ? ROOT : ino_to_path[parent];
        std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
        std::filesystem::path file_path = parent_path / std::filesystem::path(name);

        std::cout << "LOOKUP filepath: " << file_path << std::endl;

        if (!std::filesystem::exists(file_path)) {
          std::string response_payload = send_message(lookup_response, message, -1, webSocket, "2");
          std::cout << "lookup_response sent error: " << response_payload << std::endl;
          return;
        }

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

        std::string response_payload = send_message(lookup_response, message, res, webSocket, "2");

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
          std::string response_payload
              = send_message(readdir_response, message, -1, webSocket, "3");

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

        std::string response_payload = send_message(readdir_response, message, 0, webSocket, "3");

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
          std::string response_payload = send_message(open_response, message, -1, webSocket, "4");

          std::cout << "readdir_response sent error: " << response_payload << std::endl;
          return;
        }

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

        std::string response_payload = send_message(open_response, message, 0, webSocket, "4");

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
          std::string response_payload = send_message(read_response, message, -1, webSocket, "5");

          std::cout << "read_response sent error: " << response_payload << std::endl;
        }

        size_t size = read.getSize();
        off_t off = read.getOff();

        char buf[size];

        Read::FuseFileInfo::Reader fi = read.getFi();

        ::lseek(fi.getFh(), off, SEEK_SET);
        ::read(fi.getFh(), &buf, size);

        kj::ArrayPtr<kj::byte> buf_ptr = kj::arrayPtr((unsigned char*)buf, size);
        capnp::Data::Reader buf_reader(buf_ptr);

        read_response.setBuf(buf_reader);

        std::string response_payload = send_message(read_response, message, 0, webSocket, "5");

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
          std::string response_payload
              = send_message(setattr_response, message, -1, webSocket, "6");

          std::cout << "setattr_response sent error: " << response_payload << std::endl;

          return;
        }

        int err;
        std::string file_path = ino_to_path[ino];

        Setattr::Attr::Reader attr = setattr.getAttr();
        Setattr::Attr::TimeSpec::Reader stAtime = attr.getStAtime();
        Setattr::Attr::TimeSpec::Reader stMtime = attr.getStMtime();

        struct timespec a_time = {.tv_sec = stAtime.getTvSec(), .tv_nsec = stAtime.getTvNSec()};
        struct timespec m_time = {.tv_sec = stMtime.getTvSec(), .tv_nsec = stMtime.getTvNSec()};

        uint64_t to_set = setattr.getToSet();

        if (to_set & FUSE_SET_ATTR_MODE) {
          err = chmod(file_path.c_str(), attr.getStMode());
          if (err == -1) {
            std::string response_payload
                = send_message(setattr_response, message, -1, webSocket, "6");

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
                = send_message(setattr_response, message, -1, webSocket, "6");

            std::cout << "setattr_response sent error: " << response_payload << std::endl;
            return;
          }
        }

        if (to_set & FUSE_SET_ATTR_SIZE) {
          err = truncate(file_path.c_str(), attr.getStSize());
          if (err == -1) {
            std::string response_payload
                = send_message(setattr_response, message, -1, webSocket, "6");

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
            tv[0] = a_time;
          }

          if (to_set & FUSE_SET_ATTR_MTIME_NOW) {
            tv[1].tv_nsec = UTIME_NOW;
          } else if (to_set & FUSE_SET_ATTR_MTIME) {  // clang-format off
      // #if defined(__APPLE__)
      //   tv[1] = attr->st_mtimespec;
      // #else
      //   tv[1] = attr->st_mtim;
      // #endif  // clang-format on
            tv[1] = m_time;
          }

          err = utimensat(AT_FDCWD, file_path.c_str(), tv, 0);

          if (err == -1) {
            std::string response_payload = send_message(setattr_response, message, -1, webSocket, "6");

            std::cout << "setattr_response sent error: " << response_payload << std::endl;
            return;
          }
        }

        setattr_response.setIno(ino);
        
        std::string response_payload = send_message(setattr_response, message, 0, webSocket, "6");

        std::cout << "setattr_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case '7': {
        const kj::ArrayPtr<const capnp::word> view(
        reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
        reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Write::Reader write = data.getRoot<Write>();

        std::cout << "write: Received UUID: " << write.getUuid().cStr() << std::endl;

        ::capnp::MallocMessageBuilder message;
        WriteResponse::Builder write_response = message.initRoot<WriteResponse>();

        write_response.setUuid(write.getUuid());

        Write::FuseFileInfo::Reader fi = write.getFi();
        ::lseek(fi.getFh(), write.getOff(), SEEK_SET);
        size_t written = ::write(fi.getFh(), write.getBuf().cStr(), write.getSize());

        write_response.setIno(write.getIno());
        write_response.setWritten(written);

        std::string response_payload = send_message(write_response, message, 0, webSocket, "7");

        std::cout << "write_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case '8': {
        const kj::ArrayPtr<const capnp::word> view(
        reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
        reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Setxattr::Reader _setxattr = data.getRoot<Setxattr>();

        std::cout << "setxattr: Received UUID: " << _setxattr.getUuid().cStr() << std::endl;

        ::capnp::MallocMessageBuilder message;
        SetxattrResponse::Builder setxattr_response = message.initRoot<SetxattrResponse>();

        setxattr_response.setUuid(_setxattr.getUuid());

        uint64_t ino = _setxattr.getIno();

        std::string file_path = ino_to_path[ino];

        int res = setxattr(file_path.c_str(), _setxattr.getName().cStr(), _setxattr.getValue().cStr(), (size_t) _setxattr.getSize(), _setxattr.getPosition(), _setxattr.getFlags());
        if (res == -1) {
            std::string response_payload = send_message(setxattr_response, message, res, webSocket, "7");

            std::cout << "setxattr_response sent error: " << response_payload << std::endl;
            return;
        }

        setxattr_response.setIno(ino);

        std::string response_payload = send_message(setxattr_response, message, res, webSocket, "8");

        std::cout << "setxattr_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case '9': {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Create::Reader create = data.getRoot<Create>();
        Create::FuseFileInfo::Reader fi = create.getFi();

        std::cout << "create: Received UUID: " << create.getUuid().cStr() << std::endl;

        ::capnp::MallocMessageBuilder message;
        CreateResponse::Builder create_response = message.initRoot<CreateResponse>();

        create_response.setUuid(create.getUuid());

        uint64_t parent = create.getParent();

        std::string parent_path_name = parent == 1 ? ROOT : ino_to_path[parent];
        std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
        std::filesystem::path file_path = parent_path / std::filesystem::path(create.getName());

        int res = ::open(file_path.c_str(), (fi.getFlags() | O_CREAT) & ~O_NOFOLLOW, create.getMode());

        if (res == -1) {
            std::string response_payload = send_message(create_response, message, res, webSocket, "9");

            std::cout << "create_response sent error: " << response_payload << std::endl;
            return;
        } else {
          struct stat attr;
          memset(&attr, 0, sizeof(attr));

          uint64_t file_ino;

          file_ino = ++current_ino;
          ino_to_path[file_ino] = file_path;
          path_to_ino[file_path] = file_ino;

          // e.attr_timeout = 1.0;
          // e.entry_timeout = 1.0;

          CreateResponse::FuseFileInfo::Builder fi_response = create_response.initFi();

          fi_response.setCacheReaddir(fi.getCacheReaddir());
          fi_response.setDirectIo(fi.getDirectIo());
          fi_response.setFh(res);
          fi_response.setFlags(fi.getFlags());
          fi_response.setFlush(fi.getFlush());
          fi_response.setKeepCache(fi.getKeepCache());
          fi_response.setLockOwner(fi.getLockOwner());
          fi_response.setNoflush(fi.getNoflush());
          fi_response.setNonseekable(fi.getNonseekable());
          fi_response.setPadding(fi.getPadding());
          fi_response.setPollEvents(fi.getPollEvents());
          fi_response.setWritepage(fi.getWritepage());

          hello_stat(file_ino, &attr);

          create_response.setIno(file_ino);

          CreateResponse::Attr::Builder attributes = create_response.initAttr();

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
        
        std::string response_payload = send_message(create_response, message, res, webSocket, "9");

        std::cout << "create_response sent correctly: " << response_payload << std::endl;

        break;
      }

      default:
        break;
    }
  }
}