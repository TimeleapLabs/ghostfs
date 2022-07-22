/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>
  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.
  gcc -Wall hello_ll.c `pkg-config fuse --cflags --libs` -o hello_ll
*/

#define FUSE_USE_VERSION 29

#include <assert.h>
#include <fcntl.h>
#include <fuse_lowlevel.h>
#include <ghostfs/fs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <uuid_v4.h>

// CAPNPROTO

#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <create.capnp.h>
#include <create.response.capnp.h>
#include <getattr.capnp.h>
#include <getattr.response.capnp.h>
#include <ghostfs/ws.h>
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
#include <setattr.capnp.h>
#include <setattr.response.capnp.h>
#include <setxattr.capnp.h>
#include <setxattr.response.capnp.h>
#include <sys/xattr.h>
#include <unlink.capnp.h>
#include <unlink.response.capnp.h>
#include <write.capnp.h>
#include <write.response.capnp.h>
#include <rmdir.capnp.h>
#include <rmdir.response.capnp.h>

#include <filesystem>
#include <iostream>
#include <map>

static const char *hello_str = "Hello World!\n";
static const char *hello_name = "hello";

char user_file_str[40];
char user_file_name[1024];

UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

std::map<uint64_t, std::string> ino_to_path;
std::map<std::string, uint64_t> path_to_ino;

uint64_t current_ino = 1;

std::string gen_uuid() {
  UUIDv4::UUID uuid = uuidGenerator.getUUID();
  return uuid.str();
}

std::string ROOT = "/tmp/.ghostfs/root";

struct request {
  char *name;
  Ops type;
  fuse_req_t req;
  fuse_file_info *fi;
  size_t size;
  off_t off;
};

#define min(x, y) ((x) < (y) ? (x) : (y))

static int reply_buf_limited(fuse_req_t req, const char *buf, size_t bufsize, off_t off,
                             size_t maxsize) {
  if (off < bufsize)
    return fuse_reply_buf(req, buf + off, min(bufsize - off, maxsize));
  else
    return fuse_reply_buf(req, NULL, 0);
}

std::map<std::string, request> requests;

wsclient::WSClient *ws;

uint64_t get_parent_ino(uint64_t ino, std::string path) {
  if (ino == 1) {
    return ino;
  }

  std::filesystem::path parent_path = std::filesystem::path(path).parent_path();
  uint64_t parent_ino = path_to_ino[parent_path];

  return parent_ino;
}

template <class T> void fillFileInfo(T *fuseFileInfo, struct fuse_file_info *fi) {
  if (!fi) return;

  fuseFileInfo->setFlags(fi->flags);
  fuseFileInfo->setWritepage(fi->writepage);
  fuseFileInfo->setDirectIo(fi->direct_io);
  fuseFileInfo->setKeepCache(fi->keep_cache);
  fuseFileInfo->setFlush(fi->flush);
  fuseFileInfo->setNonseekable(fi->nonseekable);
  /* fuseFileInfo->setCacheReaddir(fi->cache_readdir); */
  fuseFileInfo->setPadding(fi->padding);
  fuseFileInfo->setFh(fi->fh);
  fuseFileInfo->setLockOwner(fi->lock_owner);
  /* fuseFileInfo->setPollEvents(fi->poll_events); */
  /* fuseFileInfo->setNoflush(fi->noflush); */
}

void process_response(uint8_t msg) {}
/**
 * Notes: fuse_ino_t is uint64_t
 *        off_t is apparently long int
 *        size_t is apparently unsigned int
 *        fuse_file_info check https://libfuse.github.io/doxygen/structfuse__file__info.html
 *        struct stat check https://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html and
 *                          https://doc.rust-lang.org/std/os/linux/raw/struct.stat.html
 *
 * Cool little trick:
 *        gcc -E -xc -include time.h /dev/null | grep time_t
 *        gcc -E -xc -include sys/types.h /dev/null | grep nlink_t
 *
 * Useful stuff:
 *        http://www.sde.cs.titech.ac.jp/~gondow/dwarf2-xml/HTML-rxref/app/gcc-3.3.2/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h.html
 *        Apparently Solaris devs knew how to write non-cryptic code
 */

int hello_stat(fuse_ino_t ino, struct stat *stbuf) {
  if (ino == 1) {
    // This is the fs root
    stbuf->st_ino = ino;
    stbuf->st_mode = S_IFDIR | 0777;
    stbuf->st_nlink = 2;
    return 0;
  }

  if (ino_to_path.find(ino) == ino_to_path.end()) {
    // File is unknown
    return -1;
  }

  stat(ino_to_path[ino].c_str(), stbuf);
  stbuf->st_ino = ino;

  return 0;
}

