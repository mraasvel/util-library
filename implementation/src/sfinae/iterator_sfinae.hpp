#ifndef ITERATOR_SFINAE
#define ITERATOR_SFINAE

#include <type_traits>
#include <iterator>

namespace util {

template <typename Iterator, typename Tag>
using RequireIterator = typename std::enable_if<std::is_convertible<
	typename std::iterator_traits<Iterator>::iterator_category, Tag>::value, bool>::type;

template <typename InputIterator>
using RequireInputIterator = RequireIterator<InputIterator, std::input_iterator_tag>;

template <typename RandomAccessIterator>
using RequireRandomAccessIterator = RequireIterator<RandomAccessIterator, std::random_access_iterator_tag>;

}

#endif /* ITERATOR_SFINAE */
