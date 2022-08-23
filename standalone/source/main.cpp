#include <ghostfs/fs.h>
#include <ghostfs/ghostfs.h>
#include <ghostfs/version.h>
#include <ghostfs/ws.h>
#include <ghostfs/wss.h>

#include <cxxopts.hpp>
#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>

auto main(int argc, char** argv) -> int {
  cxxopts::Options options("GhostFS", "One Ghosty FS");

  std::string default_root = std::filesystem::path(getenv("HOME")) / ".ghostfs" / "root";

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("b,bind", "Bind IP address", cxxopts::value<std::string>()->default_value("127.0.0.1"))
    ("p,port", "Server port", cxxopts::value<uint16_t>()->default_value("3444"))
    ("P,auth-port", "Server auth port", cxxopts::value<uint16_t>()->default_value("3445"))
    ("r,root", "Root directory", cxxopts::value<std::string>()->default_value(default_root))
    ("S,suffix", "User data subdirectory suffix", cxxopts::value<std::string>()->default_value(""))
    ("u,url", "Server connection URL", cxxopts::value<std::string>())
    ("o,options", "Fuse mount options", cxxopts::value<std::vector<std::string>>())
    ("U,user", "Username (GhostFS subdirectory)", cxxopts::value<std::string>())
    ("t,token", "Authentication token", cxxopts::value<std::string>())
    ("s,server", "Run in server mode")  // a bool parameter
    ("c,client", "Run in client mode");

  // options.add_options()
  //   ("h,help", "Show help")
  //   ("v,version", "Print the current version number")
  //   ("n,name", "Name to greet", cxxopts::value(name)->default_value("World"))
  //   ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  // ;

  // clang-format on

  auto result = options.parse(argc, argv);

  // std::cout << "UUID: " << gen_uuid() << std::endl;

  if (result["help"].as<bool>()) {
    // std::cout << options.help() << std::endl;
    return 0;
  }

  if (result["version"].as<bool>()) {
    // std::cout << "GhostFS, version " << GHOSTFS_VERSION << std::endl;
    return 0;
  }

  if (result["server"].as<bool>()) {
    std::string root = result["root"].as<std::string>();
    std::string bind = result["bind"].as<std::string>();
    std::string suffix = result["suffix"].as<std::string>();

    uint16_t port = result["port"].as<uint16_t>();
    uint16_t auth_port = result["auth-port"].as<uint16_t>();

    wsserver::WSServer wss(port, auth_port, bind, root, suffix);
    return wss.start();

    return 0;
  } else if (result["client"].as<bool>()) {
    std::string url = result["url"].as<std::string>();
    std::string user = result["user"].as<std::string>();
    std::string token = result["token"].as<std::string>();
    std::vector<std::string> options = result["options"].as<std::vector<std::string>>();

    wsclient::WSClient ws(url, user, token);

    return start_fs(argv[0], argv[1], options, &ws);

    // ghostfs::GhostFS ghostfs();
  }
}
