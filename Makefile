CXX = g++
CXXFLAGS = -Wall -O3

ALL = set-lb-ub ranger ranger-explorer

all: $(ALL)

ranger: ranger.cpp ranger_impl.cpp ranger.h
	$(CXX) $(CXXFLAGS) ranger.cpp ranger_impl.cpp -o $@

ranger-explorer: ranger-explorer.cpp ranger_impl.cpp ranger.h
	$(CXX) $(CXXFLAGS) ranger-explorer.cpp ranger_impl.cpp -o $@

clean:
	$(RM) $(ALL)

