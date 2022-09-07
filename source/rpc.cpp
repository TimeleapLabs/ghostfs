#include <errno.h>
#include <fmt/format.h>
#include <fuse_lowlevel.h>
#include <ghostfs/auth.h>
#include <ghostfs/fs.h>
#include <ghostfs/rpc.h>
#include <sys/xattr.h>
#include <unistd.h>

// Cap'n'Proto
#include <capnp/ez-rpc.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <create.capnp.h>
#include <create.response.capnp.h>
#include <flush.capnp.h>
#include <flush.response.capnp.h>
#include <fsync.capnp.h>
#include <fsync.response.capnp.h>
#include <getattr.capnp.h>
#include <getattr.response.capnp.h>
#include <ghostfs.capnp.h>
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
#include <unlink.capnp.h>
#include <unlink.response.capnp.h>
#include <write.capnp.h>
#include <write.response.capnp.h>

#include <filesystem>
#include <iostream>

class GhostFSImpl final : public GhostFS::Server {
  std::string user;
  std::string root;
  std::string suffix;

public:
  explicit GhostFSImpl(std::string _user, std::string _root, std::string _suffix)
      : user(move(_user)), root(move(_root)), suffix(move(_suffix)) {}

  kj::Promise<void> lookup(LookupContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    uint64_t parent = req.getParent();
    std::string name = req.getName();

    std::string user_root = normalize_path(root, user, suffix);
    std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
    std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
    std::filesystem::path file_path = parent_path / std::filesystem::path(name);

    if (!std::filesystem::exists(file_path)) {
      int err = errno;
      response.setErrno(err);
      response.setRes(-1);
      return kj::READY_NOW;
    }

    uint64_t ino;

    if (path_to_ino.find(file_path) == path_to_ino.end()) {
      ino = ++current_ino;
      ino_to_path[ino] = file_path;
      path_to_ino[file_path] = ino;
    } else {
      ino = path_to_ino[file_path];
    }

    response.setIno(ino);

    // e.attr_timeout = 1.0;
    // e.entry_timeout = 1.0;

    struct stat attr;

    memset(&attr, 0, sizeof(attr));

    int res = hello_stat(ino, &attr);
    int err = errno;

    LookupResponse::Attr::Builder attributes = response.initAttr();

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

    response.setErrno(err);
    response.setRes(res);

    return kj::READY_NOW;
  }

  kj::Promise<void> getattr(GetattrContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    struct stat attr;

    memset(&attr, 0, sizeof(attr));

    int res = hello_stat(req.getIno(), &attr);
    int err = errno;

    GetattrResponse::Attr::Builder attributes = response.initAttr();

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
    // std::cout << "st_nlink " << attr.st_nlink << " " << attributes.getStNlink() <<
    // std::endl; std::cout << "st_uid " << attr.st_uid << " " << attributes.getStUid() <<
    // std::endl; std::cout << "st_gid " << attr.st_gid << " " << attributes.getStGid() <<
    // std::endl; std::cout << "st_rdev " << attr.st_rdev << " " << attributes.getStRdev() <<
    // std::endl; std::cout << "st_size " << attr.st_size << " " << attributes.getStSize() <<
    // std::endl; std::cout << "st_atime " << attr.st_atime << " " << attributes.getStAtime()
    // << std::endl; std::cout << "st_mtime " << attr.st_mtime << " " <<
    // attributes.getStMtime() << std::endl; std::cout << "st_ctime " << attr.st_ctime << " "
    // << attributes.getStCtime() << std::endl; std::cout << "st_blksize " << attr.st_blksize
    // << " " << attributes.getStBlksize() << std::endl; std::cout << "st_blocks " <<
    // attr.st_blocks << " " << attributes.getStBlocks()
    // << std::endl;

    response.setErrno(err);
    response.setRes(res);

    // std::cout << "getattr_response sent correctly: " << response_payload << std::endl;

    return kj::READY_NOW;
  }

