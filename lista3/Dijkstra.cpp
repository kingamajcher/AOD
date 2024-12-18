// Kinga Majcher 272354

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <tuple>
#include <stdexcept>
#include <chrono>
#include <climits>
#include "Graph.h"

using namespace std;

pair<vector<int>, vector<int>> dijkstraForAll(const Graph& graph, int source) {
    int n = graph.totalVertices;
    vector<int> distance(n + 1, INT_MAX);
    vector<int> pred(n + 1, -1);

    distance[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, source);

    while (!pq.empty()) {
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (dist > distance[node]) continue;

        for (const auto& neighborEdge : graph.neighborsList[node]) {
            int neighbor = neighborEdge.first;
            int cost = neighborEdge.second;

            int value = distance[node] + cost;
            if (distance[neighbor] > value) {
                distance[neighbor] = value;
                pred[neighbor] = node;
                pq.emplace(value, neighbor);
            }
        }
    }

    return {distance, pred};
}

int dijkstraForPair(const Graph& graph, int source, int target) {
    int n = graph.totalVertices;
    vector<int> distance(n + 1, INT_MAX);
    distance[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, source);

    while (!pq.empty()) {
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (node == target) return distance[node];

        if (dist > distance[node]) continue;

        for (const auto& neighborEdge : graph.neighborsList[node]) {
            int neighbor = neighborEdge.first;
            int cost = neighborEdge.second;

            int value = distance[node] + cost;
            if (distance[neighbor] > value) {
                distance[neighbor] = value;
                pq.emplace(value, neighbor);
            }
        }
    }

    return distance[target];
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        cerr << "Błąd wywołania - niepoprawna liczba argumentów" << endl;
        return 1;
    }

    string flag1 = argv[1];
    string pathGraph = argv[2];
    string flag2 = argv[3];
    string pathSources = argv[4];
    string flag3 = argv[5];
    string pathOutput = argv[6];

    if (flag1 != "-d") {
        cerr << "Błąd wywołania - nieznana flaga " << flag1 << endl;
        return 1;
    }

    Graph graph = readGraphFromFile(pathGraph);

    if (flag2 == "-ss" && flag3 == "-oss") {
        vector<int> sources = readSources(pathSources);
        double timeTotal = 0.0;

        for (int source : sources) {
            auto start = chrono::high_resolution_clock::now();
            dijkstraForAll(graph, source);
            auto end = chrono::high_resolution_clock::now();
            timeTotal += chrono::duration<double>(end - start).count();
        }

        double avgTime = timeTotal / sources.size();
        writeResultSources(pathOutput, pathGraph, pathSources, "dijkstra", graph, graph.minEdgeCost, graph.maxEdgeCost, avgTime);

    } else if (flag2 == "-p2p" && flag3 == "-op2p") {
        vector<pair<int, int>> pairs = readPairs(pathSources);
        vector<tuple<int, int, int>> results;

        for (const auto& [i, j] : pairs) {
            int pathLength = dijkstraForPair(graph, i, j);
            results.emplace_back(i, j, pathLength);
        }

        writeResultPairs(pathOutput, pathGraph, pathSources, "dijkstra", graph, graph.minEdgeCost, graph.maxEdgeCost, results);

    } else {
        cerr << "Błąd wywołania - nieznana flaga " << flag2 << " lub " << flag3 << endl;
        return 1;
    }

    return 0;
}
