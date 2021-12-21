#include "catch.hpp"
#include "libutil.hpp"
#include <iostream>

TEST_CASE("dirfilesearch", "[util]") {
	std::string filename = "./tests/Directory";
	auto v = util::directorySearch(filename);
	REQUIRE(v.size() == 9);
}
