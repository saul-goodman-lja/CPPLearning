#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using std::cin, std::cout, std::vector, std::queue, std::unordered_map;

int main(void){

    int m, n, s, t;
    cin >> n >> m;
    vector<int> inDegree(n, 0);

    unordered_map<int, vector<int>> umap;
    vector<int> result;

    while(m--){
        cin >> s >> t;
        inDegree[t]++;
        umap[s].push_back(t);
    }

    queue<int> que;
    for(int i = 0; i < n; i++){
        if(inDegree[i] == 0){
            que.push(i);
        }
    }

    while(que.size()){
        int cur = que.front();
        que.pop();

        result.push_back(cur);
        
        vector<int> files = umap[cur];
        if(files.size()){
            for(int i = 0; i < files.size(); i++){
                inDegree[files[i]]--;
                if(inDegree[files[i]] == 0){
                    que.push(files[i]);
                }
            }
        }
    }

    if(result.size() == n){
        for(int i = 0; i < n - 1; i++){
            cout << result[i] << " ";
        }
        cout << result[n - 1] << "\n";
    }else{
        cout << "-1" << "\n";
    }

    return 0;
}