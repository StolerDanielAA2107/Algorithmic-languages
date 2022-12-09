#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <set>
#include <unordered_map>
#include <map>
#include <sstream>
#include <fstream>

#include "pipe.h"
#include "cs.h"
#include "Utils.h"

using namespace std;

class Graph
{
    unordered_map <int, pipe> pipes;
    unordered_map <int, cs> css;

    vector<vector<int>> EdgesAndVertexes(unordered_map<int, int>& indexVertexes, int& n);

public:
    Graph();
    void menu();
    void menupipe();
    void menucs();
    void InputPipe();
    void InputKS();
    void PrintAll();
    int ChoiceOrInputNewPipe(int val);
    void newgraph();
    void printgraph();
    void TopologicalSort();
    void TopologicalSortUtil(int v, bool visited[], stack<int>& Stack, vector<vector<int>>& edges);
    void ConnectPipe();
    void Search();
    void SaveAll();
    void LoadAll();
    void Delete();
   // bool CanBeUsed(const pipe& p) const;
    void ShowNetwork();
};
