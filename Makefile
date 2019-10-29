CXX = g++
CXXFLAGS = -Wall -O3
CPPFLAGS = -std=c++11

ALL = set-lb-ub ranger-tests ranger-explorer

all: $(ALL)

RANGER.COMP = $(CXX) $(CPPFLAGS) $(CXXFLAGS) $< ranger_impl.cpp -o $@

ranger-tests: ranger-tests.cpp ranger_impl.cpp ranger.h
	$(RANGER.COMP)

ranger-explorer: ranger-explorer.cpp ranger_impl.cpp ranger.h
	$(RANGER.COMP)

test: ranger-tests
	@if ./ranger-tests | diff -q - test-out.txt; then \
		echo OK; else echo FAIL; fi

clean:
	$(RM) $(ALL)

