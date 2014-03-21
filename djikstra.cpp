/* 
 * File:   main.cpp
 * Author: questworld
 *
 * Created on March 11, 2014, 12:51 AM
 */

#include <cstdlib>
#include<iostream>
#include<ctime>
#include "fqueue.h"
#include<vector>
#include<map>


/*
 * 
 */
using namespace std;

/* An adjacency list structure to store links in the graph */

struct adjList{
    int dist;
    int destination;
    adjList* next;
};

struct vertex{
    adjList* ptr;
};

void initbool(int numNodes,bool **a){
    for(int i=0;i<numNodes;i++)
    {
        for(int j=0;j<numNodes;j++)
        {
            a[i][j] = false;
        }
    }
}

void init(int nodes, vertex *v)
{
    for(int i=0;i<nodes;i++){
        v[i].ptr = NULL;        
    }   
        
}

bool check(int *visited,int nodes)
{
    for(int i=0;i<nodes;i++)
    {   
        if(visited[i]==0)
            return false;
    }   
    return true;
}

/* breadth first search to check the connectivity of the graph. Any node in the Graph that remains unvisited indicates disconnected graph. */

bool checkConnectedGraph(const int numNodes,vertex *nodeList){
    int visited[numNodes];
    for(int i=0;i<numNodes;i++)
        visited[i] = 0;
    fqueue<int> toVisit;
    toVisit.push(0);
    while(!toVisit.isEmpty())
    {   
        visited[toVisit.front()] = 1;
        adjList* strt = nodeList[toVisit.front()].ptr;
        while(strt!=NULL)
        {
            if(visited[strt->destination]==0)
            {   
               toVisit.push(strt->destination);
            }   
            strt = strt->next;
        }   
        toVisit.pop();
    }   
    bool flag = check(visited,numNodes);
    return flag;
}

adjList* createLink(vertex a, int dest,int weight)
{
    adjList* newNode = new adjList;
    newNode->destination = dest;
    newNode->dist = weight;
    newNode->next = a.ptr;
}

int main(int argc,char* argv[])
{
    const int nodes = (const int)atoi("3000");
    vertex *v = new vertex[nodes];
    int source;
    int dest;
    int count = 0;
    int weight = 0;
    int limit = (nodes*nodes)*0.001;
    bool flag = false;
    bool **link;
    link = new bool*[nodes];
    for(int i=0;i<nodes;i++){
        link[i] = new bool[nodes];
    }
    init(nodes,v);
    initbool(nodes,link);
    srand(time(NULL));
    while(flag == false)
    {
        while(count<limit){
            source = rand()%nodes;
            dest = rand()%nodes;
            weight = (rand()%1000)+1;
            if(!link[source][dest] && source!=dest)
            {
                count++;
                //cout<<"der";
                v[source].ptr = createLink(v[source],dest,weight);
                v[dest].ptr =  createLink(v[dest],source,weight);
                link[source][dest] = true;
                link[dest][source] = true;
            }
        }
    //cout<<flag;
    flag = checkConnectedGraph(nodes,v);
    if(flag == false){
        //cout<<flag<<endl;
        init(nodes,v);
        initbool(nodes,link);
        count = 0;
     }
    }
    for(int i=0;i<nodes;i++)
    {
        adjList* temp = v[i].ptr;
        while(temp!=NULL)
        {
            cout<<i<<" "<<temp->destination<<" "<<temp->dist<<endl;
            temp = temp->next;
        }
    }
}

