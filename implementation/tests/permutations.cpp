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

template <typename T>
static void testRange(T first, T last) {
	util::Permutations<T> permutations{first, last};
	std::vector<T> ref;
	while (first != last) {
		ref.emplace_back(first);
		++first;
	}
	ref.emplace_back(last);

	bool has_permutation = true;
	for (const auto& perm : permutations) {
		REQUIRE(has_permutation);
		REQUIRE(perm == ref);
		has_permutation = std::next_permutation(ref.begin(), ref.end());
	}
}

TEST_CASE("replacement permutations", "[permutations]") {
	testRange(0, 3);
}