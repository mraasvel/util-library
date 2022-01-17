#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include <iostream> // REMOVE

namespace util {

	namespace Detail {

	template <typename InputIterator, typename OutputIterator, typename Compare>
	void merge(InputIterator first1, InputIterator last1, 
				InputIterator first2, InputIterator last2,
				OutputIterator out, Compare comp) {
		while (first1 != last1 || first2 != last2) {
			if (first1 == last1) {
				*out++ = *first2++;
			} else if (first2 == last2) {
				*out++ = *first1++;
			} else if (comp(*first1, *first2)) {
				*out++ = *first1++;
			} else {
				*out++ = *first2++;
			}
		}
	}

	}

template <typename RandomAcessIterator,
	RequireRandomAccessIterator<RandomAcessIterator> = true>
void mergesort(RandomAcessIterator first, RandomAcessIterator last) {
	mergesort(first, last, std::less<typename RandomAcessIterator::value_type>());
}

template <typename RandomAcessIterator, typename Compare,
	RequireRandomAccessIterator<RandomAcessIterator> = true>
void mergesort(RandomAcessIterator first, RandomAcessIterator last, Compare comp) {
	auto dist = std::distance(first, last);
	if (dist == 1) {
		return;
	}
	RandomAcessIterator midpoint = first + dist / 2;

	// 2 branches
	mergesort(first, midpoint, comp);
	mergesort(midpoint, last, comp);

	std::vector<typename RandomAcessIterator::value_type> v;
	v.reserve(dist);
	// Merging = linear in dist(first, last)
	Detail::merge(first, midpoint, midpoint, last, std::back_inserter(v), comp);
	// Copying = linear in dist(first, last)
	std::copy(v.begin(), v.end(), first);
}

}

#endif /* MERGESORT_HPP */
