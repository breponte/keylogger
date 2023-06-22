# use g++ with C++98 support
CXX=g++
CXXFLAGS?=-Wall -pedantic -g -O0 -std=c++98
OUTFILES=key_logger.exe

all:
	$(CXX) $(CXXFLAGS) -o key_logger.exe ./scripts/logger.cpp

clean:
	rm -f $(OUTFILES) *.o