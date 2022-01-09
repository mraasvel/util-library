#include "libutil.hpp"
#include <catch2/catch.hpp>

template <typename Container>
void printPerm(const Container& c) {
	std::cout << "Permutation:";
	for (const auto& value : c) {
		std::cout << ' ' << value;
	}
	std::cout << std::endl;
}

TEST_CASE("replacement permutations", "[permutations]") {
	int first = 0;
	int last = 3;
	// std::size_t n = 3;

	// int setsize = last - first + 1;
	for (const auto& perm : util::Permutations<int>{first, last}) {
		printPerm(perm);
	}
}