CXX = g++
CXXFLAGS = -Wall -Wextra

all: run_asa run_dfs

asa: ASA.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dfs: dfs.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

run_asa: asa
	./asa inputASA.txt outputASA.txt

run_dfs: dfs
	./dfs inputDFS.txt outputDFS.txt

clean:
	rm -f asa dfs

