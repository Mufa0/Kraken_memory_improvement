# the compiler: gcc for C program, define as g++ for C++
CXX= g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
CXXFLAGS = -Wall -fopenmp -O3

  # the build target executable:
PROGS = db_sort set_lcas classify make_seqid_to_taxid_map db_shrink databaseSplit
.PHONY: all install clean
all: $(PROGS)

install: $(PROGS)
		cp $(PROGS) $(KRAKEN_DIR)/

clean:
		rm -f $(PROGS) *.o

db_shrink: krakendb.o quickfile.o

db_sort: krakendb.o quickfile.o

set_lcas: krakendb.o quickfile.o krakenutil.o seqreader.o

classify: krakendb.o quickfile.o krakenutil.o seqreader.o

make_seqid_to_taxid_map: quickfile.o

databaseSplit: krakendb.o quickfile.o krakenutil.o seqreader.o

krakenutil.o: krakenutil.cpp krakenutil.hpp
		$(CXX) $(CXXFLAGS) -c krakenutil.cpp

krakendb.o: krakendb.cpp krakendb.hpp quickfile.hpp
		$(CXX) $(CXXFLAGS) -c krakendb.cpp

seqreader.o: seqreader.cpp seqreader.hpp quickfile.hpp
		$(CXX) $(CXXFLAGS) -c seqreader.cpp

quickfile.o: quickfile.cpp quickfile.hpp
		$(CXX) $(CXXFLAGS) -c quickfile.cpp
