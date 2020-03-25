//
// Created by Octavian Custura on 26/02/2020.
//
#pragma once
#ifndef SECOND_IMPLEMENTATION_GRAPH_H
#define SECOND_IMPLEMENTATION_GRAPH_H

#include <map>
#include <utility>
#include <vector>
#include <string>

class OrderedGraphCost {
private:
    std::map<int, std::vector<int>> outMap, inMap;
    std::map<std::pair<int, int>, int> costMap;
public:
    // constructor
    explicit OrderedGraphCost(int nrVertices);

    int nrVertices();

    int nrEdges();

    std::pair<std::map<int, std::vector<int>>::iterator , std::map<int, std::vector<int>>::iterator> setOfVertices();

    bool isVertex(int v);

    bool isEdge(int v1, int v2);

    void addEdge(int v1, int v2, int cost);

    int inDegree(int x);

    int outDegree(int x);

    std::pair <std::vector<int>::iterator, std::vector<int>::iterator> inboundEdge(int x);

    std::pair <std::vector<int>::iterator, std::vector<int>::iterator> outboundEdge(int x);

    void changeCost(int x, int y, int val);

    int getCost(int x, int y);

    void removeEdge(int x, int y);

    void addVertex(int val);

    void removeVertex(int val);

    std::string toString();
};
#endif //SECOND_IMPLEMENTATION_GRAPH_H