void process_lookup_response(std::string payload) {
  const kj::ArrayPtr<const capnp::word> view(
      reinterpret_cast<const capnp::word *>(&(*std::begin(payload))),
      reinterpret_cast<const capnp::word *>(&(*std::end(payload))));

  capnp::FlatArrayMessageReader data(view);
  LookupResponse::Reader lookup_response = data.getRoot<LookupResponse>();

  struct stat attr;

  memset(&attr, 0, sizeof(attr));

  std::string uuid = lookup_response.getUuid();

  // std::cout << "process_lookup_response: Response UUID: " << uuid << std::endl;

  request request = requests[uuid];

  int res = lookup_response.getRes();

  if (res == -1) {
    // std::cout << "LOOKUP::ENOENT" << std::endl;
    fuse_reply_err(request.req, lookup_response.getErrno());
    return;
  }

  struct fuse_entry_param e;

  memset(&e, 0, sizeof(e));
  e.ino = lookup_response.getIno();
  e.attr_timeout = 1.0;
  e.entry_timeout = 1.0;

  LookupResponse::Attr::Reader attributes = lookup_response.getAttr();

  e.attr.st_dev = attributes.getStDev();
  e.attr.st_ino = attributes.getStIno();
  e.attr.st_mode = attributes.getStMode();
  e.attr.st_nlink = attributes.getStNlink();
  e.attr.st_uid = attributes.getStUid();
  e.attr.st_gid = attributes.getStGid();
  e.attr.st_rdev = attributes.getStRdev();
  e.attr.st_size = attributes.getStSize();
  e.attr.st_atime = attributes.getStAtime();
  e.attr.st_mtime = attributes.getStMtime();
  e.attr.st_ctime = attributes.getStCtime();
  e.attr.st_blksize = attributes.getStBlksize();
  e.attr.st_blocks = attributes.getStBlocks();

  // std::cout << "process_lookup_response: Request: " << request.req << std::endl;

  fuse_reply_entry(request.req, &e);

  std::cout << "process_lookup_response: fuse_reply_entry correctly executed" << std::endl;
}

void process_getattr_response(std::string payload) {
  const kj::ArrayPtr<const capnp::word> view(
      reinterpret_cast<const capnp::word *>(&(*std::begin(payload))),
      reinterpret_cast<const capnp::word *>(&(*std::end(payload))));

  capnp::FlatArrayMessageReader data(view);
  GetattrResponse::Reader getattr_response = data.getRoot<GetattrResponse>();

  struct stat attr;

  memset(&attr, 0, sizeof(attr));

  std::string uuid = getattr_response.getUuid();

  // std::cout << "process_getattr_response: Response UUID: " << uuid << std::endl;

  request request = requests[uuid];

  int res = getattr_response.getRes();

  if (res == -1) {
    fuse_reply_err(request.req, getattr_response.getErrno());
    return;
  }

  GetattrResponse::Attr::Reader attributes = getattr_response.getAttr();

  attr.st_dev = attributes.getStDev();
  attr.st_ino = attributes.getStIno();
  attr.st_mode = attributes.getStMode();
  attr.st_nlink = attributes.getStNlink();
  attr.st_uid = attributes.getStUid();
  attr.st_gid = attributes.getStGid();
  attr.st_rdev = attributes.getStRdev();
  attr.st_size = attributes.getStSize();
  attr.st_atime = attributes.getStAtime();
  attr.st_mtime = attributes.getStMtime();
  attr.st_ctime = attributes.getStCtime();
  attr.st_blksize = attributes.getStBlksize();
  attr.st_blocks = attributes.getStBlocks();

  // std::cout << "process_getattr_response: Request: " << request.req << std::endl;

  fuse_reply_attr(request.req, &attr, 1.0);

  std::cout << "process_getattr_response: fuse_reply_attr correctly executed" << std::endl;
}

void dirbuf_add(fuse_req_t req, struct dirbuf *b, const char *name, fuse_ino_t ino) {
  struct stat stbuf;
  size_t oldsize = b->size;
  b->size += fuse_add_direntry(req, NULL, 0, name, NULL, 0);
  b->p = (char *)realloc(b->p, b->size);
  memset(&stbuf, 0, sizeof(stbuf));
  stbuf.st_ino = ino;
  fuse_add_direntry(req, b->p + oldsize, b->size - oldsize, name, &stbuf, b->size);
}

void process_readdir_response(std::string payload) {
  const kj::ArrayPtr<const capnp::word> view(
      reinterpret_cast<const capnp::word *>(&(*std::begin(payload))),
      reinterpret_cast<const capnp::word *>(&(*std::end(payload))));

  capnp::FlatArrayMessageReader data(view);
  ReaddirResponse::Reader readdir_response = data.getRoot<ReaddirResponse>();

  struct dirbuf b;

  memset(&b, 0, sizeof(b));

  std::string uuid = readdir_response.getUuid();

  // std::cout << "process_readdir_response: Response UUID: " << uuid << std::endl;

  // TODO: FIX type name
  request request = requests[uuid];

  int res = readdir_response.getRes();

  if (res == -1) {
    fuse_reply_err(request.req, ENOENT);
    return;
  }

  for (ReaddirResponse::Entry::Reader entry : readdir_response.getEntries()) {
    dirbuf_add(request.req, &b, entry.getName().cStr(), entry.getIno());
  }

  reply_buf_limited(request.req, b.p, b.size, request.off, request.size);
  // free(b.p);

  std::cout << "process_readdir_response: reply_buf_limited correctly executed" << std::endl;
}

void process_open_response(std::string payload) {
  const kj::ArrayPtr<const capnp::word> view(
      reinterpret_cast<const capnp::word *>(&(*std::begin(payload))),
      reinterpret_cast<const capnp::word *>(&(*std::end(payload))));

  capnp::FlatArrayMessageReader data(view);
  OpenResponse::Reader open_response = data.getRoot<OpenResponse>();

  // struct fuse_file_info fi;

  // memset(&fi, 0, sizeof(fi));

  std::string uuid = open_response.getUuid();

  // std::cout << "process_open_response: Response UUID: " << uuid << std::endl;

  request request = requests[uuid];

  int res = open_response.getRes();

  // TODO: FIX THESE
  if (res == -1) {
    fuse_reply_err(request.req, ENOENT);
    return;
  }

  OpenResponse::FuseFileInfo::Reader fi_response = open_response.getFi();

  // fi.cache_readdir = fi_response.getCacheReaddir();
  // fi.direct_io = fi_response.getDirectIo();
  request.fi->fh = fi_response.getFh();
  // fi.flags = fi_response.getFlags();
  //  fi.flush = fi_response.getFlush();
  // fi.keep_cache = fi_response.getKeepCache();
  // fi.lock_owner = fi_response.getLockOwner();
  //  fi.noflush = fi_response.getNoflush();
  // fi.nonseekable = fi_response.getNonseekable();
  // fi.padding = fi_response.getPadding();
  //  fi.poll_events = fi_response.getPollEvents();
  // fi.writepage = fi_response.getWritepage();

  // std::cout << "process_getattr_response: Request: " << request.req << std::endl;

  fuse_reply_open(request.req, request.fi);

  std::cout << "process_getattr_response: fuse_reply_open correctly executed" << std::endl;
}

