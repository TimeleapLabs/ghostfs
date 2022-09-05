#pragma once

#include <iostream>
#include <string>

int start_rpc_server(std::string bind, int port, int auth_port, std::string root,
                     std::string suffix);