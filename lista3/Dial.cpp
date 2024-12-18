// Kinga Majcher 272354

#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <chrono>
#include <climits>
#include "Graph.h"

using namespace std;

pair<vector<int>, vector<int>> dialForAll(const Graph& graph, int source) {
    int n = graph.totalVertices;
    int maxCost = graph.maxEdgeCost;
    vector<int> distance(n + 1, INT_MAX);
    vector<int> pred(n + 1, -1);

    distance[source] = 0;

    vector<list<int>> buckets(maxCost + 1);
    int currentBucket = 0;
    int emptyBucketsInRow = 0;

    buckets[currentBucket].push_back(source);
    vector<bool> visited(n + 1, false);
    
    while (emptyBucketsInRow < maxCost + 1) {
        if (buckets[currentBucket].empty()) {
            currentBucket = (currentBucket + 1) % (maxCost + 1);
            emptyBucketsInRow++;
        } else {
            emptyBucketsInRow = 0;

            while (!buckets[currentBucket].empty()) {
                int node = buckets[currentBucket].front();
                buckets[currentBucket].pop_front();

                if (visited[node]) continue;
                visited[node] = true;

                for (const auto& neighborEdge : graph.neighborsList[node]) {
                    int neighbor = neighborEdge.first;
                    int cost = neighborEdge.second;
                    int value = distance[node] + cost;

                    if (distance[neighbor] > value) {
                        distance[neighbor] = value;
                        pred[neighbor] = node;
                        buckets[value % (maxCost + 1)].push_back(neighbor);
                    }
                }
            }
        }
    }

    return {distance, pred};
}

int dialForPair(const Graph& graph, int source, int target) {
    int n = graph.totalVertices;
    int maxCost = graph.maxEdgeCost;
    vector<int> distance(n + 1, INT_MAX);
    distance[source] = 0;

    vector<list<int>> buckets(maxCost + 1);
    int currentBucket = 0;
    int emptyBucketsInRow = 0;

    buckets[currentBucket].push_back(source);
    vector<bool> visited(n + 1, false);
    
    while (emptyBucketsInRow < maxCost + 1) {
        if (buckets[currentBucket].empty()) {
            currentBucket = (currentBucket + 1) % (maxCost + 1);
            emptyBucketsInRow++;
        } else {
            emptyBucketsInRow = 0;

            while (!buckets[currentBucket].empty()) {
                int node = buckets[currentBucket].front();
                buckets[currentBucket].pop_front();

                if (node == target) {
                    return distance[node];
                }

                if (visited[node]) continue;
                visited[node] = true;

                for (const auto& neighborEdge : graph.neighborsList[node]) {
                    int neighbor = neighborEdge.first;
                    int cost = neighborEdge.second;
                    int value = distance[node] + cost;
                    if (distance[neighbor] > value) {
                        distance[neighbor] = value;
                        buckets[value % (maxCost + 1)].push_back(neighbor);
                    }
                }
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
    string pathData = argv[4];
    string flag3 = argv[5];
    string pathOutput = argv[6];

    if (flag1 != "-d") {
        cerr << "Błąd wywołania - nieznana flaga " << flag1 << endl;
        return 1;
    }

    Graph graph = readGraphFromFile(pathGraph);

    if (flag2 == "-ss" && flag3 == "-oss") {
        vector<int> sources = readSources(pathData);
        double timeTotal = 0.0;

        for (int source : sources) {
            auto start = chrono::high_resolution_clock::now();
            dialForAll(graph, source);
            auto end = chrono::high_resolution_clock::now();
            timeTotal += chrono::duration<double>(end - start).count();
        }

        double avgTime = timeTotal / sources.size();
        writeResultSources(pathOutput, pathGraph, pathData, "dial", graph, graph.minEdgeCost, graph.maxEdgeCost, avgTime);

    } else if (flag2 == "-p2p" && flag3 == "-op2p") {
        vector<pair<int, int>> pairs = readPairs(pathData);
        vector<tuple<int, int, int>> results;

        for (const auto& [i, j] : pairs) {
            int pathLength = dialForPair(graph, i, j);
            results.emplace_back(i, j, pathLength);
        }

        writeResultPairs(pathOutput, pathGraph, pathData, "dial", graph, graph.minEdgeCost, graph.maxEdgeCost, results);

    } else {
        cerr << "Błąd wywołania - nieznana flaga " << flag2 << " lub " << flag3 << endl;
        return 1;
    }

    return 0;
}