void process_read_response(std::string payload) {
  const kj::ArrayPtr<const capnp::word> view(
      reinterpret_cast<const capnp::word *>(&(*std::begin(payload))),
      reinterpret_cast<const capnp::word *>(&(*std::end(payload))));

  capnp::FlatArrayMessageReader data(view);
  ReadResponse::Reader read_response = data.getRoot<ReadResponse>();

  struct fuse_file_info fi;

  memset(&fi, 0, sizeof(fi));

  std::string uuid = read_response.getUuid();

  // std::cout << "process_read_response: Response UUID: " << uuid << std::endl;

  request request = requests[uuid];

  int res = read_response.getRes();

  if (res == -1) {
    // std::cout << "READ::ENOENT" << std::endl;
    fuse_reply_err(request.req, read_response.getErrno());
    return;
  }

  // std::cout << "process_read_response: Request: " << request.req << std::endl;

  capnp::Data::Reader buf_reader = read_response.getBuf();
  const auto bytes = buf_reader.asBytes();
  std::string buf(bytes.begin(), bytes.end());

  reply_buf_limited(request.req, buf.c_str(), request.size, request.off, request.size);

  std::cout << "process_read_response: reply_buf_limited correctly executed" << std::endl;
}

static void hello_ll_getattr(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi);

void process_setattr_response(std::string payload) {
  const kj::ArrayPtr<const capnp::word> view(
      reinterpret_cast<const capnp::word *>(&(*std::begin(payload))),
      reinterpret_cast<const capnp::word *>(&(*std::end(payload))));

  capnp::FlatArrayMessageReader data(view);
  SetattrResponse::Reader setattr_response = data.getRoot<SetattrResponse>();

  struct fuse_file_info fi;

  memset(&fi, 0, sizeof(fi));

  std::string uuid = setattr_response.getUuid();

  // std::cout << "process_setattr_response: Response UUID: " << uuid << std::endl;

  request request = requests[uuid];

  int res = setattr_response.getRes();

  if (res == -1) {
    // std::cout << "SETATTR::ENOENT" << std::endl;
    fuse_reply_err(request.req, setattr_response.getErrno());
    return;
  }

  hello_ll_getattr(request.req, setattr_response.getIno(), request.fi);

  std::cout << "process_setattr_response: hello_ll_getattr correctly executed" << std::endl;
}

void process_write_response(std::string payload) {
  const kj::ArrayPtr<const capnp::word> view(
      reinterpret_cast<const capnp::word *>(&(*std::begin(payload))),
      reinterpret_cast<const capnp::word *>(&(*std::end(payload))));

  capnp::FlatArrayMessageReader data(view);
  WriteResponse::Reader write_response = data.getRoot<WriteResponse>();

  std::string uuid = write_response.getUuid();

  // std::cout << "process_write_response: Response UUID: " << uuid << std::endl;

  request request = requests[uuid];

  int res = write_response.getRes();

  if (res == -1) {
    // std::cout << "WRITE::ENOENT" << std::endl;
    fuse_reply_err(request.req, write_response.getErrno());
    return;
  }

  fuse_reply_write(request.req, write_response.getWritten());

  std::cout << "process_setattr_response: fuse_reply_write correctly executed" << std::endl;
}

void process_setxattr_response(std::string payload) {
  const kj::ArrayPtr<const capnp::word> view(
      reinterpret_cast<const capnp::word *>(&(*std::begin(payload))),
      reinterpret_cast<const capnp::word *>(&(*std::end(payload))));

  capnp::FlatArrayMessageReader data(view);
  SetxattrResponse::Reader setxattr_response = data.getRoot<SetxattrResponse>();

  std::string uuid = setxattr_response.getUuid();

  // std::cout << "process_setxattr_response: Response UUID: " << uuid << std::endl;

  request request = requests[uuid];

  int res = setxattr_response.getRes();

  if (res == -1) {
    // std::cout << "SETXATTR::ENOENT" << std::endl;
    fuse_reply_err(request.req, setxattr_response.getErrno());
    return;
  }

  std::cout << "process_setxattr_response: correctly executed" << std::endl;
}

