#include<iostream>
#include<cstdlib>
#include "fqueue.h"
#include<ctime>
using namespace std;

void init(int nodes, int **a)
{
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            a[i][j]=0;
        }
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

bool checkConnectedGraph(const int numNodes,int **a){
    int visited[numNodes];
    for(int i=0;i<numNodes;i++)
        visited[i] = 0;
    fqueue<int> toVisit;
    toVisit.push(0);
    while(!toVisit.isEmpty())
    {
        visited[toVisit.front()] = 1;
        for(int i=0;i<numNodes;i++){
            if(a[toVisit.front()][i]!=0 && visited[i]==0)
            {
               toVisit.push(i);
            }
        }
        toVisit.pop();
    }
    bool flag = check(visited,numNodes);
    return flag;

}

int main(int argc,char* argv[])
{
    const int nodes = (const int)atoi(argv[1]);
    int **a;
    a = new int*[nodes];
    for(int i=0;i<nodes;i++){
        a[i] = new int[nodes];
    }
    cout<<rand()%nodes<<endl;
    int source;
    int dest;
    int count = 0;
    int weight = 0;
    int limit = (nodes*nodes)*0.001;
    bool flag = false;
    init(nodes,a);
    srand(time(NULL));
    while(flag == false)
    {
        while(count<limit){
            source = rand()%nodes;
            dest = rand()%nodes;
            weight = (rand()%1000)+1;
            if(a[source][dest]==0 && source!=dest)
            {
                count++;
                a[source][dest] = weight;
                a[dest][source] = weight;
            }
        }
    flag = checkConnectedGraph(nodes,a);
    if(flag == false){ 
        init(nodes,a);
        count = 0;
     }
     else{cout<<nodes<<" "<<nodes<<endl;}
    }
    for(int i=0;i<nodes;i++)
    {
        for(int j=0;j<nodes;j++)
        {
            if(a[i][j]>0)
                cout<<i<<" "<<j<<" "<<a[i][j]<<endl;
        }
    }
}
