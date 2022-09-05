#define FUSE_USE_VERSION 29
#define _FILE_OFFSET_BITS 64

#include <fuse_lowlevel.h>
#include <ghostfs/ws.h>

#include <string>

int start_fs(char* executable, char* mountpoint, std::vector<std::string> options,
             wsclient::WSClient* wsc, std::string host, std::string user, std::string token);

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
  Auth = 1
};

// Responses
void process_auth_response(std::string payload, wsclient::WSClient* wsc);

uint64_t get_parent_ino(uint64_t ino, std::string path);