void process_create_response(std::string payload) {
  const kj::ArrayPtr<const capnp::word> view(
      reinterpret_cast<const capnp::word *>(&(*std::begin(payload))),
      reinterpret_cast<const capnp::word *>(&(*std::end(payload))));

  capnp::FlatArrayMessageReader data(view);
  CreateResponse::Reader create_response = data.getRoot<CreateResponse>();

  struct stat attr;

  memset(&attr, 0, sizeof(attr));

  std::string uuid = create_response.getUuid();

  // std::cout << "process_create_response: Response UUID: " << uuid << std::endl;

  request request = requests[uuid];

  int res = create_response.getRes();

  if (res == -1) {
    // std::cout << "CREATE::ENOENT" << std::endl;
    fuse_reply_err(request.req, create_response.getErrno());
    return;
  }

  struct fuse_entry_param e;

  memset(&e, 0, sizeof(e));
  e.ino = create_response.getIno();
  e.attr_timeout = 1.0;
  e.entry_timeout = 1.0;

  CreateResponse::Attr::Reader attributes = create_response.getAttr();

  e.attr.st_dev = attributes.getStDev();
  e.attr.st_ino = attributes.getStIno();
  e.attr.st_mode = attributes.getStMode();
  e.attr.st_nlink = attributes.getStNlink();
  e.attr.st_uid = attributes.getStUid();
  e.attr.st_gid = attributes.getStGid();
  e.attr.st_rdev = attributes.getStRdev();
  e.attr.st_size = attributes.getStSize();
  e.attr.st_atime = attributes.getStAtime();
  e.attr.st_mtime = attributes.getStMtime();
  e.attr.st_ctime = attributes.getStCtime();
  e.attr.st_blksize = attributes.getStBlksize();
  e.attr.st_blocks = attributes.getStBlocks();

  // std::cout << "process_create_response: Request: " << request.req << std::endl;

  CreateResponse::FuseFileInfo::Reader fi_response = create_response.getFi();

  request.fi->fh = fi_response.getFh();

  fuse_reply_create(request.req, &e, request.fi);

  std::cout << "process_create_response: fuse_reply_create correctly executed" << std::endl;
}

void process_mknod_response(std::string payload) {
  const kj::ArrayPtr<const capnp::word> view(
      reinterpret_cast<const capnp::word *>(&(*std::begin(payload))),
      reinterpret_cast<const capnp::word *>(&(*std::end(payload))));

  capnp::FlatArrayMessageReader data(view);
  MknodResponse::Reader mknod_response = data.getRoot<MknodResponse>();

  struct stat attr;

  memset(&attr, 0, sizeof(attr));

  std::string uuid = mknod_response.getUuid();

  // std::cout << "process_mknod_response: Response UUID: " << uuid << std::endl;

  request request = requests[uuid];

  int res = mknod_response.getRes();

  if (res == -1) {
    // std::cout << "MKNOD::ENOENT" << std::endl;
    fuse_reply_err(request.req, mknod_response.getErrno());
    return;
  }

  struct fuse_entry_param e;

  memset(&e, 0, sizeof(e));
  e.ino = mknod_response.getIno();
  e.attr_timeout = 1.0;
  e.entry_timeout = 1.0;

  MknodResponse::Attr::Reader attributes = mknod_response.getAttr();

  e.attr.st_dev = attributes.getStDev();
  e.attr.st_ino = attributes.getStIno();
  e.attr.st_mode = attributes.getStMode();
  e.attr.st_nlink = attributes.getStNlink();
  e.attr.st_uid = attributes.getStUid();
  e.attr.st_gid = attributes.getStGid();
  e.attr.st_rdev = attributes.getStRdev();
  e.attr.st_size = attributes.getStSize();
  e.attr.st_atime = attributes.getStAtime();
  e.attr.st_mtime = attributes.getStMtime();
  e.attr.st_ctime = attributes.getStCtime();
  e.attr.st_blksize = attributes.getStBlksize();
  e.attr.st_blocks = attributes.getStBlocks();

  // std::cout << "process_mknod_response: Request: " << request.req << std::endl;

  fuse_reply_entry(request.req, &e);

  std::cout << "process_mknod_response: fuse_reply_entry correctly executed" << std::endl;
}

void process_mkdir_response(std::string payload) {
  const kj::ArrayPtr<const capnp::word> view(
      reinterpret_cast<const capnp::word *>(&(*std::begin(payload))),
      reinterpret_cast<const capnp::word *>(&(*std::end(payload))));

  capnp::FlatArrayMessageReader data(view);
  MkdirResponse::Reader mkdir_response = data.getRoot<MkdirResponse>();

  struct stat attr;

  memset(&attr, 0, sizeof(attr));

  std::string uuid = mkdir_response.getUuid();

  // std::cout << "process_mkdir_response: Response UUID: " << uuid << std::endl;

  request request = requests[uuid];

  int res = mkdir_response.getRes();

  if (res == -1) {
    // std::cout << "MKDIR::ENOENT" << std::endl;
    fuse_reply_err(request.req, mkdir_response.getErrno());
    return;
  }

  struct fuse_entry_param e;

  memset(&e, 0, sizeof(e));
  e.ino = mkdir_response.getIno();
  e.attr_timeout = 1.0;
  e.entry_timeout = 1.0;

  MkdirResponse::Attr::Reader attributes = mkdir_response.getAttr();

  e.attr.st_dev = attributes.getStDev();
  e.attr.st_ino = attributes.getStIno();
  e.attr.st_mode = attributes.getStMode();
  e.attr.st_nlink = attributes.getStNlink();
  e.attr.st_uid = attributes.getStUid();
  e.attr.st_gid = attributes.getStGid();
  e.attr.st_rdev = attributes.getStRdev();
  e.attr.st_size = attributes.getStSize();
  e.attr.st_atime = attributes.getStAtime();
  e.attr.st_mtime = attributes.getStMtime();
  e.attr.st_ctime = attributes.getStCtime();
  e.attr.st_blksize = attributes.getStBlksize();
  e.attr.st_blocks = attributes.getStBlocks();

  // std::cout << "process_mkdir_response: Request: " << request.req << std::endl;

  fuse_reply_entry(request.req, &e);

  std::cout << "process_mkdir_response: fuse_reply_entry correctly executed" << std::endl;
}

