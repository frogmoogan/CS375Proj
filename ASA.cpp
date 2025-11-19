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

#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
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
    vector <int> hueristic;
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

    void compute_hueristic(int n)
    {
	double x1, x2, y1, y2;

	for (int i = 0; i < coordinates.size(); i++){
		for (int j = 0; j < coordinates.size(); j++){	
			if (coordinates[i][j] == n){
				x1 = i;
				y1 = j;
			}

			if (coordinates[i][j] == finish){
				x2 = i;
				y2 = j;
			}
		}
	}
	//calculate using euclidean distance
	hueristic[n] = sqrt(pow((x1-x2), 2) + pow ((y1-y2),2));
    }

    //setter functions
    void initMatrices(int n) {
    	numNodes = n;
    	adjMatrix.assign(n, vector<int>(n, 0));
    	coordinates.assign(n, vector<int>(n, 0));
    }


    void setEdge(int i, int j, int weight) {
    	adjMatrix[i][j] = weight;
    }

    void setCoordinate(int n, int x, int y) {
    	coordinates[x][y] = n;
}







    void compute_distance(int n){
    	int tempdist = 1000;

    	//case direct neigbor
    	if (adjMatrix[n][start] > 0){
		distance[n] = adjMatrix[n][start];
	}
	//case not direct neighbor
	else{
		//iterate through row and update tempdist if it is smaller
		for (int i = 1; i <adjMatrix.size(); i++){
			if (adjMatrix[n][i] + distance[i] > 0 ){
				if (adjMatrix[n][i] < tempdist){
					tempdist = adjMatrix[n][i] + distance[i];
				}
			}
		}
	}
    }

    void compute_totalVal(int n){
    	totalVal[n] = hueristic[n] + distance[n];
    }

    void remove_openList(int n){
    	for (int i = 0; i < openList.size(); i++){
		if (openList[i] == n){
			openList.erase(openList.begin() + i);
			return;
		}
	}
    }

    //check if closedList has this node
    bool closedListsearch(int n){
    	for (int i = 0; i <closedList.size(); i++){
		if (closedList[i] == n){
			return true;
		}
	}
	//did not find element
	return false;
    }
    //some type of merge sort to ensure openList is a priority queue
    void sort_openList(){
    	sort(openList.begin(), openList.end(), [&](int a, int b) {
             return totalVal[a] < totalVal[b];
         });
}
    


// s for starting
// f for finishing node
void ASA(){
	
	//intialize values for starting node
	compute_hueristic(start);
	compute_distance(start);
	compute_totalVal(start);

	//add starting node to openlist
	openList.push_back(start);
		
	int curr;
	while (!openList.empty()){
		curr = openList.front();
		path.push_back(curr);

		if (curr == finish){
			return;
		}

		//move curr node from open to closed list
		remove_openList(curr);
		closedList.push_back(curr);

		//check neighboring potential paths of curr
		for (int i = 0; i < adjMatrix.size(); i++){
			if (adjMatrix[curr][i] > 0){
				openList.push_back(i);
			}
		}

		//make sure list is sorted b4 proceeding
		sort_openList();
	
		//for each neighbor of current:
		for (int i = 0; i < openList.size();i++){
			if (closedListsearch(openList[i])){
				continue;	
			}

			//claculate neighbors t score
			compute_distance(i);
			compute_hueristic(i);
			compute_totalVal(i);
			
		}
				
				
    }
}

    void printResult(ofstream& outfile){
        for(int i = 0; i < path.size(); i++){
            outfile << path [i] << " -> ";
        }
        outfile << endl;
        return;
    }

};

int main(int argc, char* argv[])
{
    ifstream inputFile(argv[1]);
    ofstream outfile(argv[2]);

    string firstline;
    int s;
    inputFile >> s;


    //graph wants start and finish node before constructed
    Graph g(1, 9);
    g.initMatrices(s);
    int i, j, d;

    // get edges from input file
    while(getline(inputFile, firstline)){
	if (firstline  == "//coordinate location node"){
		break;
	}

	inputFile >> i >> j >> d;
        g.setEdge(i,j,d); 
    }

    //get coordinates
    while(getline(inputFile, firstline)){
	if (firstline == "//end of file"){
	    break;
	}

	inputFile >> d >> i >> j;
	g.setCoordinate(d,i,j);
    }


    //run asa and put results in output file
    g.ASA();
    g.printResult(outfile);

    return 0;
}
