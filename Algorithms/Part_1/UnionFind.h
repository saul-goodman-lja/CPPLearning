#pragma once
#include <iostream>
#include <memory>
    
class QuickFindUF{
private:
    int len;
    std::unique_ptr<int[]> id;
public:
    QuickFindUF(int N) : len(N), id(std::make_unique<int[]>(N)){
        for(int i = 0; i < N; i++){
            id[i] = i;
        }
    }
    bool connected(int p, int q){
        return id[p] == id[q];
    }
    void _union(int p, int q){
        int pid = id[p];
        int qid = id[q];
        for(int i = 0; i < len; i++){
            if(id[i] == pid){
                id[i] = qid;
            }
        }
    }
};

// trie may be too tall, hardly to search
class QuickUnionUF{
private:
    int len;
    std::unique_ptr<int[]> id;
public:
    QuickUnionUF(int N) : len(N), id(std::make_unique<int[]>(N)){
        for(int i = 0; i < N; i++){
            id[i] = i;
        }
    }
    // 查找根节点
    int root(int i){ 
        while(i != id[i]){
            i = id[i];
        }
        return i;
    }
    bool connected(int p, int q){
        return root(p) == root(q);
    }
    void _union(int p, int q){
        int i = root(p);
        int j = root(q);
        id[i] = j;
    }
};
class QuickUnionImprovements{
private:
    int len;
    std::unique_ptr<int[]> id;
    std::unique_ptr<int[]> sz;
public:
    QuickUnionImprovements(int N) : len(N), id(std::make_unique<int[]>(N)), sz(std::make_unique<int[]>(N)){
        for(int i = 0; i < N; i++){
            id[i] = i;
            sz[i] = 1;
        }
    }
    // 查找根节点
    int root(int i){ 
        while(i != id[i]){
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }
    bool connected(int p, int q){
        return root(p) == root(q);
    }
    // lgN
    void _union(int p, int q){
        int i = root(p);
        int j = root(q);
        if(i == j){
            return;
        }
        if(sz[i] < sz[j]){
            id[i] = j;
            sz[i] += sz[j];
        }else{
            id[j] = i;
            sz[j] += sz[i];
        }
    }
};