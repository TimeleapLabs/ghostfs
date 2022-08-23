
#include <errno.h>
#include <fmt/format.h>
#include <fuse_lowlevel.h>
#include <ghostfs/auth.h>
#include <ghostfs/fs.h>
#include <ghostfs/wss.h>
#include <sys/xattr.h>

// Cap'n'Proto

#include <auth.capnp.h>
#include <auth.response.capnp.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <create.capnp.h>
#include <create.response.capnp.h>
#include <getattr.capnp.h>
#include <getattr.response.capnp.h>
#include <lookup.capnp.h>
#include <lookup.response.capnp.h>
#include <mkdir.capnp.h>
#include <mkdir.response.capnp.h>
#include <mknod.capnp.h>
#include <mknod.response.capnp.h>
#include <open.capnp.h>
#include <open.response.capnp.h>
#include <read.capnp.h>
#include <read.response.capnp.h>
#include <readdir.capnp.h>
#include <readdir.response.capnp.h>
#include <release.capnp.h>
#include <release.response.capnp.h>
#include <rename.capnp.h>
#include <rename.response.capnp.h>
#include <rmdir.capnp.h>
#include <rmdir.response.capnp.h>
#include <setattr.capnp.h>
#include <setattr.response.capnp.h>
#include <setxattr.capnp.h>
#include <setxattr.response.capnp.h>
#include <token.capnp.h>
#include <token.response.capnp.h>
#include <unlink.capnp.h>
#include <unlink.response.capnp.h>
#include <write.capnp.h>
#include <write.response.capnp.h>

#include <filesystem>
#include <iostream>

using namespace wsserver;

WSServer::WSServer(int _port, int _auth_port, std::string _host, std::string _root,
                   std::string _suffix)
    : port(std::move(_port)),
      auth_port(std::move(_auth_port)),
      host(std::move(_host)),
      root(std::move(_root)),
      suffix(std::move(_suffix)) {}

int WSServer::start() {
  if (root.length() > 0) {
    if (!std::filesystem::is_directory(root)) {
      std::cout << "ERROR: directory " << '"' << root << '"' << " does not exist." << std::endl;
      return 1;
    };
  }
  // Start the server on port
  ix::WebSocketServer server(port, host);
  ix::WebSocketServer auth_server(auth_port);

  std::cout << "Starting the server on " << host << ":" << port << "..." << std::endl;
  std::cout << "Starting the auth server on port " << auth_port << "..." << std::endl;

  // Setup a callback to be fired (in a background thread, watch out for race conditions !)
  // when a message or an event (open, close, error) is received
  server.setOnClientMessageCallback(
      [this](std::shared_ptr<ix::ConnectionState> connectionState, ix::WebSocket& webSocket,
             const ix::WebSocketMessagePtr& msg) { onMessage(connectionState, webSocket, msg); });
  auth_server.setOnClientMessageCallback(
      [this](std::shared_ptr<ix::ConnectionState> connectionState, ix::WebSocket& webSocket,
             const ix::WebSocketMessagePtr& msg) {
        onAuthMessage(connectionState, webSocket, msg);
      });

  // auto res = server.listen();
  /*
   if (!res.first) {
     // Error handling
     return 1;
   } */

  server.listen();
  auth_server.listen();

  // Per message deflate connection is enabled by default. It can be disabled
  // which might be helpful when running on low power devices such as a Rasbery Pi
  server.disablePerMessageDeflate();
  auth_server.disablePerMessageDeflate();

  // Run the server in the background. Server can be stoped by calling server.stop()
  server.start();
  auth_server.start();

  // Block until server.stop() is called.
  server.wait();
  auth_server.stop();

  return 0;
}

template <class T> std::string send_message(T& response, ::capnp::MallocMessageBuilder& message,
                                            int res, int err, ix::WebSocket& webSocket,
                                            Ops opcode) {
  response.setRes(res);
  response.setErrno(err);

  const auto response_data = capnp::messageToFlatArray(message);
  const auto bytes = response_data.asBytes();
  std::string response_payload(bytes.begin(), bytes.end());

  webSocket.send((char)opcode + response_payload, true);

  return response_payload;
}