void process_unlink_response(std::string payload) {
  const kj::ArrayPtr<const capnp::word> view(
      reinterpret_cast<const capnp::word *>(&(*std::begin(payload))),
      reinterpret_cast<const capnp::word *>(&(*std::end(payload))));

  capnp::FlatArrayMessageReader data(view);
  UnlinkResponse::Reader unlink_response = data.getRoot<UnlinkResponse>();

  std::string uuid = unlink_response.getUuid();

  // std::cout << "process_unlink_response: Response UUID: " << uuid << std::endl;

  request request = requests[uuid];

  int res = unlink_response.getRes();
  int err = unlink_response.getErrno();

  fuse_reply_err(request.req, res == -1 ? err : 0);

  // std::cout << "process_unlink_response: Request: " << request.req << std::endl;

  std::cout << "process_unlink_response: executed" << std::endl;
}

void process_rmdir_response(std::string payload) {
  const kj::ArrayPtr<const capnp::word> view(
      reinterpret_cast<const capnp::word *>(&(*std::begin(payload))),
      reinterpret_cast<const capnp::word *>(&(*std::end(payload))));

  capnp::FlatArrayMessageReader data(view);
  RmdirResponse::Reader rmdir_response = data.getRoot<RmdirResponse>();

  std::string uuid = rmdir_response.getUuid();

  // std::cout << "process_rmdir_response: Response UUID: " << uuid << std::endl;

  request request = requests[uuid];

  int res = rmdir_response.getRes();
  int err = rmdir_response.getErrno();

  fuse_reply_err(request.req, res == -1 ? err : 0);

  //std::cout << "process_rmdir_response: Request: " << request.req << std::endl;

  std::cout << "process_rmdir_response executed with result: " << res << std::endl;
}

/**
 * @brief
 *
 * @param req
 * @param ino -> uint64_t
 * @param fi -> {
 *             int 	flags
 *    unsigned int 	writepage
 *    unsigned int 	direct_io
 *    unsigned int 	keep_cache
 *    unsigned int 	flush
 *    unsigned int 	nonseekable
 *    unsigned int 	cache_readdir
 *    unsigned int 	padding
 *    uint64_t 	    fh
 *    uint64_t 	    lock_owner
 *    uint32_t 	    poll_events
 *    unsigned int 	noflush
 * }
 */
static void hello_ll_getattr(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi) {
  ::capnp::MallocMessageBuilder message;
  Getattr::Builder getattr = message.initRoot<Getattr>();
  Getattr::FuseFileInfo::Builder fuseFileInfo = getattr.initFi();

  getattr.setIno(ino);

  fillFileInfo(&fuseFileInfo, fi);

  std::string uuid = gen_uuid();
  requests[uuid] = {.type = Ops::Getattr, .req = req};

  // std::cout << "hello_ll_getattr: Request UUID: " << uuid << std::endl;

  getattr.setUuid(uuid);

  const auto data = capnp::messageToFlatArray(message);
  const auto bytes = data.asBytes();
  std::string payload(bytes.begin(), bytes.end());

  ws->send((char)Ops::Getattr + payload);

  std::cout << "hello_ll_getattr executed correctly: " << payload << std::endl;
}

/**
 * @brief
 *
 * @param req
 * @param parent -> uint64_t
 * @param name -> *char
 */
static void hello_ll_lookup(fuse_req_t req, fuse_ino_t parent, const char *name) {
  // printf("Called .lookup\n");

  ::capnp::MallocMessageBuilder message;
  Lookup::Builder lookup = message.initRoot<Lookup>();

  lookup.setParent(parent);
  lookup.setName(name);

  // std::cout << "LOOKUP name: " << name << std::endl;

  std::string uuid = gen_uuid();
  requests[uuid] = {.type = Ops::Lookup, .req = req};

  lookup.setUuid(uuid);

  // std::cout << "hello_ll_lookup: Request UUID: " << uuid << std::endl;

  const auto data = capnp::messageToFlatArray(message);
  const auto bytes = data.asBytes();
  std::string payload(bytes.begin(), bytes.end());

  ws->send((char)Ops::Lookup + payload);

  std::cout << "hello_ll_lookup executed correctly: " << payload << std::endl;
}

/**
 * @brief Readdir fuse low-level function (called when using ls)
 *
 * @param req
 * @param ino -> uint64_t
 * @param size -> unsigned int
 * @param off -> long int
 * @param fi -> {
 *             int 	flags
 *    unsigned int 	writepage
 *    unsigned int 	direct_io
 *    unsigned int 	keep_cache
 *    unsigned int 	flush
 *    unsigned int 	nonseekable
 *    unsigned int 	cache_readdir
 *    unsigned int 	padding
 *    uint64_t 	    fh
 *    uint64_t 	    lock_owner
 *    uint32_t 	    poll_events
 *    unsigned int 	noflush
 * }
 */
static void hello_ll_readdir(fuse_req_t req, fuse_ino_t ino, size_t size, off_t off,
                             struct fuse_file_info *fi) {
  //(void)fi;

  ::capnp::MallocMessageBuilder message;
  Readdir::Builder readdir = message.initRoot<Readdir>();
  Readdir::FuseFileInfo::Builder fuseFileInfo = readdir.initFi();

  readdir.setIno(ino);
  readdir.setSize(size);
  readdir.setOff(off);

  fillFileInfo(&fuseFileInfo, fi);

  // Don't remove these 3 lines
  // const auto m = capnp::messageToFlatArray(message);
  // const auto c = m.asChars();
  // std::cout << "Size: " << c.size() << std::endl;

  // printf("Called .readdir\n");

  std::string uuid = gen_uuid();
  requests[uuid] = {.type = Ops::Readdir, .req = req, .size = size, .off = off};

  readdir.setUuid(uuid);

  // std::cout << "hello_ll_readdir: Request UUID: " << uuid << std::endl;

  const auto data = capnp::messageToFlatArray(message);
  const auto bytes = data.asBytes();
  std::string payload(bytes.begin(), bytes.end());

  ws->send((char)Ops::Readdir + payload);

  std::cout << "hello_ll_readdir executed correctly: " << payload << std::endl;
}

