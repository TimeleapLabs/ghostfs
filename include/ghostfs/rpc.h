#pragma once

#include <iostream>
#include <string>

int start_rpc_server(std::string bind, int port, int auth_port, std::string root,
                     std::string suffix);

int rpc_add_token(uint16_t port, std::string user, std::string token, int64_t retries);