#define FUSE_USE_VERSION 29
#define _FILE_OFFSET_BITS 64

#include <fuse_lowlevel.h>
#include <ghostfs/ws.h>

#include <string>

int start_fs(int argc, char* argv[], wsclient::WSClient* wsc);
std::string gen_uuid();
void process_response(uint8_t msg);
int hello_stat(fuse_ino_t ino, struct stat* stbuf);
std::map<uint64_t, std::string> ino_to_path;
std::map<std::string, uint64_t> path_to_ino;
std::string ROOT;

struct dirbuf {
  char* p;
  size_t size;
};

void dirbuf_add(fuse_req_t req, struct dirbuf* b, const char* name, fuse_ino_t ino);

// Responses
void process_getattr_response(std::string payload);
void process_readdir_response(std::string payload);