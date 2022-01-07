#include <catch2/catch.hpp>
#include "libutil.hpp"
#include <vector>
#include <utility>

namespace __UTIL_TEST__ {

typedef std::pair<std::string, std::string> InputType;
typedef std::vector<std::string> ResultType;
typedef std::pair<InputType, ResultType> TestCase;

TEST_CASE("String Split", "[string]") {
	std::vector<TestCase> testcases = {
		TestCase(InputType("1", " "), {"1"}),
		TestCase(InputType("", " "), {}),
		TestCase(InputType("1 2", " "), {"1", "2"}),
		TestCase(InputType(" 1 2 ", " "), {"1", "2"}),
		TestCase(InputType(" ", " "), {}),
		TestCase(InputType(" 1\t2 ", " \t"), {"1", "2"}),
	};

	for (const TestCase& testcase : testcases) {
		SECTION("split(\"" + testcase.first.first + "\", \"" + testcase.first.second + "\");") {
			REQUIRE(util::stringSplit(testcase.first.first, testcase.first.second) == testcase.second);
		}
	}
}

}