/**
 * @brief
 *
 * @param req
 * @param ino -> uint64_t
 * @param fi -> {
 *             int 	flags
 *    unsigned int 	writepage
 *    unsigned int 	direct_io
 *    unsigned int 	keep_cache
 *    unsigned int 	flush
 *    unsigned int 	nonseekable
 *    unsigned int 	cache_readdir
 *    unsigned int 	padding
 *    uint64_t 	    fh
 *    uint64_t 	    lock_owner
 *    uint32_t 	    poll_events
 *    unsigned int 	noflush
 * }
 */
static void hello_ll_open(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi) {
  // printf("Called .open\n");

  ::capnp::MallocMessageBuilder message;
  Open::Builder open = message.initRoot<Open>();
  Open::FuseFileInfo::Builder fuseFileInfo = open.initFi();

  open.setIno(ino);

  std::string uuid = gen_uuid();
  requests[uuid] = {.type = Ops::Open, .req = req, .fi = fi};

  open.setUuid(uuid);

  fillFileInfo(&fuseFileInfo, fi);

  // std::cout << "hello_ll_open: Request UUID: " << uuid << std::endl;

  const auto data = capnp::messageToFlatArray(message);
  const auto bytes = data.asBytes();
  std::string payload(bytes.begin(), bytes.end());

  ws->send((char)Ops::Open + payload);

  std::cout << "hello_ll_open executed correctly: " << payload << std::endl;
}

/**
 * @brief
 *
 * @param req
 * @param ino -> uint64_t
 * @param size -> unsigned int
 * @param off -> long int
 * @param fi -> {
 *             int 	flags
 *    unsigned int 	writepage
 *    unsigned int 	direct_io
 *    unsigned int 	keep_cache
 *    unsigned int 	flush
 *    unsigned int 	nonseekable
 *    unsigned int 	cache_readdir
 *    unsigned int 	padding
 *    uint64_t 	    fh
 *    uint64_t 	    lock_owner
 *    uint32_t 	    poll_events
 *    unsigned int 	noflush
 * }
 */
static void hello_ll_read(fuse_req_t req, fuse_ino_t ino, size_t size, off_t off,
                          struct fuse_file_info *fi) {
  (void)fi;

  // printf("Called .read\n");

  ::capnp::MallocMessageBuilder message;
  Read::Builder read = message.initRoot<Read>();
  Read::FuseFileInfo::Builder fuseFileInfo = read.initFi();

  read.setIno(ino);
  read.setSize(size);
  read.setOff(off);

  fillFileInfo(&fuseFileInfo, fi);

  std::string uuid = gen_uuid();
  requests[uuid] = {.type = Ops::Read, .req = req, .size = size, .off = off};

  read.setUuid(uuid);

  // std::cout << "hello_ll_read: Request UUID: " << uuid << std::endl;

  const auto data = capnp::messageToFlatArray(message);
  const auto bytes = data.asBytes();
  std::string payload(bytes.begin(), bytes.end());

  ws->send((char)Ops::Read + payload);

  std::cout << "hello_ll_read executed correctly: " << payload << std::endl;
}

/**
 * @brief
 *
 * @param req
 * @param ino -> uint64_t
 * @param buf -> *char
 * @param size -> unsigned int
 * @param off -> long int
 * @param fi -> {
 *             int 	flags
 *    unsigned int 	writepage
 *    unsigned int 	direct_io
 *    unsigned int 	keep_cache
 *    unsigned int 	flush
 *    unsigned int 	nonseekable
 *    unsigned int 	cache_readdir
 *    unsigned int 	padding
 *    uint64_t 	    fh
 *    uint64_t 	    lock_owner
 *    uint32_t 	    poll_events
 *    unsigned int 	noflush
 * }
 */
static void hello_ll_write(fuse_req_t req, fuse_ino_t ino, const char *buf, size_t size, off_t off,
                           struct fuse_file_info *fi) {
  // printf("Called .write\n");

  ::capnp::MallocMessageBuilder message;
  Write::Builder write = message.initRoot<Write>();
  Write::FuseFileInfo::Builder fuseFileInfo = write.initFi();

  write.setIno(ino);
  write.setBuf(buf);
  write.setSize(size);
  write.setOff(off);

  fillFileInfo(&fuseFileInfo, fi);

  std::string uuid = gen_uuid();
  requests[uuid] = {.type = Ops::Write, .req = req};

  write.setUuid(uuid);

  // std::cout << "hello_ll_write: Request UUID: " << uuid << std::endl;

  const auto data = capnp::messageToFlatArray(message);
  const auto bytes = data.asBytes();
  std::string payload(bytes.begin(), bytes.end());

  ws->send((char)Ops::Write + payload);

  std::cout << "hello_ll_write executed correctly: " << payload << std::endl;
}

static void hello_ll_unlink(fuse_req_t req, fuse_ino_t parent, const char *name) {
  // printf("Called .unlink\n");

  ::capnp::MallocMessageBuilder message;
  Unlink::Builder unlink = message.initRoot<Unlink>();

  unlink.setParent(parent);
  unlink.setName(name);

  std::string uuid = gen_uuid();
  requests[uuid] = {.type = Ops::Unlink, .req = req};

  unlink.setUuid(uuid);

  // std::cout << "hello_ll_unlink: Request UUID: " << uuid << std::endl;

  const auto data = capnp::messageToFlatArray(message);
  const auto bytes = data.asBytes();
  std::string payload(bytes.begin(), bytes.end());

  ws->send((char)Ops::Unlink + payload);

  std::cout << "unlink executed correctly: " << payload << std::endl;
}

