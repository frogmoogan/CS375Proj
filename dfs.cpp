/*     DFS Pseudocode

FUNCTION DFS(int u)

// All nodes already initialized to white (unvisited)

// If node already visited, skip

IF color[u] == gray OR color[u] == red: return false;
IF u == goal: return true

// Set node to visited
color[u] = gray

FOR each v in adj[u]:
parent[v] = u
IF DFS(v): return true
END FOR

// Set node to fully discovered
color[u] = red	
return false;

*/



#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// graph class to store graph info
class Graph {

    private:
    int n; // number of nodes
    int dest; // destination node
    vector<vector<int>> g;// adjacency list
    vector<string> color; // color
    
    vector<int> result; // result from DFS

    public:

    vector<int> parent; // parent
    // graph constructor

    Graph(int n, int dest): 
    n(n),
    dest(dest),
    g(n),
    color(n, "white"),
    parent(n, -1){}

    // depth first search function

    bool dfs(int u){
        // If node already visited or fully discovered, return
        if(color[u] == "gray" || color[u] == "red"){
            return false;
        }
        if(u == dest){
            return true;
        

        }

        // Set node to visited
        color[u] = "gray";

        // Search for neighbors v of node u and run DFS on them
        for(int v = 0; v < g[u].size(); v++){
                int neighbor = g[u][v];

                if(color[neighbor] == "white"){
                parent[neighbor] = u;
                if(dfs(neighbor)){
                    return true;
                }
            }

        }

        // Set node to fully discovered; all of u's neighbors will have been visited after the for loop
        color[u] = "red";
        return false;

    }


    // add edge to graph
    void addEdge(int u, int v){
        g[u].push_back(v);
        // Push back (v,u) as well for undirected graph
        g[v].push_back(u);
    }

    // print result of dfs
    void printResult(ofstream& outfile){
        vector<int> path;
        int current = dest;
        while(current != -1){
            path.push_back(current);
            current = parent[current];
        }

        for(int i = path.size()-1; i > -1; i--){
            outfile << path[i] << " ";
        }

        outfile << endl;

        return;
    }



};

// edge class to store edge info
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

    // check if correct number of arguments provided
    if(argc != 3){
        cout << "Incorrect number of arguments. Must provide input and output file." << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);

    // check if input file is valid
    if(!infile){
        cout << "Could not open input file." << endl;
        return 1;
    }

    // check if output file is valid
    if(!outfile){
        cout << "Could not open output file." << endl;
        return 1;
    }

    // get number of nodes from top of input file
    int s;
    infile >> s;
    infile.ignore();
    Graph g(s, 23);
    int i, j, k;

    vector<vector<Edge>> edges(s); // vector of edges for each node

    // get info from input file
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
    
    // print added edges to make sure info stored correctly
    /*cout << "Added edge " << i << " -> " << j << endl;*/
}

    // run dfs and put results in output file
    g.dfs(0);
    g.printResult(outfile);






    return 0;


}