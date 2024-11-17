// aim to achieve the shortest path in the dag
#include <iostream>
#include <unordered_map>
#include <list>
#include <stack>
#include <vector>
#include <limits.h>
using namespace std;
class graph{
  public:
    // we wil store graph in adj list
    // we used pair because each edge has a particular weight
    unordered_map<int,list<pair<int,int>>> adj;
    
    void makeEdge(int u,int v,int weight){
        pair<int,int> p;
        p = make_pair(v,weight);
        adj[u].push_back(p);
    }
    void printGraph(){
        for(auto i:adj){
            cout<<i.first<<"-> ";
            for(auto j:i.second){
                cout<<"(" <<j.first <<"," <<j.second<<")";
            }
            cout<<endl;
        }
    }
    
    void dfs(int node, unordered_map<int,bool> &visited, stack<int> &topo){
        // first make the src node visited as true;
        visited[node]=true;
        
        for(auto neighbour:adj[node]){
            // here neighbour would be a pair so in the pair first is node second is weight
            if(!visited[neighbour.first]){
                // make call if not visited;
                dfs(neighbour.first,visited,topo);
            }
        }
        // when return back from the function push inti stact every time;
        topo.push(node);
    }
    
    void shortestPath(int src, vector<int> &dist, stack<int> &topo){
        // in this we rearrange the distance
        // distance of src node would be always 0
        dist[src] = 0;
        while(!topo.empty()){
            int top = topo.top();
            topo.pop();
            
            if(dist[top]!=INT_MAX){
                for(auto neighbour:adj[top]){
                    // check if the current distance is less than update
                    if(dist[top]+neighbour.second < dist[neighbour.first]){
                        dist[neighbour.first] = dist[top]+neighbour.second;
                    }
                }
            }
        }
    }
};
int main() {
    graph g;
    g.makeEdge(0,1,5);
    g.makeEdge(0,2,3);
    g.makeEdge(1,2,2);
    g.makeEdge(1,3,6);
    g.makeEdge(2,3,7);
    g.makeEdge(2,4,4);
    g.makeEdge(2,5,2);
    g.makeEdge(3,4,-1);
    g.makeEdge(4,5,-2);
    g.printGraph();
    
    unordered_map<int,bool> visited;
    stack<int> topo;
    int n = 6;
    // making topological sorting 
    for(int i=0;i<n;i++){
        if(!visited[i])
            g.dfs(i,visited,topo);
    }
    
    vector<int> dist(n);
    // first make all the distannce as infinity
    for(int i=0;i<n;i++){
        dist[i] = INT_MAX;
    }
    int src = 1 ;
    g.shortestPath(src,dist,topo);
    for(int i=0;i<n;i++){
        if(dist[i]==INT_MAX) cout<<"MAX"<<" ";
        else cout<<dist[i]<<" ";
    }
    return 0;
}