  kj::Promise<void> setattr(SetattrContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    uint64_t ino = req.getIno();

    int err = 0;

    if (ino_to_path.find(ino) == ino_to_path.end()) {
      // Parent is unknown
      err = errno;
      response.setErrno(err);
      response.setRes(-1);
      return kj::READY_NOW;
    }

    std::string file_path = ino_to_path[ino];

    Setattr::Attr::Reader attr = req.getAttr();
    Setattr::Attr::TimeSpec::Reader stAtime = attr.getStAtime();
    Setattr::Attr::TimeSpec::Reader stMtime = attr.getStMtime();

    struct timespec a_time = {.tv_sec = stAtime.getTvSec(), .tv_nsec = stAtime.getTvNSec()};
    struct timespec m_time = {.tv_sec = stMtime.getTvSec(), .tv_nsec = stMtime.getTvNSec()};

    uint64_t to_set = req.getToSet();

    int res;

    if (to_set & FUSE_SET_ATTR_MODE) {
      res = chmod(file_path.c_str(), attr.getStMode());
      if (res == -1) {
        err = errno;
        response.setErrno(err);
        response.setRes(res);
        return kj::READY_NOW;
      }
    }

    if (to_set & (FUSE_SET_ATTR_UID | FUSE_SET_ATTR_GID)) {
      uid_t uid = (to_set & FUSE_SET_ATTR_UID) ? attr.getStUid() : (uid_t)-1;
      gid_t gid = (to_set & FUSE_SET_ATTR_GID) ? attr.getStGid() : (gid_t)-1;

      res = lchown(file_path.c_str(), uid, gid);
      if (res == -1) {
        err = errno;
        response.setErrno(err);
        response.setRes(res);
        return kj::READY_NOW;
      }
    }

    if (to_set & FUSE_SET_ATTR_SIZE) {
      res = truncate(file_path.c_str(), attr.getStSize());
      if (res == -1) {
        err = errno;
        response.setErrno(err);
        response.setRes(res);
        return kj::READY_NOW;
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
      err = errno;
      response.setErrno(err);


      if (res == -1) {
        response.setErrno(err);
        response.setRes(res);
        return kj::READY_NOW;
      }
    }

    response.setIno(ino);
    response.setErrno(err);
    response.setRes(0);
    return kj::READY_NOW;
  }

  kj::Promise<void> mknod(MknodContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    uint64_t parent = req.getParent();

    std::string user_root = normalize_path(root, user, suffix);
    std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
    std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
    std::filesystem::path file_path = parent_path / req.getName();

    uint64_t file_ino;

    file_ino = ++current_ino;
    ino_to_path[file_ino] = file_path;
    path_to_ino[file_path] = file_ino;

    int res = ::mknod(file_path.c_str(), req.getMode(), req.getRdev());
    int err = errno;

    if (res == -1) {      
      ino_to_path.erase(file_ino);
      path_to_ino.erase(file_path);
      
      response.setErrno(err);
      response.setRes(res);
      return kj::READY_NOW;
    } else {
      response.setIno(file_ino);

      struct stat attr;
      memset(&attr, 0, sizeof(attr));

      //e.attr_timeout = 1.0;
      //e.entry_timeout = 1.0;

      hello_stat(file_ino, &attr);
      
      MknodResponse::Attr::Builder attributes = response.initAttr();

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
    
    response.setErrno(err);
    response.setRes(res);

    // std::cout << "mknod_response sent correctly: " << response_payload << std::endl;

    return kj::READY_NOW;
  }

   kj::Promise<void> mkdir(MkdirContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    uint64_t parent = req.getParent();

    std::string user_root = normalize_path(root, user, suffix);
    std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
    std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
    std::filesystem::path file_path = parent_path / req.getName();

    int res = ::mkdir(file_path.c_str(), req.getMode());
    int err = errno;

    if (res == -1) {
      response.setRes(-1);
      response.setErrno(err);
      return kj::READY_NOW;
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
      
      response.setIno(file_ino);

      hello_stat(file_ino, &attr);

      MkdirResponse::Attr::Builder attributes = response.initAttr();

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
    
    response.setErrno(err);
    response.setRes(res);

    // std::cout << "mkdir_response sent correctly: " << response_payload << std::endl;

    return kj::READY_NOW;
  }

  kj::Promise<void> unlink(UnlinkContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    uint64_t parent = req.getParent();
    std::string name = req.getName();

    std::string user_root = normalize_path(root, user, suffix);
    std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
    std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
    std::filesystem::path file_path = parent_path / std::filesystem::path(name);

    // TODO: this removes write protected files without warning
    int res = ::unlink(file_path.c_str());
    int err = errno;

    response.setErrno(err);
    response.setRes(res);

    return kj::READY_NOW;
  }

  kj::Promise<void> rmdir(RmdirContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    uint64_t parent = req.getParent();
    std::string name = req.getName();

    // std::cout << "RMDIR name: " << name << std::endl;

    std::string user_root = normalize_path(root, user, suffix);
    std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
    std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
    std::filesystem::path file_path = parent_path / std::filesystem::path(name);

    // std::cout << "RMDIR file_path: " << file_path.c_str() << std::endl;

    int res = ::rmdir(file_path.c_str());
    int err = errno;
    
    response.setErrno(err);
    response.setRes(res);

    return kj::READY_NOW;
  }

  kj::Promise<void> rename(RenameContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    uint64_t parent = req.getParent();
    std::string name = req.getName();
    uint64_t newparent = req.getNewparent();
    std::string newname = req.getNewname();

    std::string user_root = normalize_path(root, user, suffix);

    std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
    std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
    std::filesystem::path file_path = parent_path / std::filesystem::path(name);

    std::string newparent_path_name = newparent == 1 ? user_root : ino_to_path[newparent];
    std::filesystem::path newparent_path = std::filesystem::path(newparent_path_name);
    std::filesystem::path newfile_path = newparent_path / std::filesystem::path(newname);

    // use rename
    int res = ::rename(file_path.c_str(), newfile_path.c_str());
    int err = errno;

    response.setErrno(err);
    response.setRes(res);

    // std::cout << "rename_response sent correctly: " << response_payload << std::endl;

    return kj::READY_NOW;
  }

   kj::Promise<void> open(OpenContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    if (ino_to_path.find(req.getIno()) == ino_to_path.end()) {
      // File is unknown
      response.setRes(-1);
      response.setErrno(ENOENT);
      return kj::READY_NOW;
    }

    response.setIno(req.getIno());

    Open::FuseFileInfo::Reader fi = req.getFi();

    int64_t fh = ::open(ino_to_path[req.getIno()].c_str(), fi.getFlags());
    int err = errno;
    response.setErrno(err);
    response.setRes(fh);

    if (fh == -1) {
      response.setRes(fh);
      return kj::READY_NOW;
    }

    OpenResponse::FuseFileInfo::Builder fi_response = response.initFi();

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

    // std::cout << "open_response sent correctly: " << response_payload << std::endl;

    return kj::READY_NOW;
  }

  kj::Promise<void> read(ReadContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    if (ino_to_path.find(req.getIno()) == ino_to_path.end()) {
      // File is unknown
      response.setRes(-1);
      response.setErrno(ENOENT);
      return kj::READY_NOW;
    }

    size_t size = req.getSize();
    off_t off = req.getOff();

    char buf[size];

    Read::FuseFileInfo::Reader fi = req.getFi();

    ::lseek(fi.getFh(), off, SEEK_SET);
    ::read(fi.getFh(), &buf, size);

    int err = errno;

    kj::ArrayPtr<kj::byte> buf_ptr = kj::arrayPtr((kj::byte*)buf, size);
    capnp::Data::Reader buf_reader(buf_ptr);

    response.setBuf(buf_reader);
    response.setErrno(err);
    response.setRes(0);

    return kj::READY_NOW;
  }

  kj::Promise<void> write(WriteContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    Write::FuseFileInfo::Reader fi = req.getFi();
    capnp::Data::Reader buf_reader = req.getBuf();

    const auto chars = buf_reader.asChars();
    const char* buf = chars.begin();

    ::lseek(fi.getFh(), req.getOff(), SEEK_SET);
    size_t written = ::write(fi.getFh(), buf, req.getSize());

    int err = errno;

    auto results = context.getResults();
    auto response = results.getRes();

    response.setRes(0);
    response.setErrno(err);
    response.setIno(req.getIno());
    response.setWritten(written);

    return kj::READY_NOW;
  }

  kj::Promise<void> bulkWrite(BulkWriteContext context) override {
    auto params = context.getParams();
    auto reqs = params.getReq();

    int64_t count = 0;
    for ([[maybe_unused]] auto req : reqs) {
      count++;
    }

    auto results = context.getResults();
    auto response = results.initRes(count);

    int64_t i = 0;
    for (auto req : reqs) {
      Write::FuseFileInfo::Reader fi = req.getFi();
      capnp::Data::Reader buf_reader = req.getBuf();

      const auto chars = buf_reader.asChars();
      const char* buf = chars.begin();

      ::lseek(fi.getFh(), req.getOff(), SEEK_SET);
      size_t written = ::write(fi.getFh(), buf, req.getSize());
      int err = errno;

      response[i].setRes(0);
      response[i].setErrno(err);
      response[i].setIno(req.getIno());
      response[i++].setWritten(written);
    }

    return kj::READY_NOW;
  }

  kj::Promise<void> release(ReleaseContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    Release::FuseFileInfo::Reader fi = req.getFi();

    int res = ::close(fi.getFh());
    int err = errno;

    response.setErrno(err);
    response.setRes(res);

    return kj::READY_NOW;
  }

  kj::Promise<void> readdir(ReaddirContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    uint64_t ino = req.getIno();

    /**
     * Check if authenticated (example).
     * On fail we need to return a fuse error.
     * EACCESS for access denied.
     */
    // TODO
    bool auth = is_authenticated(user);

    if (!auth) {
      response.setErrno(EACCES);
      response.setRes(-1);

      return kj::READY_NOW;
    }  // END EXAMPLE

    std::string path;

    // Root
    if (ino == 1) {
      path = normalize_path(root, user, suffix);
    } else if (ino_to_path.find(ino) != ino_to_path.end()) {
      path = ino_to_path[ino];
    } else {
      response.setErrno(ENOENT);
      response.setRes(-1);

      return kj::READY_NOW;
    }

    /**
     * example check access
     * TODO: Add suffix here
     */
    bool access_ok = check_access(root, user, path);

    if (!access_ok) {
      response.setErrno(EACCES);
      response.setRes(-1);

      return kj::READY_NOW;
    }  // END EXAMPLE

    uint64_t length = 2;

    std::filesystem::directory_iterator iter(
        path, std::filesystem::directory_options::skip_permission_denied);

    for ([[maybe_unused]] const auto& entry : iter) {
      length++;
    }

    ::capnp::List<ReaddirResponse::Entry>::Builder entries = response.initEntries(length);

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

    response.setErrno(0);
    response.setRes(0);

    // std::cout << "readdir_response sent correctly: " << response_payload << std::endl;

    return kj::READY_NOW;
  }
  
  #ifdef __APPLE__
  kj::Promise<void> setxattr(SetxattrContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    uint64_t ino = req.getIno();

    std::string file_path = ino_to_path[ino];

    int res = ::setxattr(file_path.c_str(), req.getName().cStr(), req.getValue().cStr(), (size_t) req.getSize(), req.getPosition(), req.getFlags());
    int err = errno;
    response.setRes(res);
    response.setErrno(err);
    
    if (res == -1) {
      return kj::READY_NOW;
    }

    response.setIno(ino);
    return kj::READY_NOW;

    // std::cout << "setxattr_response sent correctly: " << response_payload << std::endl;
  }
  #endif

  kj::Promise<void> create(CreateContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    Create::FuseFileInfo::Reader fi = req.getFi();

    uint64_t parent = req.getParent();

    std::string user_root = normalize_path(root, user, suffix);
    std::string parent_path_name = parent == 1 ? user_root : ino_to_path[parent];
    std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
    std::filesystem::path file_path = parent_path / req.getName();

    // std::cout << "create: open file path: " << file_path.c_str() << std::endl;
    // std::cout << "create: flags: " << fi.getFlags() << std::endl;

    int res = ::creat(file_path.c_str(), req.getMode());

    if (res == -1) {
      int err = errno;

      response.setRes(res);
      response.setErrno(err);
      return kj::READY_NOW;
    }

    struct stat attr;
    memset(&attr, 0, sizeof(attr));

    uint64_t file_ino;

    file_ino = ++current_ino;
    ino_to_path[file_ino] = file_path;
    path_to_ino[file_path] = file_ino;

    // e.attr_timeout = 1.0;
    // e.entry_timeout = 1.0;

    CreateResponse::FuseFileInfo::Builder fi_response = response.initFi();

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

    response.setIno(file_ino);

    CreateResponse::Attr::Builder attributes = response.initAttr();

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

    response.setErrno(err);
    response.setRes(res);

    return kj::READY_NOW;
  }

  kj::Promise<void> flush(FlushContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    Flush::FuseFileInfo::Reader fi = req.getFi();

    int res = ::close(dup(fi.getFh()));
    int err = errno;

    response.setErrno(err);
    response.setRes(res);

    return kj::READY_NOW;
  }

  kj::Promise<void> fsync(FsyncContext context) override {
    auto params = context.getParams();
    auto req = params.getReq();

    auto results = context.getResults();
    auto response = results.getRes();

    Fsync::FuseFileInfo::Reader fi = req.getFi();

    #ifndef __APPLE__
      int res;
      uint64_t datasync = req.getDatasync();
      if (datasync) {
        res = ::fdatasync(fi.getFh());
      } else
        res = ::fsync(fi.getFh());
      }
    #else
      int res = ::fsync(fi.getFh());
    #endif

    int err = errno;

    response.setErrno(err);
    response.setRes(res);

    return kj::READY_NOW;
  }

  // Any method which we don't implement will simply throw
  // an exception by default.
};

class GhostFSAuthServerImpl final : public GhostFSAuthServer::Server {
  public:

    kj::Promise<void> authorize(AuthorizeContext context) override {
      auto params = context.getParams();

      auto userPtr = params.getUser();
      std::string user(userPtr.begin(), userPtr.end());

      auto tokenPtr = params.getToken();
      std::string token(tokenPtr.begin(), tokenPtr.end());

      uint64_t retries = params.getRetries();

      std::string token_final = add_token(user, token, retries);

      auto res = context.getResults();
      res.setToken(token_final);
      
      return kj::READY_NOW;
    }
};

int rpc_add_token(uint16_t port, std::string user, std::string token, int64_t retries) {
  capnp::EzRpcClient rpc("127.0.0.1", port);

  auto& waitScope = rpc.getWaitScope();
  GhostFSAuthServer::Client authClient = rpc.getMain<GhostFSAuthServer>();

  auto request = authClient.authorizeRequest();

  request.setUser(user);
  request.setToken(token);
  request.setRetries(retries);

  auto promise = request.send();
  auto result = promise.wait(waitScope);
  auto tokenPtr = result.getToken();

  std::string tokenFinal(tokenPtr.begin(), tokenPtr.end());
  std::cout << tokenFinal << std::endl;

  return 0;
}

class GhostFSAuthImpl final : public GhostFSAuth::Server {
  std::string root;
  std::string suffix;

public:
  explicit GhostFSAuthImpl(std::string _root, std::string _suffix)
      : root(move(_root)), suffix(move(_suffix)) {}

  kj::Promise<void> auth(AuthContext context) override {
    auto params = context.getParams();

    auto userPtr = params.getUser();
    std::string user(userPtr.begin(), userPtr.end());

    auto tokenPtr = params.getToken();
    std::string token(tokenPtr.begin(), tokenPtr.end());

    // TODO: in previous WebSocket implementation userId
    // wasn't equal to user's subdirectory, this needs attention
    bool isValid = authenticate(token, user, user);
    auto res = context.getResults();
    
    res.setAuthSuccess(isValid);

    if (isValid) {
      res.setGhostFs(kj::heap<GhostFSImpl>(user, root, suffix));
      std::cout << "User " << user << "connected.";
    }

    return kj::READY_NOW;
  }
};

int start_rpc_server(std::string bind, int port, int auth_port, std::string root, std::string suffix) {
  if (root.length() > 0) {
    if (!std::filesystem::is_directory(root)) {
      std::cout << "ERROR: directory " << '"' << root << '"' << " does not exist." << std::endl;
      return 1;
    };
  }

  std::cout << "Starting GhostFS server on " << bind << ":" << port << "..." << std::endl;
  std::cout << "Starting GhostFS auth server on port " << auth_port << "..." << std::endl;

  /**
   * Capnp RPC server. We need to find out how to pass parameters to the
   * GhostFSImpl class, instead of assigning them globally.
   */

  capnp::EzRpcServer auth_rpc_server(kj::heap<GhostFSAuthServerImpl>(), "127.0.0.1", auth_port);
  capnp::EzRpcServer rpc_server(kj::heap<GhostFSAuthImpl>(root, suffix), bind, port);

  // Run forever, accepting connections and handling requests.
  auto& waitScope = rpc_server.getWaitScope();
  kj::NEVER_DONE.wait(waitScope);

  return 0;
}