#include <ghostfs/ws.h>

#include <string>

int start_fs(int argc, char* argv[], wsclient::WSClient* wsc);
std::string gen_uuid();
void process_response(uint8_t msg);