static void hello_ll_rmdir(fuse_req_t req, fuse_ino_t parent, const char *name) {
  // printf("Called .rmdir\n");

  ::capnp::MallocMessageBuilder message;
  Rmdir::Builder rmdir = message.initRoot<Rmdir>();

  rmdir.setParent(parent);
  rmdir.setName(name);

  std::string uuid = gen_uuid();
  requests[uuid] = {.type = Ops::Rmdir, .req = req};

  rmdir.setUuid(uuid);

  // std::cout << "hello_ll_rmdir: Request UUID: " << uuid << std::endl;

  const auto data = capnp::messageToFlatArray(message);
  const auto bytes = data.asBytes();
  std::string payload(bytes.begin(), bytes.end());

  ws->send((char)Ops::Rmdir + payload);

  std::cout << "rmdir executed correctly: " << payload << std::endl;
}

/**
 * @brief
 *
 * @param req
 * @param parent -> uint64_t
 * @param name -> *char
 * @param mode -> uint64_t
 * @param rdev -> uint16_t
 */
static void hello_ll_mknod(fuse_req_t req, fuse_ino_t parent, const char *name, mode_t mode,
                           dev_t rdev) {
  // printf("Called .mknod\n");

  ::capnp::MallocMessageBuilder message;
  Mknod::Builder mknod = message.initRoot<Mknod>();

  mknod.setParent(parent);
  mknod.setName(name);
  mknod.setMode(mode);
  mknod.setRdev(rdev);

  std::string uuid = gen_uuid();
  requests[uuid] = {.type = Ops::Mknod, .req = req};

  mknod.setUuid(uuid);

  // std::cout << "hello_ll_mknod: Request UUID: " << uuid << std::endl;

  const auto data = capnp::messageToFlatArray(message);
  const auto bytes = data.asBytes();
  std::string payload(bytes.begin(), bytes.end());

  ws->send((char)Ops::Mknod + payload);

  std::cout << "hello_ll_mknod executed correctly: " << payload << std::endl;
}

/**
 * @brief
 *
 * @param req
 * @param parent -> uint64_t
 * @param name -> *char
 * @param mode -> uint64_t
 * @param fi -> {
 *             int 	flags
 *    unsigned int 	writepage
 *    unsigned int 	direct_io
 *    unsigned int 	keep_cache
 *    unsigned int 	flush
 *    unsigned int 	nonseekable
 *    unsigned int 	cache_readdir
 *    unsigned int 	padding
 *    uint64_t 	    fh
 *    uint64_t 	    lock_owner
 *    uint32_t 	    poll_events
 *    unsigned int 	noflush
 * }
 */
static void hello_ll_create(fuse_req_t req, fuse_ino_t parent, const char *name, mode_t mode,
                            struct fuse_file_info *fi) {
  struct fuse_entry_param e;

  // printf("Called .create\n");

  ::capnp::MallocMessageBuilder message;
  Create::Builder create = message.initRoot<Create>();
  Create::FuseFileInfo::Builder fuseFileInfo = create.initFi();

  create.setParent(parent);
  create.setName(name);
  create.setMode(mode);

  fillFileInfo(&fuseFileInfo, fi);

  std::string uuid = gen_uuid();
  requests[uuid] = {.type = Ops::Create, .req = req, .fi = fi};

  create.setUuid(uuid);

  // std::cout << "hello_ll_create: Request UUID: " << uuid << std::endl;

  const auto data = capnp::messageToFlatArray(message);
  const auto bytes = data.asBytes();
  std::string payload(bytes.begin(), bytes.end());

  ws->send((char)Ops::Create + payload);

  std::cout << "hello_ll_create executed correctly: " << payload << std::endl;
}

/**
 * @brief
 *
 * @param req
 * @param parent -> uint64_t
 * @param name -> *char
 * @param mode -> uint64_t
 */
static void hello_ll_mkdir(fuse_req_t req, fuse_ino_t parent, const char *name, mode_t mode) {
  // printf("Called .mkdir\n");

  ::capnp::MallocMessageBuilder message;
  Mkdir::Builder mkdir = message.initRoot<Mkdir>();

  mkdir.setParent(parent);
  mkdir.setName(name);
  mkdir.setMode(mode);

  std::string uuid = gen_uuid();
  requests[uuid] = {.type = Ops::Mkdir, .req = req};

  mkdir.setUuid(uuid);

  // std::cout << "hello_ll_mkdir: Request UUID: " << uuid << std::endl;

  const auto data = capnp::messageToFlatArray(message);
  const auto bytes = data.asBytes();
  std::string payload(bytes.begin(), bytes.end());

  ws->send((char)Ops::Mkdir + payload);

  std::cout << "hello_ll_mkdir executed correctly: " << payload << std::endl;
}

/**
 * @brief
 *
 * @param req
 * @param ino -> uint64_t
 * @param attr -> {
 *    uint16_t      st_dev
 *    uint64_t      st_ino
 *    uint64_t      st_mode
 *    uint16_t      st_nlink
 *             int  st_uid
 *             int  st_gid
 *    uint16_t      st_rdev
 *    long     int  st_size
 *    int64_t       st_atime
 *    int64_t       st_mtime
 *    int64_t       st_ctime
 *    uint64_t      st_blksize
 *    uint64_t      st_blocks
 * }
 * @param to_set -> int64_t
 * @param fi -> {
 *             int 	flags
 *    unsigned int 	writepage
 *    unsigned int 	direct_io
 *    unsigned int 	keep_cache
 *    unsigned int 	flush
 *    unsigned int 	nonseekable
 *    unsigned int 	cache_readdir
 *    unsigned int 	padding
 *    uint64_t 	    fh
 *    uint64_t 	    lock_owner
 *    uint32_t 	    poll_events
 *    unsigned int 	noflush
 * }
 */
