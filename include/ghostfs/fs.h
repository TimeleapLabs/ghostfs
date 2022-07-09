#define FUSE_USE_VERSION 29
#define _FILE_OFFSET_BITS 64

#include <fuse_lowlevel.h>
#include <ghostfs/ws.h>

#include <string>

int start_fs(int argc, char* argv[], wsclient::WSClient* wsc);
std::string gen_uuid();
void process_response(uint8_t msg);
int hello_stat(fuse_ino_t ino, struct stat* stbuf);

// Responses

void process_getattr_response(std::string payload);