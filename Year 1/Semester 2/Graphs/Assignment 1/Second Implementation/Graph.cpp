//
// Created by Octavian Custura on 26/02/2020.
//

#include "Graph.h"
#include <exception>
#include <iostream>

OrderedGraphCost::OrderedGraphCost(int nrVertices) {
    for (int i = 0; i < nrVertices; ++i) {
        inMap[i] = std::vector<int>();
        outMap[i] = std::vector<int>();
    }
}

void OrderedGraphCost::addEdge(int v1, int v2, int cost) {
    if (!isVertex(v1) or !isVertex(v2) or isEdge(v1, v2)) {
        throw std::exception();
    }
    costMap[std::make_pair(v1, v2)] = cost;
    outMap[v1].push_back(v2);
    inMap[v2].push_back(v1);
}

bool OrderedGraphCost::isVertex(int v) {
    if (inMap.find(v) != inMap.end()) {
        return true;
    }
    return false;
}
bool OrderedGraphCost::isEdge(int v1, int v2) {
    return std::find(outMap[v1].begin(), outMap[v1].end(), v2) != outMap[v1].end();
}

std::pair<std::map<int, std::vector<int>>::iterator , std::map<int, std::vector<int>>::iterator> OrderedGraphCost::setOfVertices() {
    return std::make_pair(outMap.begin(), outMap.end());
}

int OrderedGraphCost::nrVertices() {
    return outMap.size();
}

int OrderedGraphCost::nrEdges() {
    return costMap.size();
}

int OrderedGraphCost::inDegree(int x) {
    return inMap[x].size();
}

int OrderedGraphCost::outDegree(int x) {
    return outMap[x].size();
}

int OrderedGraphCost::getCost(int x, int y) {
    if (!isEdge(x, y)) {
        throw std::exception();
    }
    return costMap[std::make_pair(x, y)];
}

void OrderedGraphCost::changeCost(int x, int y, int val) {
    if (!isEdge(x, y)) {
        throw std::exception();
    }
    this->costMap[std::make_pair(x, y)] = val;
}

std::pair <std::vector<int>::iterator, std::vector<int>::iterator> OrderedGraphCost::inboundEdge(int x) {
    return std::make_pair(inMap[x].begin(), inMap[x].end());
}

std::pair<std::vector<int>::iterator, std::vector<int>::iterator> OrderedGraphCost::outboundEdge(int x) {
    return std::make_pair(outMap[x].begin(), outMap[x].end());
}

void OrderedGraphCost::removeEdge(int x, int y) {
    if (!isEdge(x, y)) {
        throw std::exception();
    }
    for (auto &elem : costMap) {
        if (y == elem.first.second and x == elem.first.first) {
            costMap.erase(elem.first);
            break;
        }
    }
    inMap[y].erase(std::find(inMap[y].begin(), inMap[y].end(), x));
    outMap[x].erase(std::find(outMap[x].begin(), outMap[x].end(), y));
}

void OrderedGraphCost::addVertex(int val) {
    if (isVertex(val)) {
        throw std::exception();
    }
    inMap[val] = std::vector<int>();
    outMap[val] = std::vector<int>();
}

void OrderedGraphCost::removeVertex(int val) {
    inMap.erase(inMap.find(val));
    outMap.erase(outMap.find(val));
    int len = costMap.size();
    std::vector<std::pair<int, int>> array;
    for (auto& el : costMap) {
        array.push_back(el.first);
    }
    int i = 0;
    std::map<std::pair<int, int>, int> newCostMap;
    while (i < len) {
        if (array[i].second == val or array[i].first == val) {
            costMap.erase(costMap.find(array[i]));
            array.erase(std::find(array.begin(), array.end(), array[i]));
            len--;
            continue;
        }
        int x = array[i].first;
        int y = array[i].second;
        if (x > val) x--;
        if (y > val) y--;
        newCostMap[std::make_pair(x, y)] = costMap[array[i]];
        i++;
    }
    costMap = newCostMap;
    std::map<int, std::vector<int>> newInMap;
    for (auto el : inMap) {
        auto c = std::find(el.second.begin(), el.second.end(), val);
        if (c != el.second.end()) {
            el.second.erase(c);
        }
    }
    for (i = 0; i < inMap.size(); ++i) {
        int x = i;
        if (x > val) x--;
        newInMap[x] = inMap[i];
        for (int j = 0; j < inMap[i].size(); ++j) {
            if (inMap[i][j] > val) {
                newInMap[x][j] = inMap[i][j] - 1;
            }
        }
    }
    std::map<int, std::vector<int>> newOutMap;
    for (auto el : outMap) {
        auto c = std::find(el.second.begin(), el.second.end(), val);
        if (c != el.second.end()) {
            el.second.erase(c);
        }
    }
    for (i = 0; i < outMap.size(); ++i) {
        int x = i;
        if (x > val) x--;
        newOutMap[x] = outMap[i];
        for (int j = 0; j < outMap[i].size(); ++j) {
            if (outMap[i][j] > val) {
                newOutMap[x][j] = outMap[i][j] - 1;
            }
        }
    }
    std::cout << '\n';
    inMap = newInMap;
    outMap = newOutMap;
}

std::string OrderedGraphCost::toString() {
    std::string str;
    str += std::to_string(nrVertices()) + " " + std::to_string(nrEdges()) + "\n";
    for (auto i: costMap) {
        str += std::to_string(i.first.first) + " " + std::to_string(i.first.second) + " " + std::to_string(i.second) + "\n";
    }
    return str;
}
