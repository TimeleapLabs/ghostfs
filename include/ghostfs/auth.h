#pragma once
#include <filesystem>
#include <string>

bool is_authenticated(std::string user_id);
bool authenticate(std::string token, std::string sub_directory, std::string user_id);
bool check_access(std::string root, std::string user_id, std::string path);
std::string add_token(std::string user, std::string token, int64_t retries);
std::filesystem::path normalize_path(std::string root, std::string user_id, std::string path);
std::filesystem::path normalize_path(std::string root, std::string user_id);
