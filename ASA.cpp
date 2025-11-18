//ASA psuedocode
/*
 *
 build some type of node structure

 Node(){
 	needs to have following values
	start which is distance from start to node
	heuristic - undefined how to find it maybe euclidian distance formula?
	total which is just start+ hueristic
 }


 * s for starting
 * f for finishing node
 func ASA(s node, f node){
 	//initialize string vectors
	openList[start];	//nodes in queue
	closedList[];		//nodes whose paths have been explored
	path[] 			//to store optimal path from start to finish
	
	//intialize nodes
	s.start = 0; 				//distance from start to start is 0
	s.heuristic = hueristic(start, goal); 	
	s.total = s.start + s.heuristic;	//total value
	s.parent = null; 			//for backtracking
	
	all other nodes should have their starts be intialized to infinity 

	while openList is not empty:
		explore node at the top(should be smallest total value
		curr = node at the top

		if curr = goal{
			return path;
		}

		//move curr node from open to closed list

		//check nieghboring potential paths
		for each neiighbro of current:
			if neighbor in closedList;
			continue;

			//calculate neighbors t score
			neighbor.total = curr.start + 1 + neighbor.heuristic;

			if neighbor not in openList:
				add neighbor to openList in order

			//how can we ensure the best path exists?
 }
  
 */
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Graph {
private:
    int numNodes;
    int start;
    int finish;
    int roundsCount;
    vector <vector<int>> adjMatrix;
    vector <vector<int>> coordinates;
    vector <int> distance;	//distance relative from start
    vector <int> hueristic>;
    vector <int> totalVal;
    vector <int> openList;	//nodes in queue
    vector <int> closedList;	//nodes whose paths have been explored
    vector <int> path;		//to store optimal path solution

public:
    //constructor for Graph
    Graph(int s, int f){
	    start = s;
	    finish = f;
    }


    //shld we use eculidian formula (?)
    void compute_hueristic(int n)
    {
	
    }

    //figure out how to compute distance for each node
    void compute_distance(int n){
    
    }

    void compute_totalVal(int n){
    	totalVal[n] = hueristic[n] + distance[n];
    }


    void add_openList(int n){
    
    }

    void remove_openList(int n){
    
    }

    void add_closedList(int n){
    
    }
    //some type of merge sort to ensure openList is a priority queue
    void sort_openList(){
    
    }
    


// s for starting
// f for finishing node
void ASA(){
	
	//intialize values for starting node
	compute_hueristic(start);
	compute_totalVal(start);

	//add starting node to openlist
	openList.insert(s, hueristic[s]);
		
	while (!openList.empty()){
		/*
		explore node at the top(should be smallest total value
		curr = node at the top

		if curr = goal{
			return path;
		}

		//move curr node from open to closed list

		//check nieghboring potential paths
		for each neiighbro of current:
			if neighbor in closedList;
			continue;

			//calculate neighbors t score
			neighbor.total = curr.start + 1 + neighbor.heuristic;

			if neighbor not in openList:
				add neighbor to openList in order
		*/
	
    }

    void printResult(ofstream& outfile){
        for(int i = 0; i < path.size(); i++){
            outfile << path [i] << " -> ";
        }
        outfile << endl;
        return;
    }

};

int main(int argc, , char* argv[])
{
    ifstream inputFile(arv[1]);
    ofstream outfile(argv[2]);

    string firstline;
    int s;
    inputFile >> s;

    //graph wants start and finish node before constructed
    Graph g(1, 9);
    int i, j, d;

    // get edges from input file
    while(getline(inputFile, firstline){
	if (firstline  == "//coordinate location node"){
		break;
	}

	inputFile >> i >> j >> d;
	adjMatrix[i][j] = d;
        
    }

    //get coordinates
    while(getline(inputFile, firstline){
	if (firstline == "//end of file"){
	    break;
	}

	inpuFile >> d >> i >> j;
	coordinates[i][j] = d;

    }


    //run asa and put results in output file
    g.ASA();
    g.printResult(outfile);

    return 0;
}
