#include "libutil.hpp"
#include <catch2/catch.hpp>

template <typename C>
static void printContainer(const C& c) {
	std::cout << "container:";
	for (const auto& val : c) {
		std::cout << ' ' << val;
	}
	std::cout << std::endl;
}

template <typename C,
	typename std::enable_if<std::is_integral<typename C::value_type>::value, bool>::type = true>
void randomContainer(C& c, size_t n) {
	while (n-- > 0) {
		c.emplace_back(rand());
	}
}

template <typename Sorter, typename Container, typename Compare>
static void sortTest(Sorter sort, Container c, Compare comp) {
	sort(c.begin(), c.end(), comp);
	REQUIRE(std::is_sorted(c.begin(), c.end(), comp));
}

TEST_CASE("merge sort", "[sort]") {
	srand(time(0));
	std::vector<int> v;
	randomContainer(v, 100);
	sortTest(util::mergesort<std::vector<int>::iterator, std::less<int>>, v, std::less<int>());
}