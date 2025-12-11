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
#include <string>
//for printf
#include <cstdio>

using namespace std;

class Graph {
private:
    int numNodes;
    int start;
    int finish;
    //used to calculate distance
    //int parent; 

    //int roundsCount;
    //vector <vector<int>> adjMatrix;

    vector <int> parent;	   //used to calculate path later
    vector<vector<int>> neighbors; //improved version of adjMatrix
    vector<vector<int>> coordinates;	
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

   void new_path(int s, int f){	
	//if it is not empty, ASA has been called before
	//clear lists, distance, path, and hueristics
	if (!closedList.empty()){
		distance.clear();
		hueristic.clear();
		totalVal.clear();
		openList.clear();
		closedList.clear();
		path.clear();
		neighbors.clear();
		parent.clear();
	}
   }

   void print_parent(){
	int i = 0;
   	cout << "parent list \n";
	
	for (int x: parent){
	cout << i  << "'s parent is " << x << endl;
	i++;
	}
   }
   void print_neighbors(){
	cout << "neighbors list \n ";
   	for (const auto& row : neighbors) {
		cout << &row << ": ";
    		for (int x : row) {
       		cout << x << " ";
    		}
    	cout << "\n";
	}

   }

   bool visitalready(int n){
   	for (int x: closedList){
		if (x == n){
			return true;
		}
	}

	//only returns if we never visited before
	return false;
   
   } 

    int get_start(){
    	return start;
    }

    int get_finish(){
    	return finish;
    }

    //setter functions
    void initMatrices(int n) {
    	numNodes = n;
	neighbors.resize(n);
    	parent.assign(numNodes, -1);
	coordinates.assign(n, vector<int>(2, 0));
	distance.assign(numNodes , 0);
	hueristic.assign(numNodes, 0);
	totalVal.assign(numNodes, 0);

    }


    void setEdge(int i, int j, int weight) {
    	neighbors[i].push_back(j);
	neighbors[j].push_back(i);
	distance[j] = weight;
    }

    void setCoordinate(int n, int x, int y) {
    	coordinates[n][0] = x;
	coordinates[n][1] = y;
}
	
void compute_hueristic(int n)
    {
	//let x1,y1 = n coords
	//let x2,y2 = end coords
	int x1, x2, y1, y2;

	x1 = coordinates[n][0];
	x2 = coordinates[finish][0];
	y1 = coordinates[n][1];
	y2 = coordinates[finish][1];

	//calculate using euclidean distance
	hueristic[n] = sqrt(pow((x1-x2), 2) + pow ((y1-y2),2));
    }


    void compute_distance(int n){
    	int tempdist = 0;
	int lastnode = 0;

	
	if(n == start){
		distance[n] = 0;
		return;
	}

	//add up distances of current path 
	for (int x: path){
		tempdist += distance[x];
		lastnode = x;
	}
	//dont forget to add distance btwn curr path and potential node
	tempdist+= distance[n];

	//update results in distance array 
	distance[n] = tempdist;
	
    	//case direct neigbor
	/*
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
		distance[n] = tempdist;
	}
	*/
	

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

    void gen_path(){
    	int curr = finish;
        while(curr != -1){
            path.push_back(curr);
            curr = parent[curr];
        }
	//done path has been generated!
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


    bool openListsearch(int n){
    	for (int i = 0; i < openList.size(); i++){
		if (openList[i] == n){
			return true;
		}
	}
	//did not find element
	return false;
    }

    //some type of merge sort to ensure openList is a priority queue
    void sort_openList(){
	    std::sort(openList.begin(), openList.end());
    }

/*
int get_edge(int x, int y){
	return adjMatrix[x][y];
}
*/
    


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
		//path.push_back(curr);


		if (curr == finish){
			//formulate path vector
			//gen_path();
			return;
		}

		//if closedList has this ovj, has already been explored
		//continue
		if (visitalready(curr)){
			cout << "visit already, skip" << endl;
			//remove top element
			openList.erase(openList.begin());

			//proceed to next node
			continue;
		}
		
		//move curr node from open to closed list
		openList.erase(openList.begin());
		//openList.clear();
		closedList.push_back(curr);

		//check neighboring potential paths of curr		
		for (int x: neighbors[curr]){
			compute_distance(x);
			compute_hueristic(x);
			compute_totalVal(x);
			openList.push_back(x);

			if (!visitalready(x)){
				//openList.push_back(x);
				parent[x] = curr;
			}
			//parent[x] = curr;
			
			/*
			cout << "node: " << x << endl;
			cout << " " << endl;
			*/
			
		}
		sort_openList();

		//debug purposes
			
		
		for (int x: openList){
			cout << "current openlist" << endl;
			cout << "node: " << x << endl;
			cout << " " << endl;
		}
		
		
		
				
    }
	cout << "end of ASA reached" << endl;
}

