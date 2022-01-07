#include "libutil.hpp"
#include <catch2/catch.hpp>

TEST_CASE("mrlog", "[mrlog]") {
	// mrlog::log("Hello\n");
	mrlog::log("H {}\n", 1234);
}
