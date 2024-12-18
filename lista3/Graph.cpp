// Kinga Majcher 272354

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <stdexcept>
#include <tuple>
#include <climits>

using namespace std;

struct Graph {
    int totalVertices;
    int edgesNo;
    vector<vector<pair<int, int>>> neighborsList;
    int minEdgeCost;
    int maxEdgeCost;

    Graph(int vertices, int edges, int minCost, int maxCost)
        : totalVertices(vertices), edgesNo(edges), minEdgeCost(minCost), maxEdgeCost(maxCost) {
        neighborsList.resize(totalVertices + 1);
    }
};

Graph readGraphFromFile(const string& filename) {
    int totalVertices = 0, edgesNo = 0;
    int minEdgeCost = INT_MAX;
    int maxEdgeCost = INT_MIN;
    vector<vector<pair<int, int>>> neighborsList;

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string flag;
        iss >> flag;

        if (flag == "c") {
            continue;
        } else if (flag == "p") {
            string temp;
            iss >> temp >> totalVertices >> edgesNo;
            neighborsList.resize(totalVertices + 1);
        } else if (flag == "a") {
            int u, v;
            int c;
            iss >> u >> v >> c;
            maxEdgeCost = max(maxEdgeCost, c);
            minEdgeCost = min(minEdgeCost, c);
            neighborsList[u].emplace_back(v, c);
        } else {
            throw runtime_error("Unknown flag in file!");
        }
    }

    file.close();
    Graph graph = Graph(totalVertices, edgesNo, minEdgeCost, maxEdgeCost);
    graph.neighborsList = move(neighborsList);

    return graph;
}

vector<int> readSources(const string& filename) {
    vector<int> sourceVector;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string flag;
        iss >> flag;

        if (flag == "c") {
            continue;
        } else if (flag == "p") {
            continue;
        } else if (flag == "s") {
            int u;
            iss >> u;
            sourceVector.push_back(u);
        } else {
            throw runtime_error("Unknown flag in file!");
        }
    }

    file.close();
    return sourceVector;
}

vector<pair<int, int>> readPairs(const string& filename) {
    vector<pair<int, int>> pairsVector;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string flag;
        iss >> flag;

        if (flag == "c") {
            continue;
        } else if (flag == "p") {
            continue;
        } else if (flag == "q") {
            int u, v;
            iss >> u >> v;
            pairsVector.emplace_back(u, v);
        } else {
            throw runtime_error("Unknown flag in file!");
        }
    }

    file.close();
    return pairsVector;
}

void writeResultSources(const string& outputFilename, const string& graphFilename, const string& sourcesFilename, const string& algorithmType, const Graph& graph, int minCost, int maxCost, double avgTime) {
    ofstream file(outputFilename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + outputFilename);
    }

    file << "p res sp ss " << algorithmType << "\n";
    file << "-------------------------------\n";
    file << "f " << graphFilename << " " << sourcesFilename << "\n";
    file << "g " << graph.totalVertices << " " << graph.edgesNo << " " << minCost << " " << maxCost << "\n";
    file << "t " << avgTime << "\n";

    file.close();
}

void writeResultPairs(const string& outputFilename, const string& graphFilename, const string& pairsFilename, const string& algorithmType, const Graph& graph, int minCost, int maxCost, const vector<tuple<int, int, int>>& pairsWithResults) {
    ofstream file(outputFilename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + outputFilename);
    }

    file << "p res sp p2p " << algorithmType << "\n";
    file << "c -------------------------------\n";
    file << "f " << graphFilename << " " << pairsFilename << "\n";
    file << "g " << graph.totalVertices << " " << graph.edgesNo << " " << minCost << " " << maxCost << "\n";

    for (const auto& pair : pairsWithResults) {
        int u = get<0>(pair);
        int v = get<1>(pair);
        int cost = get<2>(pair);

        if (cost == INT_MAX) {
            file << "d " << u << " " << v << " INFINITY\n";
        } else {
            file << "d " << u << " " << v << " " << cost << "\n";
        }
    }


    file.close();
}