    void printResult(ofstream& outfile){
        for(int i = path.size() - 1; i > -1; i--){
		
	    //prints to output.txt
	    //outfile << "shortest path from " << g.get_start() << " to " << g.get_finish() << ": ";
            outfile << "-> " << path [i] << " ";
	    
	    //rpints to terminal
	    cout << " -> " << path[i] << " ";
	    //cout << "shortest path from " << g.get_start() << " to " << g.get_finish() << ": ";
        }
        outfile << endl;
	cout << endl;
        return;
    }

};

int main(int argc, char* argv[])
{
    ifstream inputFile(argv[1]);
    ofstream outfile(argv[2]);

    if (!inputFile.is_open()) {
    cerr << "FAILED TO OPEN INPUT FILE\n";
    return 1;
    }

    //string firstline;
    int s;
    inputFile >> s;

    inputFile.ignore(numeric_limits<streamsize>::max(), '\n');


    //graph wants start and finish node before constructed
    Graph g(0, 23);
    g.initMatrices(s);
    int i, j, d;
    string line = "";

        // get edges from input file
    while(getline(inputFile, line)){
	//printf("curr in edge loop");
	if ( line  == "//coordinate location node"){
		//printf("exits coord loop \n");
		break;
	}
	if (line.empty()){
	       	continue;
	}
        if (line.rfind("//", 0) == 0){
	       	continue;
	}

	stringstream ss(line);
	ss >> i >> j >> d;
	//for debugging
	//cout << "edge " << i << " to " << j << " " << d << " units"<< endl;
	
	//undirected graph
        g.setEdge(i,j,d);

	//to make sure edge was initialized properly
	//printf("coord dist %d \n", g.get_edge(i,j));
    }

    //cout <<"got edges from input file" << endl;
    //printf("printf works test\n ");

    //get coordinates
    while(getline(inputFile, line)){
	//printf("curr in coord loop");
	if ( line == "//end of file"){
	    break;
	}
	if (line.empty()){
	       	continue;
	}
        if (line.rfind("//", 0) == 0){
	       	continue;
	}

	stringstream ss(line);
	ss >> d >> i >> j;
	//for debugging
	//cout << "node " << d << " x: " << i << " y: " << j <<endl;
	g.setCoordinate(d,i,j);
    }

    //printf("printf test2\n");
    //cout << "got coordinates from input file" <<endl;

    //neighobors list is working
    g.print_neighbors();

    //run asa and put results in output file
    g.ASA();
    //cout << "ASA run done" << endl;
    

    g.gen_path();
    g.print_parent();

    outfile << "shortest path from " << g.get_start() << " to " << g.get_finish() << ": ";
    cout << "shortest path from " << g.get_start() << " to " << g.get_finish() << ": ";
    g.printResult(outfile);
    //cout << "print results done" << endl;
    

    //shelved temporary
    //g.new_path(6,1);
    //g.ASA();
    //g.printResult(outfile);

    return 0;
}
