#include <doctest/doctest.h>
#include <ghostfs/ghostfs.h>
#include <ghostfs/version.h>

#include <string>

// TEST_CASE("GhostFS") {
//   using namespace ghostfs;

//   GhostFS ghostfs("Tests");

//   CHECK(ghostfs.greet(LanguageCode::EN) == "Hello, Tests!");
//   CHECK(ghostfs.greet(LanguageCode::DE) == "Hallo Tests!");
//   CHECK(ghostfs.greet(LanguageCode::ES) == "¡Hola Tests!");
//   CHECK(ghostfs.greet(LanguageCode::FR) == "Bonjour Tests!");
// }

TEST_CASE("GhostFS version") {
  static_assert(std::string_view(GHOSTFS_VERSION) == std::string_view("1.0"));
  CHECK(std::string(GHOSTFS_VERSION) == std::string("1.0"));
}