static void hello_ll_setattr(fuse_req_t req, fuse_ino_t ino, struct stat *attr, int to_set,
                             struct fuse_file_info *fi) {
  ::capnp::MallocMessageBuilder message;
  Setattr::Builder setattr = message.initRoot<Setattr>();

  Setattr::FuseFileInfo::Builder fuseFileInfo = setattr.initFi();
  Setattr::Attr::Builder attributes = setattr.initAttr();

  Setattr::Attr::TimeSpec::Builder stAtime = attributes.initStAtime();
  Setattr::Attr::TimeSpec::Builder stMtime = attributes.initStMtime();

  setattr.setIno(ino);
  setattr.setToSet(to_set);

  attributes.setStDev(attr->st_dev);
  attributes.setStIno(attr->st_ino);
  attributes.setStMode(attr->st_mode);
  attributes.setStNlink(attr->st_nlink);
  attributes.setStUid(attr->st_uid);
  attributes.setStGid(attr->st_gid);
  attributes.setStRdev(attr->st_rdev);
  attributes.setStSize(attr->st_size);
  attributes.setStCtime(attr->st_ctime);
  attributes.setStBlksize(attr->st_blksize);
  attributes.setStBlocks(attr->st_blocks);

  // clang-format off
  #if defined(__APPLE__)
    stAtime.setTvSec(attr->st_atimespec.tv_sec);
    stAtime.setTvNSec(attr->st_atimespec.tv_nsec);
    stMtime.setTvSec(attr->st_mtimespec.tv_sec);
    stMtime.setTvNSec(attr->st_mtimespec.tv_nsec);
  #else
    stAtime.setTvSec(attr->st_atim.tv_sec);
    stAtime.setTvNSec(attr->st_atim.tv_nsec);
    stMtime.setTvSec(attr->st_mtim.tv_sec);
    stMtime.setTvNSec(attr->st_mtim.tv_nsec);
  #endif

  fillFileInfo(&fuseFileInfo, fi);

  std::string uuid = gen_uuid();
  requests[uuid] = {.type = Ops::Setattr, .req = req, .fi = fi};

  setattr.setUuid(uuid);

  // std::cout << "hello_ll_setattr: Request UUID: " << uuid << std::endl;

  const auto data = capnp::messageToFlatArray(message);
  const auto bytes = data.asBytes();
  std::string payload(bytes.begin(), bytes.end());

  ws->send((char)Ops::Setattr + payload);

  std::cout << "hello_ll_setattr executed correctly: "
            << payload << std::endl;
}

#ifdef __APPLE__
static void hello_ll_setxattr(fuse_req_t req, fuse_ino_t ino, const char *name, const char *value,
                              size_t size, int flags, uint32_t position) {

  ::capnp::MallocMessageBuilder message;
  Setxattr::Builder _setxattr = message.initRoot<Setxattr>();

  _setxattr.setIno(ino);
  _setxattr.setName(name);
  _setxattr.setValue(value);
  _setxattr.setSize(size);
  _setxattr.setFlags(flags);
  _setxattr.setPosition(position);

  std::string uuid = gen_uuid();
  requests[uuid] = {.type = Ops::Setxattr, .req = req};

  _setxattr.setUuid(uuid);

  // std::cout << "hello_ll_setxattr: Request UUID: " << uuid << std::endl;

  const auto data = capnp::messageToFlatArray(message);
  const auto bytes = data.asBytes();
  std::string payload(bytes.begin(), bytes.end());

  ws->send((char)Ops::Setxattr + payload);

  std::cout << "hello_ll_setxattr executed correctly: " << payload << std::endl;
}
#endif

// clang-format off
static const struct fuse_lowlevel_ops hello_ll_oper = {
    .lookup = hello_ll_lookup,
    .getattr = hello_ll_getattr,
    .setattr = hello_ll_setattr,
    .mknod = hello_ll_mknod,
    .mkdir = hello_ll_mkdir,
    .unlink = hello_ll_unlink,
    .rmdir = hello_ll_rmdir,
    .open = hello_ll_open,
    .read = hello_ll_read,
    .write = hello_ll_write,
    .readdir = hello_ll_readdir,
    #ifdef __APPLE__
      .setxattr = hello_ll_setxattr,
    #endif
    .create = hello_ll_create,
};
// clang-format on

int start_fs(int argc, char *argv[], wsclient::WSClient *wsc) {
  ws = wsc;

  struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
  struct fuse_chan *ch;
  char *mountpoint;
  int err = -1;

  if (fuse_parse_cmdline(&args, &mountpoint, NULL, NULL) != -1
      && (ch = fuse_mount(mountpoint, &args)) != NULL) {
    struct fuse_session *se;

    se = fuse_lowlevel_new(&args, &hello_ll_oper, sizeof(hello_ll_oper), NULL);
    if (se != NULL) {
      if (fuse_set_signal_handlers(se) != -1) {
        fuse_session_add_chan(se, ch);
        err = fuse_session_loop(se);
        fuse_remove_signal_handlers(se);
        fuse_session_remove_chan(ch);
      }
      fuse_session_destroy(se);
    }
    fuse_unmount(mountpoint, ch);
  }
  fuse_opt_free_args(&args);

  return err ? 1 : 0;
}