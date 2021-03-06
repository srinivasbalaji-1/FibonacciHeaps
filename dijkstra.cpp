/* 
 * Author: srinivas balaji ramesh
 * UFID : 94217395
 * email : rsbalaji@ufl.edu
 * Created on March 11, 2014, ; 12:51 AM
 	In the user mode an input file is read from disk and a graph is generated with edges and weights
	present in the file.
	The following is the way to run the program.
	
	./dijkstra –s <input>
	
	For the simple scheme using an array
	
	./dijkstra –r <input>
	
	In this mode, two parameters are given as input to the program as follows
	
	./dijkstra -r n d src

	where -r implies it is to be run in random mode and n represents number of vertices in the graph, d
	represents percentage of density of edges in the graph and src represents the source node.

 */
 
 
#include<fstream>
#include <cstdlib>
#include<iostream>
#include<ctime>
#include<vector>
#include<queue>
#include<climits>
#include "fiboheap.h"


/*
 * 
 */
using namespace std;

/* An adjacency list structure to store links in the graph */

struct adjList {
    int dist;
    int destination;
    adjList* next;
};

/* Keeps track of the source in the construction of the adjacency list*/
struct vertex {
    bool visited;
    int minSourceDistance;
    adjList* ptr;
};



/* Initializes the boolean array. This function is used for initializing the visited array */
void initbool(int numNodes, bool **a) {
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            a[i][j] = false;
        }
    }
}
/**
 * initialize
 * @param nodes
 * @param v
 */
void init(int nodes, vertex *v) {
    for (int i = 0; i < nodes; i++) {
        v[i].ptr = NULL;
        v[i].visited = false;
    }

}

bool check(int *visited, int nodes) {
    for (int i = 0; i < nodes; i++) {
        if (visited[i] == 0)
            return false;
    }
    return true;
}

/* breadth first search to check the connectivity of the graph. Any node in the Graph that 
 * remains unvisited indicates disconnected graph. */

bool checkConnectedGraph(const int numNodes, vertex *nodeList) {
    int visited[numNodes];
    bool flag = false;
    for (int i = 0; i < numNodes; i++)
        visited[i] = 0;
    queue<int> toVisit;
    //int popCount = 0;
    int pushCount = 0;
    toVisit.push(0);
    while (!toVisit.empty()) {
        visited[toVisit.front()] = 1;
        adjList* strt = nodeList[toVisit.front()].ptr;
        while (strt != NULL) {
            if (visited[strt->destination] == 0) {
                toVisit.push(strt->destination);
                pushCount++;
            }
            if (pushCount == numNodes) {
                return true;
            }
            strt = strt->next;
        }
        toVisit.pop();
    }

    return flag;
}

/**
 * creates the link between newly created vertex node and the adjacency list.
 * @param a
 * @param dest
 * @param weight
 * @return 
 */
adjList* createLink(vertex a, int dest, int weight) {
    adjList* newNode = new adjList;
    newNode->destination = dest;
    newNode->dist = weight;
    newNode->next = a.ptr;
    return newNode;
}

/**
 * prints the data stored in the adjacency list structure to random.txt file. 
 * @param v
 * @param numNodes
 */
void printToFile(vertex* v, const int numNodes) {
    ofstream out;
    out.open("random.txt");
    for (int i = 0; i < numNodes; i++) {
        adjList* temp = v[i].ptr;
        while (temp != NULL) {
            out << i << " " << temp->destination << " " << temp->dist << "\n";
            temp = temp->next;
        }
    }
    out.close();
}

/**
 * Genrates a randomly generated connected graph. All the generated results are stored in the form of
 * an adjacency list structure.
 * @param numNodes
 * @param edgeDensity
 * @return 
 */
vertex* createRandomGraph(const int numNodes, float edgeDensity) {
    /*  here v is defined as an array of vertex pointers  */
    vertex *v = new vertex[numNodes];
    int source;
    int dest;
    long int count = 0;
    int weight = 0;
    int limit = (numNodes * (numNodes - 1) / 2)*edgeDensity/100;
    bool flag = false;
    bool **link;
    link = new bool*[numNodes];
    for (int i = 0; i < numNodes; i++) {
        link[i] = new bool[numNodes];
    }
    init(numNodes, v);
    initbool(numNodes, link);
    //srand(time(NULL));
    while (flag == false) {
        while (count < limit) {
            source = rand() % numNodes;
            dest = rand() % numNodes;
            weight = (rand() % 1000) + 1;
            if (!link[source][dest] && source != dest) {
                count++;
                v[source].ptr = createLink(v[source], dest, weight);
                v[dest].ptr = createLink(v[dest], source, weight);
                link[source][dest] = true;
                link[dest][source] = true;
            }
        }
        flag = checkConnectedGraph(numNodes, v);

        if (flag == false) {
            init(numNodes, v);
            initbool(numNodes, link);
            count = 0;
        }
    }
    //printToFile(v, numNodes);
    return v;
}
/**
 * prints the results to the standard output stream.
 * @param v
 * @param numNodes
 * @param src
 */
void printResultsToFile(vertex* v,const int numNodes,int src)
{
    for(int i=0;i<numNodes;i++)
        {
            cout<<v[i].minSourceDistance<<" \\\\ cost from "<<src<<" to "<<i<<endl;
            if(i%400==0){
                cout.flush();
            }
        }
}

/**
 * Uses the Fibonacci heap scheme to solve the Dijkstra’s single source shortest path algorithm
 * @param v
 * @param numNodes
 * @param src
 * @return 
 */
