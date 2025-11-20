/*     DFS Pseudocode

FUNCTION DFS(int u)
// All nodes already initialized to white (unvisited)

// If node already visited, skip
IF color[u] == gray OR color[u] == red:
	return
END IF

// Set node to visited
color[u] = gray

FOR v = 0 to number of nodes:
	IF graph[u][v] == 1:
		DFS(v)
	END IF
END FOR

// Set node to fully discovered
color[u] = red	

return

*/


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


class Graph {

    private:
    int n; // number of nodes
    vector<vector<int>> g;// adjacency matrix
    vector<string> color; // color
    vector<int> parent; // parent
    vector<int> result; // result from DFS

    public:

    Graph(int n): 
    n(n),
    g(n, vector<int>(n,0)),
    color(n, "white"),
    parent(n, -1){}

    void dfs(int u){
        // If node already visited or fully discovered, return
        if(color[u] == "gray" || color[u] == "red"){
            return;
        }

        // Set node to visited
        color[u] = "gray";
        result.push_back(u);



        // Search for neighbors v of node u and run DFS on them
        for(int v = 0; v < n; v++){
            if(g[u][v] == 1){
                dfs(v);
            }
        }

        // Set node to fully discovered; all of u's neighbors will have been visited after the for loop
        color[u] = "red";
        return;

    }


    // add edge to graph
    void addEdge(int u, int v){
        g[u][v] = 1;
    }

    // print result of dfs
    void printResult(ofstream& outfile){
        for(int i = 0; i < result.size(); i++){
            outfile << result[i] << " ";
        }

        outfile << endl;

        return;
    }



};

 class Edge{

        private:
        int v; // destination node
        int weight; // weight of edge
       

        public:

        Edge(int v, int weight):
        v(v),
        weight(weight){}     

    };


int main(int argc, char* argv[]){

    if(argc != 3){
        cout << "Incorrect number of arguments. Must provide input and output file." << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);

    if(!infile){
        cout << "Could not open input file." << endl;
        return 1;
    }

    if(!outfile){
        cout << "Could not open output file." << endl;
        return 1;
    }

    // get number of nodes from top of input file
    int s;
    infile >> s;
    infile.ignore();
    Graph g(s);
    int i, j, k;

    vector<vector<Edge>> edges(s); // vector of edges for each node

    string line;
    while(getline(infile, line)){
    istringstream iss(line);

    iss >> i >> j;
    
    if(iss >> k){
        // there is a weight
        g.addEdge(i, j);
        edges[i].push_back({j, k});
    } else {

        // no weight, just add edge
        g.addEdge(i, j);
        edges[i].push_back({j, 0});
    }
    
    cout << "Added edge " << i << " -> " << j << endl;
}

    // run dfs and put results in output file
    g.dfs(0);
    g.printResult(outfile);






    return 0;


}