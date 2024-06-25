#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>

using std::cin, std::cout, std::string, std::istringstream;
using std::vector, std::stack;

void dfs(int v, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& recStack, stack<int>& Stack, bool& hasCycle){
    visited[v] = true;
    recStack[v] = true;

    for(int i : adj[v]){
        if(!visited[i]){
            dfs(i, adj, visited, recStack, Stack, hasCycle);
        }else if(recStack[i]){
            hasCycle = true;
            return ;
        }
    }
    recStack[v] = false;
    Stack.push(v);
}

vector<int> topologicalSortDFS(int V, vector<vector<int>>& adj){
    stack<int> Stack;
    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);
    bool hasCycle = false;

    for(int i = 0; i < V; i++){
        if(!visited[i]){
            dfs(i, adj, visited, recStack, Stack, hasCycle);
            if(hasCycle){
                return {};
            }
        }
    }

    vector<int> top_order;
    while(!Stack.empty()){
        top_order.push_back(Stack.top());
        Stack.pop();
    }

    return top_order;
}

int main(void){

    int V, n;
    int a, b;
    string line;
    getline(cin, line);
    istringstream iss(line);
    iss >> V >> n;
    vector<vector<int>> adj(V);
    while(n--){
        getline(cin, line);
        iss.clear();
        iss.str(line);
        iss >> a >> b;
        adj[a].push_back(b);
    }
    vector<int> rst_order = topologicalSortDFS(V, adj);
    if(rst_order.size() < V){
        cout << "-1" << "\n";
        return 0;
    }

    for(int i = 0; i < rst_order.size() - 1; i++){
        cout << rst_order[i] << " ";
    }
    cout << rst_order.back() << "\n";
    return 0;
}