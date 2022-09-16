
#include <ghostfs/uuid.h>

#include <algorithm>
#include <filesystem>
#include <iterator>
#include <map>
#include <string>

struct User {
  std::string sub_directory;
  std::map<std::string, std::string> soft_mounts;
};

struct Token {
  std::string token;
  int64_t usable;
};

std::map<std::string, struct User> users;
std::map<std::string, struct Token> tokens;

std::string random_token() {
  std::string uuid = gen_uuid();
  std::replace(uuid.begin(), uuid.end(), '-', uuid[3]);
  return uuid;
}

std::string add_token(std::string user, std::string token, int64_t retries) {
  std::string token_to_add = token.length() ? token : random_token();

  tokens[user] = {.token = token_to_add, .usable = retries};

  if (not users.contains(user)) {
    users[user] = {.sub_directory = user};
  }

  return token_to_add;
}

void soft_mount(std::string user, std::string src, std::string dest) {
  if (users.contains(user)) {
    users[user].soft_mounts[dest] = src;
  }
}

void soft_unmount(std::string user, std::string dest) {
  if (users.contains(user) and users[user].soft_mounts.contains(dest)) {
    users[user].soft_mounts.erase(dest);
  }
}

std::map<std::string, std::string>* get_user_mounts(std::string user) {
  return &users[user].soft_mounts;
}

bool authenticate(std::string token, std::string user) {
  if (not tokens.contains(user)) {
    return false;
  }

  struct Token* t = &tokens[user];

  if (t->token != token) {
    return false;
  }

  if (t->usable == 0) {
    return false;
  } else if (t->usable > 0) {  // pass -1 to allow infinite use
    t->usable--;
  }

  return true;
}

bool check_access(std::string root, std::string user_id, std::string path) {
  std::filesystem::path user_root = std::filesystem::path(root) / users[user_id].sub_directory;

  auto const root_can = std::filesystem::canonical(user_root);
  auto const path_can = std::filesystem::canonical(path);

  auto itr = std::search(path_can.begin(), path_can.end(), root_can.begin(), root_can.end());
  return itr == path_can.begin();
}

std::filesystem::path normalize_path(std::string root, std::string user_id) {
  return std::filesystem::path(root) / users[user_id].sub_directory;
}

std::filesystem::path normalize_path(std::string root, std::string user_id, std::string path) {
  if (!path.length()) {
    return normalize_path(root, user_id);
  }
  return std::filesystem::path(root) / users[user_id].sub_directory / path;
}
