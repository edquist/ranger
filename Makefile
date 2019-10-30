CXX = g++
CXXFLAGS = -Wall -O3
CPPFLAGS = -std=c++11

RANGER = ranger-tests ranger-explorer ranger-explorer2
ALL = set-lb-ub $(RANGER)

all: $(ALL)

RANGER.HDRS = ranger.h ranger_ostream.h ranger_persist.h
RANGER.SRCS = ranger_impl.cpp ranger_iterator_impl.cpp ranger_ostream.cpp \
              stl_string_utils.cpp ranger_persist.cpp
RANGER.COMP = $(CXX) $(CPPFLAGS) $(CXXFLAGS) $< $(RANGER.SRCS) -o $@

$(RANGER): %: %.cpp $(RANGER.SRCS) $(RANGER.HDRS)
	$(RANGER.COMP)

test: ranger-tests
	@if ./ranger-tests | diff -q - test-out.txt; then \
		echo OK; else echo FAIL; fi

clean:
	$(RM) $(ALL)

