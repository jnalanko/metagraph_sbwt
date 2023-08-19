INCLUDEPATHS=-I sdsl-lite/build/include/ -I sdsl-lite/build/external/libdivsufsort/include
LIBS=-lsdsl -ldivsufsort -ldivsufsort64 -fopenmp
LIBPATHS=-L sdsl-lite/build/lib/ -L sdsl-lite/build/external/libdivsufsort/lib/

all:
	g++ main.cpp sequence_graph.cpp -o main $(LIBPATHS) $(INCLUDEPATHS) $(LIBS) -std=c++17 -g -O3