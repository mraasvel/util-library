#include "libutil.hpp"
#include <catch2/catch.hpp>
#include <limits>
#include <vector>

namespace __UTIL_TEST__ {

template <typename T>
void testLimits() {
	const std::vector<T> values = {
		std::numeric_limits<T>::max(),
		std::numeric_limits<T>::min(),
		0,
	};

	for (const T& val : values) {
		SECTION("itoa(" + std::to_string(val) + ");") {
			REQUIRE(util::itoa(val) == std::to_string(val));
		}
	}
}

TEST_CASE("itoa limit") {
	testLimits<int>();
	testLimits<long>();
	testLimits<unsigned long>();
	testLimits<unsigned int>();
}

TEST_CASE("itoa basic") {
	const std::vector<int> basic_tests = {
		-1, 1, 100, -100, 1234, -1234
	};

	for (int value : basic_tests) {
		SECTION("itoa(" + std::to_string(value) + ");") {
			REQUIRE(util::itoa(value) == std::to_string(value));
		}
	}
}

TEST_CASE("itoa base") {
	const std::vector<std::pair<std::pair<int, int>, std::string>> tests = {
		std::make_pair(std::make_pair(5, 2), "101"),
		std::make_pair(std::make_pair(1234, 16), "4D2"),
		std::make_pair(std::make_pair(1234, 8), "2322"),
		std::make_pair(std::make_pair(-1, 16), "-1"),
	};

	for (const auto& testcase : tests) {
		SECTION("itoa(" + std::to_string(testcase.first.first) + ", " + std::to_string(testcase.first.second) + ");") {
			REQUIRE(util::itoa(testcase.first.first, testcase.first.second) == testcase.second);
		}
	}
}

}
