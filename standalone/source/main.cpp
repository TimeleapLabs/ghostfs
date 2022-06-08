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
  cxxopts::Options options("MyProgram", "One line description of MyProgram");

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("s,server", "Run in server mode")  // a bool parameter
    ("g,ghost", "Run in ghost mode")
    ("c,client", "Run in client mode");

  // options.add_options()
  //   ("h,help", "Show help")
  //   ("v,version", "Print the current version number")
  //   ("n,name", "Name to greet", cxxopts::value(name)->default_value("World"))
  //   ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  // ;

  // clang-format on

  auto result = options.parse(argc, argv);

  std::cout << "UUID: " << gen_uuid() << std::endl;

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
    wss.start();

    return 0;
  } else if (result["client"].as<bool>()) {
    wsclient::WSClient ws("http://localhost:3444");
    ws.prompt();

    return 0;
  } else if (result["ghost"].as<bool>()) {
    return start_fs(argc, argv);

    // ghostfs::GhostFS ghostfs();
  }
}