vertex* solveUsingFibonacciHeaps(vertex* v, const int numNodes, int src) {
		//clock_t start, time;
		//start = clock();
    fiboheap<adjList> fheap(numNodes);
    int weight = 0;
    adjList* source = v[src].ptr;
    v[src].visited = true;
    v[src].minSourceDistance = 0;
    while (source != NULL) {
        adjList src1 = *source;
        fheap.insert(src1);
        source = source->next;
    }
    while (!fheap.isEmpty()) {
        adjList nextDestinationInPath = fheap.getMin();
        fheap.removeMin();
        weight = nextDestinationInPath.dist;
        v[nextDestinationInPath.destination].visited = true;
        v[nextDestinationInPath.destination].minSourceDistance = weight;
        adjList* toAddNodes = v[nextDestinationInPath.destination].ptr;
        while (toAddNodes != NULL) {
            if (v[toAddNodes->destination].visited == false) {
                adjList toAddNodes1;
                toAddNodes1.destination = toAddNodes->destination;
                toAddNodes1.dist = toAddNodes->dist;
                //toAddNodes1.next = toAddNodes->next;
                adjList temp = {weight + toAddNodes1.dist,toAddNodes1.destination, NULL};
                if (!fheap.isRefNull(toAddNodes1)) {                    
                    fheap.decreaseKey(temp);
                } else
                    fheap.insert(temp);
            }
            toAddNodes = toAddNodes->next;
        }
        
    }
    //time = clock()-start;
    //cout << "\nTotal execution time using Fibonacci Scheme : "<< (double) time / CLOCKS_PER_SEC << " secs\n";
   // printResultsToFile(v,numNodes,src);
    return v;
}


/**
 * Resets the vertex structure variable visited and set it to false
 * @param v
 * @param numNodes
 * @return 
 */
vertex* vertexReset(vertex* v,const int numNodes)
{
    for (int i = 0; i < numNodes; i++) {
        v[i].visited = false;
        v[i].minSourceDistance = 0;
    }
    return v;
}

/**
 * Find the index of the smallest value in the minimumWeight array.This used in solving Dijkstra’s
 *single source shortest path algorithm using the simple array scheme.
 * @param v
 * @param numNodes
 * @return 
 */
int findMinIndex(int* v,const int numNodes)
{
    int min = INT_MAX;
    int minIndex = 0;
    for(int i=0;i<numNodes;i++)
    {
        if(v[i]<min)
        {
            min = v[i];
            minIndex = i; 
        }
    }
    return minIndex;
    
}

/**
 * Solves Dijkstra’s single source shortest path algorithm using the simple array scheme.
 * @param v
 * @param numNodes
 * @param src
 * @return 
 */
vertex* solveUsingSimpleScheme(vertex* v,const int numNodes,int src){
		
    int weight = 0;
    adjList* node = v[src].ptr;
    int minWeightArray[numNodes];
    for(int i =0;i<numNodes;i++)
    {
        minWeightArray[i] = INT_MAX;
    }
    minWeightArray[src] = 0;
    int visitCount = 0;
    while(visitCount!=numNodes)
    {
        int minNode = findMinIndex(minWeightArray,numNodes);
        weight = minWeightArray[minNode];
        v[minNode].visited = true;
        node = v[minNode].ptr;
        visitCount++;
        v[minNode].minSourceDistance = weight;
        minWeightArray[minNode] = INT_MAX;
        while(node!=NULL)
        {
            if(v[node->destination].visited == false && minWeightArray[node->destination]>(weight+node->dist)){
            minWeightArray[node->destination] = weight+node->dist;
            }
            node = node->next;
        }
        
    }
    //time = clock()-start;
    //cout << "\nTotal execution time using Simple Scheme : "<< (double) time / CLOCKS_PER_SEC << " secs\n";
    //printResultsToFile(v,numNodes);
    return v;
}

int main(int argc, char* argv[]) {
		string type = argv[1];
		vertex* v;
		clock_t start, time;
		
		
    if (type == "-r") {
        const int numNodes = (const int) atoi(argv[2]);
        float edgeDensity = atof(argv[3]);
        const int src = atoi(argv[4]);
        v = createRandomGraph(numNodes, edgeDensity);
        start = clock();
        v = solveUsingFibonacciHeaps(v, numNodes, src);
        time = clock()-start;
        cout<<"the fibonacci heap scheme takes:"<<time<<"msec"<<endl;
        //printResultsToFile(v,nodes);
        v = vertexReset(v,numNodes);
        start = clock();
        v = solveUsingSimpleScheme(v,numNodes,src);
        time = clock()-start;
        cout<<"the simple array scheme takes:"<<time<<"msec"<<endl;
        
        //printResultsToFile(v,nodes);
        
    }
    if(type == "-s" or type == "-f"){
    	int src1,numNodes1,numEdges;
    	ifstream in(argv[2]);
    	in>>src1;    	
    	in>>numNodes1>>numEdges;
    	v = new vertex[(const int)numNodes1];
    	int source,destination,distance;
    	init((const int)numNodes1, v);
    	for(int i=0;i<numEdges;i++){
    		in>>source>>destination>>distance;
    		v[source].ptr = createLink(v[source], destination, distance);
        v[destination].ptr = createLink(v[destination], source, distance);
    		
    	} 
    	if(!checkConnectedGraph((const int)numNodes1,v))
    	{
    		cout<<"graph not connected: stopping the program.....";
    		return 0;
    	}
    	if(type=="-f") {
    	v = solveUsingFibonacciHeaps(v, (const int)numNodes1, src1);
    	printResultsToFile(v,(const int)numNodes1,src1);
    	}
    	v = vertexReset(v,(const int)numNodes1);
    	if(type=="-s"){
    	v = solveUsingSimpleScheme(v,(const int)numNodes1,src1);
    	printResultsToFile(v,(const int)numNodes1,src1);
    	}
    }


}

