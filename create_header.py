import sys

args = sys.argv

FILENAME = "libutil.hpp"

file = open(FILENAME, 'w')

HEADER_PROTECTION = [
	"#ifdef " + "LIBUTIL_HPP",
	"# define " + "LIBUTIL_HPP",
	"#endif /* " + "LIBUTIL_HPP" + " */"
]

file.write(HEADER_PROTECTION[0] + "\n")
file.write(HEADER_PROTECTION[1] + "\n")

for header in args[1:]:
	with open(header, 'r') as f:
		file.write(f.read())

file.write(HEADER_PROTECTION[2] + "\n")
file.close()
