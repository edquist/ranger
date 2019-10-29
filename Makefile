CXX = g++
CXXFLAGS = -Wall -O3
CPPFLAGS = -std=c++11

ALL = set-lb-ub ranger ranger-explorer

all: $(ALL)

RANGER.COMP = $(CXX) $(CPPFLAGS) $(CXXFLAGS) $< ranger_impl.cpp -o $@

ranger: ranger.cpp ranger_impl.cpp ranger.h
	$(RANGER.COMP)

ranger-explorer: ranger-explorer.cpp ranger_impl.cpp ranger.h
	$(RANGER.COMP)

clean:
	$(RM) $(ALL)

