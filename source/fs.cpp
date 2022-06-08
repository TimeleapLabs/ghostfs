/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>
  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.
  gcc -Wall hello_ll.c `pkg-config fuse --cflags --libs` -o hello_ll
*/

#define FUSE_USE_VERSION 29

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse_lowlevel.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <uuid_v4.h>

// CAPNPROTO

#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <create.capnp.h>
#include <getattr.capnp.h>
#include <lookup.capnp.h>
#include <mkdir.capnp.h>
#include <mknod.capnp.h>
#include <open.capnp.h>
#include <read.capnp.h>
#include <readdir.capnp.h>
#include <setattr.capnp.h>
#include <write.capnp.h>

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

static int hello_stat(fuse_ino_t ino, struct stat *stbuf) {
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

  struct stat stbuf;

  // printf("Called .getattr\n");

  (void)fi;

  memset(&stbuf, 0, sizeof(stbuf));
  if (hello_stat(ino, &stbuf) == -1)
    fuse_reply_err(req, ENOENT);
  else
    fuse_reply_attr(req, &stbuf, 1.0);
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

  struct fuse_entry_param e;

  bool is_hello = strcmp(name, hello_name) == 0;
  bool is_user_file = strcmp(name, user_file_name) == 0;
  bool user_file_exists = strlen(user_file_name) > 0;

  std::string parent_path_name = parent == 1 ? "./root" : ino_to_path[parent];
  std::filesystem::path parent_path = std::filesystem::path(parent_path_name);
  std::filesystem::path file_path = parent_path / std::filesystem::path(name);

  if (!std::filesystem::exists(file_path)) {
    fuse_reply_err(req, ENOENT);
  } else {
    memset(&e, 0, sizeof(e));
    e.ino = path_to_ino[file_path];
    e.attr_timeout = 1.0;
    e.entry_timeout = 1.0;
    hello_stat(e.ino, &e.attr);

    fuse_reply_entry(req, &e);
  }
}

struct dirbuf {
  char *p;
  size_t size;
};

static void dirbuf_add(fuse_req_t req, struct dirbuf *b, const char *name, fuse_ino_t ino) {
  struct stat stbuf;
  size_t oldsize = b->size;
  b->size += fuse_add_direntry(req, NULL, 0, name, NULL, 0);
  b->p = (char *)realloc(b->p, b->size);
  memset(&stbuf, 0, sizeof(stbuf));
  stbuf.st_ino = ino;
  fuse_add_direntry(req, b->p + oldsize, b->size - oldsize, name, &stbuf, b->size);
}

#define min(x, y) ((x) < (y) ? (x) : (y))

static int reply_buf_limited(fuse_req_t req, const char *buf, size_t bufsize, off_t off,
                             size_t maxsize) {
  if (off < bufsize)
    return fuse_reply_buf(req, buf + off, min(bufsize - off, maxsize));
  else
    return fuse_reply_buf(req, NULL, 0);
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
  (void)fi;

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

  // Root
  if (ino == 1) {
    std::string path = "./root";

    struct dirbuf b;

    memset(&b, 0, sizeof(b));
    dirbuf_add(req, &b, ".", 1);
    dirbuf_add(req, &b, "..", 1);

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
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

    reply_buf_limited(req, b.p, b.size, off, size);
    free(b.p);
  } else {
    fuse_reply_err(req, ENOTDIR);
  }
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

  fillFileInfo(&fuseFileInfo, fi);

  if (ino != 2 && ino != 3) fuse_reply_err(req, EISDIR);
  // else if ((fi->flags & 3) != O_RDONLY)
  //   fuse_reply_err(req, EACCES);
  else
    fuse_reply_open(req, fi);
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

  assert(ino == 2 || ino == 3);

  if (ino == 2) {
    reply_buf_limited(req, hello_str, strlen(hello_str), off, size);
  } else {
    reply_buf_limited(req, user_file_str, strlen(user_file_str), off, size);
  }
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
  assert(ino == 3);

  // printf("Called .write\n");

  ::capnp::MallocMessageBuilder message;
  Write::Builder write = message.initRoot<Write>();
  Write::FuseFileInfo::Builder fuseFileInfo = write.initFi();

  write.setIno(ino);
  write.setBuf(buf);
  write.setSize(size);
  write.setOff(off);

  fillFileInfo(&fuseFileInfo, fi);

  strcpy(user_file_str, buf);

  if (false) {
    fuse_reply_err(req, 1);
  } else {
    fuse_reply_write(req, size);
  }
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
  struct fuse_entry_param e;

  // printf("Called .mknod\n");

  ::capnp::MallocMessageBuilder message;
  Mknod::Builder mknod = message.initRoot<Mknod>();

  mknod.setParent(parent);
  mknod.setName(name);
  mknod.setMode(mode);
  mknod.setRdev(rdev);

  strcpy(user_file_name, name);

  if (false)
    fuse_reply_err(req, ENOENT);
  else {
    memset(&e, 0, sizeof(e));
    e.ino = 3;
    e.attr_timeout = 1.0;
    e.entry_timeout = 1.0;
    hello_stat(e.ino, &e.attr);

    fuse_reply_entry(req, &e);
  }
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

  strcpy(user_file_name, name);

  if (false)
    fuse_reply_err(req, ENOENT);
  else {
    memset(&e, 0, sizeof(e));
    e.ino = 3;
    e.attr_timeout = 1.0;
    e.entry_timeout = 1.0;
    hello_stat(e.ino, &e.attr);

    fi->fh = 4;

    fuse_reply_create(req, &e, fi);
  }
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
  struct fuse_entry_param e;

  // printf("Called .mkdir\n");

  ::capnp::MallocMessageBuilder message;
  Mkdir::Builder mkdir = message.initRoot<Mkdir>();

  mkdir.setParent(parent);
  mkdir.setName(name);
  mkdir.setMode(mode);

  strcpy(user_file_name, name);

  if (false)
    fuse_reply_err(req, ENOENT);
  else {
    memset(&e, 0, sizeof(e));
    e.ino = 3;
    e.attr_timeout = 1.0;
    e.entry_timeout = 1.0;
    hello_stat(e.ino, &e.attr);

    fuse_reply_entry(req, &e);
  }
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

  setattr.setIno(ino);

  attributes.setStDev(attr->st_dev);
  attributes.setStIno(attr->st_ino);
  attributes.setStMode(attr->st_mode);
  attributes.setStNlink(attr->st_nlink);
  attributes.setStUid(attr->st_uid);
  attributes.setStGid(attr->st_gid);
  attributes.setStRdev(attr->st_rdev);
  attributes.setStSize(attr->st_size);
  attributes.setStAtime(attr->st_atime);
  attributes.setStMtime(attr->st_mtime);
  attributes.setStCtime(attr->st_ctime);
  attributes.setStBlksize(attr->st_blksize);
  attributes.setStBlocks(attr->st_blocks);

  setattr.setToSet(to_set);

  fillFileInfo(&fuseFileInfo, fi);

  // printf("Called .setattr\n");

  hello_ll_getattr(req, ino, fi);
}

// clang-format off
static struct fuse_lowlevel_ops hello_ll_oper = {
    .lookup = hello_ll_lookup,
    .getattr = hello_ll_getattr,
    .readdir = hello_ll_readdir,
    //.open = hello_ll_open,
    //.read = hello_ll_read,
    //.write = hello_ll_write,
    //.mknod = hello_ll_mknod,
    //.create = hello_ll_create,
    //.mkdir = hello_ll_mkdir,
    //.setattr = hello_ll_setattr
};
// clang-format on

int start_fs(int argc, char *argv[]) {
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