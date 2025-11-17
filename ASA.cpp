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
