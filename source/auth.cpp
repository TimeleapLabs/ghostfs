
#include <ghostfs/uuid.h>

#include <filesystem>
#include <iterator>
#include <map>
#include <string>

struct User {
  bool authenticated;
  std::string sub_directory;
};

struct Token {
  std::string token;
  int64_t usable;
};

std::map<std::string, struct User> users;
std::map<std::string, struct Token> tokens;

bool is_authenticated(std::string user_id) {
  if (users.find(user_id) == users.end()) {
    return false;
  }

  return users[user_id].authenticated;
}

bool authenticate(std::string token, std::string sub_directory, std::string user_id) {
  /**
   * Add a dummy token
   */

  if (tokens.find("test") == tokens.end()) {
    tokens["test"] = {.token = "dummy", .usable = 1};
  }

  if (tokens.find(sub_directory) == tokens.end()) {
    return false;
  }

  struct Token *t = &tokens[sub_directory];

  if (t->token != token) {
    return false;
  }

  if (t->usable == 0) {
    return false;
  } else if (t->usable > 0) {  // pass -1 to allow infinite use
    t->usable--;
  }

  struct User user = {.authenticated = true, .sub_directory = sub_directory};
  users[user_id] = user;

  return true;
}

bool check_access(std::string root, std::string user_id, std::string path) {
  std::filesystem::path user_root = std::filesystem::path(root) / users[user_id].sub_directory;

  auto const root_can = std::filesystem::canonical(user_root);
  auto const path_can = std::filesystem::canonical(path);

  auto itr = std::search(path_can.begin(), path_can.end(), root_can.begin(), root_can.end());
  return itr == path_can.begin();
}

std::filesystem::path normalize_path(std::string root, std::string user_id, std::string path) {
  return std::filesystem::path(root) / users[user_id].sub_directory / path;
}

std::filesystem::path normalize_path(std::string root, std::string user_id) {
  return std::filesystem::path(root) / users[user_id].sub_directory;
}
