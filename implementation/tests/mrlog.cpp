#include "libutil.hpp"
#include <catch2/catch.hpp>

TEST_CASE("mrlog", "[mrlog]") {
	mrlog::clearLog();
	mrlog::log("Hello");
	mrlog::error("{}", "error");
	// mrlog::clearLog();
}