template <class T> std::string send_message(T& response, ::capnp::MallocMessageBuilder& message,
                                            int res, ix::WebSocket& webSocket, Ops opcode) {
  response.setRes(res);

  const auto response_data = capnp::messageToFlatArray(message);
  const auto bytes = response_data.asBytes();
  std::string response_payload(bytes.begin(), bytes.end());

  webSocket.sendBinary((char)opcode + response_payload);

  return response_payload;
}

void WSServer::onAuthMessage(std::shared_ptr<ix::ConnectionState> connectionState,
                             ix::WebSocket& webSocket, const ix::WebSocketMessagePtr& msg) {
  (void)connectionState;
  if (msg->type == ix::WebSocketMessageType::Message) {
    const kj::ArrayPtr<const capnp::word> view(
        reinterpret_cast<const capnp::word*>(&(*std::begin(msg->str))),
        reinterpret_cast<const capnp::word*>(&(*std::end(msg->str))));

    capnp::FlatArrayMessageReader data(view);
    TokenRequest::Reader token_request = data.getRoot<TokenRequest>();

    std::string user = token_request.getUser();
    std::string token = token_request.getToken();
    int64_t retries = token_request.getRetries();

    std::string added_token = add_token(user, token, retries);

    ::capnp::MallocMessageBuilder message;
    TokenResponse::Builder token_response = message.initRoot<TokenResponse>();

    token_response.setToken(added_token);

    const auto response_data = capnp::messageToFlatArray(message);
    const auto bytes = response_data.asBytes();
    std::string response_payload(bytes.begin(), bytes.end());

    webSocket.sendBinary(response_payload);
  }
}
void WSServer::onMessage(std::shared_ptr<ix::ConnectionState> connectionState,
                         ix::WebSocket& webSocket, const ix::WebSocketMessagePtr& msg) {
  std::cout << "Remote ip: " << connectionState->getRemoteIp() << std::endl;

  if (msg->type == ix::WebSocketMessageType::Open) {
    std::cout << "New connection" << std::endl;

    // // A connection state object is available, and has a default id
    // // You can subclass ConnectionState and pass an alternate factory
    // // to override it. It is useful if you want to store custom
    // // attributes per connection (authenticated bool flag, attributes, etc...)
    std::cout << "id: " << connectionState->getId() << std::endl;

    // // The uri the client did connect to.
    std::cout << "Uri: " << msg->openInfo.uri << std::endl;

    std::cout << "Headers:" << std::endl;
    // for (auto it : msg->openInfo.headers) {
    //   std::cout << "\t" << it.first << ": " << it.second << std::endl;
    // }
  } else if (msg->type == ix::WebSocketMessageType::Message) {
    // For an echo server, we just send back to the client whatever was received by the server
    // All connected clients are available in an std::set. See the broadcast cpp example.
    // Second parameter tells whether we are sending the message in binary or text mode.
    // Here we send it in the same mode as it was received.
    std::cout << "Received: " << msg->str << std::endl;

    // webSocket.send(msg->str, msg->binary);

    const char command = msg->str[0];
    std::string payload = msg->str.substr(1);

    switch (command) {
      case (char)Ops::Auth: {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Auth::Reader auth = data.getRoot<Auth>();

        std::string user = auth.getUser();
        std::string token = auth.getToken();

        bool is_valid = authenticate(token, user, connectionState->getId());

        ::capnp::MallocMessageBuilder message;
        AuthResponse::Builder auth_response = message.initRoot<AuthResponse>();

        auth_response.setSuccess(is_valid);

        const auto response_data = capnp::messageToFlatArray(message);
        const auto bytes = response_data.asBytes();
        std::string response_payload(bytes.begin(), bytes.end());

        webSocket.sendBinary((char)Ops::Auth + response_payload);
        break;
      }

      case (char)Ops::Getattr: {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Getattr::Reader getattr = data.getRoot<Getattr>();

        std::cout << "getattr: Received UUID: " << getattr.getUuid().cStr() << std::endl;

        struct stat attr;

        memset(&attr, 0, sizeof(attr));
        int res = hello_stat(getattr.getIno(), &attr);
        int err = errno;

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
        std::cout << "st_blksize " << attr.st_blksize << " " << attributes.getStBlksize()
                  << std::endl;
        std::cout << "st_blocks " << attr.st_blocks << " " << attributes.getStBlocks() << std::endl;

        std::string response_payload
            = send_message(getattr_response, message, res, err, webSocket, Ops::Getattr);

        std::cout << "getattr_response sent correctly: " << response_payload << std::endl;

        break;
      }

      case (char)Ops::Lookup: {
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

        std::string user_root = normalize_path(root, connectionState->getId(), suffix);
        std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
        std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
        std::filesystem::path file_path = parent_path / std::filesystem::path(name);

        if (!std::filesystem::exists(file_path)) {
          int err = errno;
          std::string response_payload
              = send_message(lookup_response, message, -1, err, webSocket, Ops::Lookup);
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
        int err = errno;

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

        std::string response_payload
            = send_message(lookup_response, message, res, err, webSocket, Ops::Lookup);

        std::cout << "lookup_response sent correctly: " << response_payload << std::endl;

        break;
      }

      case (char)Ops::Readdir: {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Readdir::Reader readdir = data.getRoot<Readdir>();
        uint64_t ino = readdir.getIno();

        std::cout << "readdir: Received UUID: " << readdir.getUuid().cStr() << std::endl;

        // char msg[] = {3, ino};
        // ws->sendBinary(msg);

        ::capnp::MallocMessageBuilder message;
        ReaddirResponse::Builder readdir_response = message.initRoot<ReaddirResponse>();
        readdir_response.setUuid(readdir.getUuid());

        /**
         * Check if authenticated (example).
         * On fail we need to return a fuse error.
         * EACCESS for access denied.
         */
        // TODO
        bool auth = is_authenticated(connectionState->getId());

        if (!auth) {
          send_message(readdir_response, message, EACCES, webSocket, Ops::Readdir);
          return;
        }  // END EXAMPLE

        std::string path;

        // Root
        if (ino == 1) {
          path = normalize_path(root, connectionState->getId(), suffix);
        } else if (ino_to_path.find(ino) != ino_to_path.end()) {
          path = ino_to_path[ino];
        } else {
          std::string response_payload
              = send_message(readdir_response, message, -1, webSocket, Ops::Readdir);

          std::cout << "readdir_response sent error: " << response_payload << std::endl;

          return;
        }

        /**
         * example check access
         * TODO: Add suffix here
         */
        bool access_ok = check_access(root, connectionState->getId(), path);

        if (!access_ok) {
          send_message(readdir_response, message, EACCES, webSocket, Ops::Readdir);
          return;
        }  // END EXAMPLE

        uint64_t length = 2;

        std::filesystem::directory_iterator iter(
            path, std::filesystem::directory_options::skip_permission_denied);

        for (const auto& entry : iter) {
          (void)entry;
          length++;
        }

        ::capnp::List<ReaddirResponse::Entry>::Builder entries
            = readdir_response.initEntries(length);

        entries[0].setName(".");
        entries[0].setIno(ino);
        entries[1].setName("..");
        entries[1].setIno(get_parent_ino(ino, path));

        uint64_t index = 2;

        // TODO: Find out how we can reuse the iterator from previous step
        iter = std::filesystem::directory_iterator(
            path, std::filesystem::directory_options::skip_permission_denied);

        for (const auto& entry : iter) {
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

        std::string response_payload
            = send_message(readdir_response, message, 0, webSocket, Ops::Readdir);

        std::cout << "readdir_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case (char)Ops::Open: {
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
          std::string response_payload
              = send_message(open_response, message, -1, webSocket, Ops::Open);

          std::cout << "readdir_response sent error: " << response_payload << std::endl;
          return;
        }

        open_response.setIno(open.getIno());

        Open::FuseFileInfo::Reader fi = open.getFi();

        int64_t fh = ::open(ino_to_path[open.getIno()].c_str(), fi.getFlags());

        if (fh == -1) {
          int err = errno;

          std::string response_payload
              = send_message(open_response, message, fh, err, webSocket, Ops::Open);

          return;
        }

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

        std::string response_payload
            = send_message(open_response, message, 0, webSocket, Ops::Open);

        std::cout << "open_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case (char)Ops::Read: {
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
          std::string response_payload
              = send_message(read_response, message, -1, webSocket, Ops::Read);

          std::cout << "read_response sent error: " << response_payload << std::endl;
        }

        size_t size = read.getSize();
        off_t off = read.getOff();

        char buf[size];

        Read::FuseFileInfo::Reader fi = read.getFi();

        ::lseek(fi.getFh(), off, SEEK_SET);
        ::read(fi.getFh(), &buf, size);

        int err = errno;

        kj::ArrayPtr<kj::byte> buf_ptr = kj::arrayPtr((kj::byte*)buf, size);
        capnp::Data::Reader buf_reader(buf_ptr);

        read_response.setBuf(buf_reader);

        std::string response_payload
            = send_message(read_response, message, 0, err, webSocket, Ops::Read);

        std::cout << "read_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case (char)Ops::Setattr: {
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
              = send_message(setattr_response, message, -1, webSocket, Ops::Setattr);

          std::cout << "setattr_response sent error: " << response_payload << std::endl;

          return;
        }

        int res;
        int err;

        std::string file_path = ino_to_path[ino];

        Setattr::Attr::Reader attr = setattr.getAttr();
        Setattr::Attr::TimeSpec::Reader stAtime = attr.getStAtime();
        Setattr::Attr::TimeSpec::Reader stMtime = attr.getStMtime();

        struct timespec a_time = {.tv_sec = stAtime.getTvSec(), .tv_nsec = stAtime.getTvNSec()};
        struct timespec m_time = {.tv_sec = stMtime.getTvSec(), .tv_nsec = stMtime.getTvNSec()};

        uint64_t to_set = setattr.getToSet();

        if (to_set & FUSE_SET_ATTR_MODE) {
          res = chmod(file_path.c_str(), attr.getStMode());
          if (res == -1) {
            err = errno;
            std::string response_payload
                = send_message(setattr_response, message, res, err, webSocket, Ops::Setattr);

            std::cout << "setattr_response sent error: " << response_payload << std::endl;

            return;
          }
        }

        if (to_set & (FUSE_SET_ATTR_UID | FUSE_SET_ATTR_GID)) {
          uid_t uid = (to_set & FUSE_SET_ATTR_UID) ? attr.getStUid() : (uid_t)-1;
          gid_t gid = (to_set & FUSE_SET_ATTR_GID) ? attr.getStGid() : (gid_t)-1;

          res = lchown(file_path.c_str(), uid, gid);
          if (res == -1) {
            err = errno;
            std::string response_payload
                = send_message(setattr_response, message, res, err, webSocket, Ops::Setattr);

            std::cout << "setattr_response sent error: " << response_payload << std::endl;
            return;
          }
        }

        if (to_set & FUSE_SET_ATTR_SIZE) {
          res = truncate(file_path.c_str(), attr.getStSize());
          if (res == -1) {
            err = errno;
            std::string response_payload
                = send_message(setattr_response, message, res, err, webSocket, Ops::Setattr);

            std::cout << "setattr_response sent error: " << response_payload << std::endl;
            return;
          }
        }

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

          res = utimensat(AT_FDCWD, file_path.c_str(), tv, 0);

          if (res == -1) {
            err = errno;
            std::string response_payload = send_message(setattr_response, message, res, err, webSocket, Ops::Setattr);

            std::cout << "setattr_response sent error: " << response_payload << std::endl;
            return;
          }
        }

        setattr_response.setIno(ino);
        
        std::string response_payload = send_message(setattr_response, message, 0, webSocket, Ops::Setattr);

        std::cout << "setattr_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case (char)Ops::Write: {
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

        capnp::Data::Reader buf_reader = write.getBuf();
        const auto chars = buf_reader.asChars();
        const char *buf = chars.begin();

        ::lseek(fi.getFh(), write.getOff(), SEEK_SET);
        size_t written = ::write(fi.getFh(), buf, write.getSize());
        
        int err = errno;

        write_response.setIno(write.getIno());
        write_response.setWritten(written);

        std::string response_payload = send_message(write_response, message, 0, err, webSocket, Ops::Write);

        std::cout << "write_response sent correctly: " << response_payload << std::endl;

        break;
      }
      #ifdef __APPLE__
      case (char)Ops::Setxattr: {
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
            int err = errno;
            std::string response_payload = send_message(setxattr_response, message, res, err, webSocket, Ops::Setxattr);

            std::cout << "setxattr_response sent error: " << response_payload << std::endl;
            return;
        }

        setxattr_response.setIno(ino);

        std::string response_payload = send_message(setxattr_response, message, res, webSocket, Ops::Setxattr);

        std::cout << "setxattr_response sent correctly: " << response_payload << std::endl;

        break;
      }
      #endif
      case (char)Ops::Create: {
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

        std::string user_root = normalize_path(root, connectionState->getId(), suffix);
        std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
        std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
        std::filesystem::path file_path = parent_path / create.getName();

        std::cout << "create: open file path: " << file_path.c_str() << std::endl;
        std::cout << "create: flags: " << fi.getFlags() << std::endl;

        int res = ::creat(file_path.c_str(), create.getMode());

        if (res == -1) {
            int err = errno;

            std::cout << "create: open errno: " << err << std::endl;

            std::string response_payload = send_message(create_response, message, res, err, webSocket, Ops::Create);

            std::cout << "create_response sent error: " << response_payload << std::endl;
            return;
        }

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

        res = hello_stat(file_ino, &attr);
        int err = errno;

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
        
        std::string response_payload = send_message(create_response, message, res, err, webSocket, Ops::Create);

        std::cout << "create_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case (char)Ops::Mknod: {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Mknod::Reader mknod = data.getRoot<Mknod>();

        std::cout << "mknod: Received UUID: " << mknod.getUuid().cStr() << std::endl;

        ::capnp::MallocMessageBuilder message;
        MknodResponse::Builder mknod_response = message.initRoot<MknodResponse>();

        mknod_response.setUuid(mknod.getUuid());

        uint64_t parent = mknod.getParent();

        std::string user_root = normalize_path(root, connectionState->getId(), suffix);
        std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
        std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
        std::filesystem::path file_path = parent_path / mknod.getName();

        uint64_t file_ino;

        file_ino = ++current_ino;
        ino_to_path[file_ino] = file_path;
        path_to_ino[file_path] = file_ino;

        int res = ::mknod(file_path.c_str(), mknod.getMode(), mknod.getRdev());

        if (res == -1) {
          ino_to_path.erase(file_ino);
          path_to_ino.erase(file_path);
          int err = errno;

          std::string response_payload = send_message(mknod_response, message, res, err, webSocket, Ops::Mknod);

          std::cout << "mknod_response sent error: " << response_payload << std::endl;
          return;
        } else {
          mknod_response.setIno(file_ino);

          struct stat attr;
          memset(&attr, 0, sizeof(attr));

          //e.attr_timeout = 1.0;
          //e.entry_timeout = 1.0;

          hello_stat(file_ino, &attr);
          
          MknodResponse::Attr::Builder attributes = mknod_response.initAttr();

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
        
        std::string response_payload = send_message(mknod_response, message, res, webSocket, Ops::Mknod);

        std::cout << "mknod_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case (char)Ops::Mkdir: {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Mkdir::Reader mkdir = data.getRoot<Mkdir>();

        std::cout << "mkdir: Received UUID: " << mkdir.getUuid().cStr() << std::endl;

        ::capnp::MallocMessageBuilder message;
        MkdirResponse::Builder mkdir_response = message.initRoot<MkdirResponse>();

        mkdir_response.setUuid(mkdir.getUuid());

        uint64_t parent = mkdir.getParent();

        std::string user_root = normalize_path(root, connectionState->getId(), suffix);
        std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
        std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
        std::filesystem::path file_path = parent_path / mkdir.getName();

        int res = ::mkdir(file_path.c_str(), mkdir.getMode());

        if (res == -1) {
          int err = errno;
          std::string response_payload = send_message(mkdir_response, message, res, err, webSocket, Ops::Mkdir);

          std::cout << "mkdir_response sent error: " << response_payload << std::endl;
          return;
        }
        else {
          struct stat attr;
          memset(&attr, 0, sizeof(attr));

          uint64_t file_ino;

          file_ino = ++current_ino;
          ino_to_path[file_ino] = file_path;
          path_to_ino[file_path] = file_ino;

          //e.attr_timeout = 1.0;
          //e.entry_timeout = 1.0;
          
          mkdir_response.setIno(file_ino);

          hello_stat(file_ino, &attr);

          MkdirResponse::Attr::Builder attributes = mkdir_response.initAttr();

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
        
        std::string response_payload = send_message(mkdir_response, message, res, webSocket, Ops::Mknod);

        std::cout << "mkdir_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case (char)Ops::Unlink: {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Unlink::Reader unlink = data.getRoot<Unlink>();

        std::cout << "unlink: Received UUID: " << unlink.getUuid().cStr() << std::endl;

        ::capnp::MallocMessageBuilder message;
        UnlinkResponse::Builder unlink_response = message.initRoot<UnlinkResponse>();

        unlink_response.setUuid(unlink.getUuid());

        uint64_t parent = unlink.getParent();
        std::string name = unlink.getName();

        std::string user_root = normalize_path(root, connectionState->getId(), suffix);
        std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
        std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
        std::filesystem::path file_path = parent_path / std::filesystem::path(name);

        int res = ::unlink(file_path.c_str());
        int err = errno;
        
        std::string response_payload = send_message(unlink_response, message, res, err, webSocket, Ops::Unlink);
        std::cout << "unlink_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case (char)Ops::Rmdir: {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Rmdir::Reader rmdir = data.getRoot<Rmdir>();

        std::cout << "rmdir: Received UUID: " << rmdir.getUuid().cStr() << std::endl;

        ::capnp::MallocMessageBuilder message;
        RmdirResponse::Builder rmdir_response = message.initRoot<RmdirResponse>();

        rmdir_response.setUuid(rmdir.getUuid());

        uint64_t parent = rmdir.getParent();
        std::string name = rmdir.getName();

        std::cout << "RMDIR name: " << name << std::endl;

        std::string user_root = normalize_path(root, connectionState->getId(), suffix);
        std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
        std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
        std::filesystem::path file_path = parent_path / std::filesystem::path(name);

        std::cout << "RMDIR file_path: " << file_path.c_str() << std::endl;

        int res = ::rmdir(file_path.c_str());
        int err = errno;
        
        std::string response_payload = send_message(rmdir_response, message, res, err, webSocket, Ops::Rmdir);
        std::cout << "rmdir_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case (char)Ops::Rename: {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Rename::Reader rename = data.getRoot<Rename>();

        std::cout << "rename: Received UUID: " << rename.getUuid().cStr() << std::endl;

        ::capnp::MallocMessageBuilder message;
        RenameResponse::Builder rename_response = message.initRoot<RenameResponse>();

        rename_response.setUuid(rename.getUuid());

        uint64_t parent = rename.getParent();
        std::string name = rename.getName();
        uint64_t newparent = rename.getNewparent();
        std::string newname = rename.getNewname();

        std::string user_root = normalize_path(root, connectionState->getId(), suffix);

        std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
        std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
        std::filesystem::path file_path = parent_path / std::filesystem::path(name);

        std::string newparent_path_name = newparent == 1 ? user_root : ino_to_path[newparent];
        std::filesystem::path newparent_path = std::filesystem::path(newparent_path_name);
        std::filesystem::path newfile_path = newparent_path / std::filesystem::path(newname);

        // use rename
        int res = ::rename(file_path.c_str(), newfile_path.c_str());
        int err = errno;

        std::string response_payload = send_message(rename_response, message, res, err, webSocket, Ops::Rmdir);
        std::cout << "rename_response sent correctly: " << response_payload << std::endl;

        break;
      }
      case (char)Ops::Release: {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Release::Reader release = data.getRoot<Release>();
        Release::FuseFileInfo::Reader fi = release.getFi();

        int res = ::close(fi.getFh());
        int err = errno;

        std::cout << "release: Received UUID: " << release.getUuid().cStr() << std::endl;

        ::capnp::MallocMessageBuilder message;
        ReleaseResponse::Builder release_response = message.initRoot<ReleaseResponse>();

        release_response.setUuid(release.getUuid());
        std::string response_payload = send_message(release_response, message, res, err, webSocket, Ops::Release);

        break;
      }

      default:
        break;
    }
  }
}