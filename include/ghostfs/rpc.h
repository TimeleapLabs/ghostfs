#pragma once

#include <iostream>
#include <string>

int start_rpc_server(std::string bind, int port, int auth_port, std::string root,
                     std::string suffix, std::string key_file, std::string cert_file);

int rpc_add_token(uint16_t port, std::string user, std::string token, int64_t retries);
int rpc_mount(uint16_t port, std::string user, std::string source, std::string destination);
int rpc_unmount(uint16_t port, std::string user, std::string destination);
