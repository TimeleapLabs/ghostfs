#define FUSE_USE_VERSION 29
#define _FILE_OFFSET_BITS 64

#include <fuse_lowlevel.h>
#include <ghostfs/ws.h>

#include <string>

int start_fs(char* executable, char* mountpoint, std::vector<std::string> options,
             wsclient::WSClient* wsc);

void process_response(uint8_t msg);
int hello_stat(fuse_ino_t ino, struct stat* stbuf);

extern std::map<uint64_t, std::string> ino_to_path;
extern std::map<std::string, uint64_t> path_to_ino;
extern uint64_t current_ino;

struct dirbuf {
  char* p;
  size_t size;
};

void dirbuf_add(fuse_req_t req, struct dirbuf* b, const char* name, fuse_ino_t ino);

enum class Ops : char {
  Auth = 1,
  Getattr = 2,
  Lookup = 3,
  Readdir = 4,
  Open = 5,
  Read = 6,
  Setattr = 7,
  Write = 8,
  Setxattr = 9,
  Create = 10,
  Mknod = 11,
  Mkdir = 12,
  Unlink = 13,
  Rmdir = 14,
  Rename = 15,
};

// Responses
void process_auth_response(std::string payload, wsclient::WSClient* wsc);
void process_getattr_response(std::string payload);
void process_lookup_response(std::string payload);
void process_readdir_response(std::string payload);
void process_open_response(std::string payload);
void process_read_response(std::string payload);
void process_setattr_response(std::string payload);
void process_write_response(std::string payload);
void process_setxattr_response(std::string payload);
void process_create_response(std::string payload);
void process_mknod_response(std::string payload);
void process_mkdir_response(std::string payload);
void process_unlink_response(std::string payload);
void process_rmdir_response(std::string payload);
void process_rename_response(std::string payload);

uint64_t get_parent_ino(uint64_t ino, std::string path);
