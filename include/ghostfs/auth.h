#pragma once
#include <filesystem>
#include <map>
#include <string>

bool authenticate(std::string token, std::string user_id);
bool check_access(std::string root, std::string user_id, std::string path);

std::string add_token(std::string user, std::string token, int64_t retries);

std::filesystem::path normalize_path(std::string root, std::string user_id, std::string path);
std::filesystem::path normalize_path(std::string root, std::string user_id);

void soft_mount(std::string user, std::string src, std::string dest);
void soft_unmount(std::string user, std::string dest);
std::map<std::string, std::string>* get_user_mounts(std::string user);