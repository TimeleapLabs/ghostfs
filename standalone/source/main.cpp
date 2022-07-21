#include <ghostfs/fs.h>
#include <ghostfs/ghostfs.h>
#include <ghostfs/version.h>
#include <ghostfs/ws.h>
#include <ghostfs/wss.h>

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

auto main(int argc, char** argv) -> int {
  cxxopts::Options options("GhostFS", "One Ghosty FS");

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("r,root", "Root directory", cxxopts::value<std::string>())
    ("u,url", "Server connection URL", cxxopts::value<std::string>())
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
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (result["version"].as<bool>()) {
    std::cout << "GhostFS, version " << GHOSTFS_VERSION << std::endl;
    return 0;
  }

  if (result["server"].as<bool>()) {
    wsserver::WSServer wss(3444);
    std::string root = result["root"].as<std::string>();
    wss.start(root);

    return 0;
  } else if (result["client"].as<bool>()) {
    std::string url = result["url"].as<std::string>();
    wsclient::WSClient ws(url);
    return start_fs(argc, argv, &ws);

    // ghostfs::GhostFS ghostfs();
  }
}
