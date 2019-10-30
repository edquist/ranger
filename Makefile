CXX = g++
CXXFLAGS = -Wall -O3
CPPFLAGS = -std=c++11

ALL = set-lb-ub ranger-tests ranger-explorer

all: $(ALL)

RANGER.HDRS = ranger.h ranger_ostream.h
RANGER.SRCS = ranger_impl.cpp ranger_iterator_impl.cpp ranger_ostream.cpp
RANGER.COMP = $(CXX) $(CPPFLAGS) $(CXXFLAGS) $< $(RANGER.SRCS) -o $@

ranger-tests: ranger-tests.cpp $(RANGER.SRCS) $(RANGER.HDRS)
	$(RANGER.COMP)

ranger-explorer: ranger-explorer.cpp $(RANGER.SRCS) $(RANGER.HDRS)
	$(RANGER.COMP)

test: ranger-tests
	@if ./ranger-tests | diff -q - test-out.txt; then \
		echo OK; else echo FAIL; fi

clean:
	$(RM) $(ALL)

