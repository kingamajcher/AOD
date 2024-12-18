// Kinga Majcher 272354

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <limits>
#include <utility>
#include <string>
#include <stdexcept>

using namespace std;

struct Graph {
    int totalVertices;
    int edgesNo;
    vector<vector<pair<int, int>>> neighborsList;
    int minEdgeCost;
    int maxEdgeCost;

    Graph(int vertices, int edges, int minCost, int maxCost);
};

Graph readGraphFromFile(const string& filename);
vector<int> readSources(const string& filename);
vector<pair<int, int>> readPairs(const string& filename);
void writeResultSources(const string& outputFilename, const string& graphFilename, const string& sourcesFilename, const string& algorithmType, const Graph& graph, int minCost, int maxCost, double avgTime);
void writeResultPairs(const string& outputFilename, const string& graphFilename, const string& pairsFilename, const string& algorithmType, const Graph& graph, int minCost, int maxCost, const vector<tuple<int, int, int>>& pairsWithResults);

#endif // GRAPH_H
