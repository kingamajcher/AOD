// Kinga Majcher 272354

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <chrono>
#include <tuple>
#include <climits>
#include "Graph.h"

using namespace std;

struct Bucket {
    int minRange;
    int maxRange;
    int bucketWidth;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> container;

    Bucket(int minR, int maxR, int width)
        : minRange(minR), maxRange(maxR), bucketWidth(width) {}
};

pair<vector<int>, vector<int>> radixHeapForAll(const Graph &graph, int source) {
    int n = graph.totalVertices;
    int maxCost = graph.maxEdgeCost;

    vector<Bucket> buckets;
    vector<int> distances(n + 1, INT_MAX);
    vector<int> predecessors(n + 1, -1);
    distances[source] = 0;

    int currentMaxRange = 0;
    int currentMinRange = 0;

    int K = static_cast<int>(ceil(log2(maxCost + 1))) + 2;

    for (int k = 0; k < K - 1; ++k) {
        int currentWidth = (k < 2) ? 1 : (1 << (k - 1));
        currentMaxRange = currentMinRange + currentWidth - 1;
        buckets.emplace_back(currentMinRange, currentMaxRange, currentWidth);
        
        currentMinRange = currentMaxRange + 1;
    }

    buckets.emplace_back(currentMinRange, INT_MAX, INT_MAX - currentMinRange + 1);

    int bucketsSize = buckets.size();

    buckets[0].container.emplace(0, source);
    int currentNonEmptyBucketIndex = 0;

    while (currentNonEmptyBucketIndex < bucketsSize) {
        if (buckets[currentNonEmptyBucketIndex].container.empty()) {
            buckets[currentNonEmptyBucketIndex].container = {};
            currentNonEmptyBucketIndex++;
            continue;
        }

        while (!buckets[currentNonEmptyBucketIndex].container.empty()) {
            auto [currentDist, currentNode] = buckets[currentNonEmptyBucketIndex].container.top();
            buckets[currentNonEmptyBucketIndex].container.pop();

            for (const auto &edge : graph.neighborsList[currentNode]) {
                int neighbor = edge.first;
                int weight = edge.second;
                int newDist = currentDist + weight;

                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    predecessors[neighbor] = currentNode;

                    for (int i = currentNonEmptyBucketIndex; i < bucketsSize; ++i) {
                        if (newDist >= buckets[i].minRange && newDist <= buckets[i].maxRange) {
                            buckets[i].container.emplace(newDist, neighbor);
                            break;
                        }
                    }
                }
            }
        }
        currentNonEmptyBucketIndex++;
    }

    return {distances, predecessors};
}

int radixHeapForPair(const Graph &graph, int source, int target) {
    int n = graph.totalVertices;
    int maxCost = graph.maxEdgeCost;

    vector<Bucket> buckets;
    vector<int> distances(n + 1, INT_MAX);
    distances[source] = 0;


    int currentMaxRange = 0;
    int currentMinRange = 0;

    int K = static_cast<int>(ceil(log2(maxCost + 1))) + 2;

    for (int k = 0; k < K - 1; ++k) {
        int currentWidth = (k < 2) ? 1 : (1 << (k - 1));
        currentMaxRange = currentMinRange + currentWidth - 1;
        buckets.emplace_back(currentMinRange, currentMaxRange, currentWidth);
        
        currentMinRange = currentMaxRange + 1;
    }

    buckets.emplace_back(currentMinRange, INT_MAX, INT_MAX - currentMinRange + 1);

    buckets[0].container.emplace(0, source);
    int currentNonEmptyBucketIndex = 0;

    int bucketsSize = buckets.size();

    while (currentNonEmptyBucketIndex < bucketsSize) {
        if (buckets[currentNonEmptyBucketIndex].container.empty()) {
            buckets[currentNonEmptyBucketIndex].container = {};
            currentNonEmptyBucketIndex++;
            continue;
        }

        while (!buckets[currentNonEmptyBucketIndex].container.empty()) {
            auto [currentDist, currentNode] = buckets[currentNonEmptyBucketIndex].container.top();
            buckets[currentNonEmptyBucketIndex].container.pop();

            if (currentNode == target) {
                return currentDist;
            }

            for (const auto &edge : graph.neighborsList[currentNode]) {
                int neighbor = edge.first;
                int weight = edge.second;
                int newDist = currentDist + weight;

                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;

                    for (int i = currentNonEmptyBucketIndex; i < bucketsSize; ++i) {
                        if (newDist >= buckets[i].minRange && newDist <= buckets[i].maxRange) {
                            buckets[i].container.emplace(newDist, neighbor);
                            break;
                        }
                    }
                }
            }
        }
        currentNonEmptyBucketIndex++;
    }

    return distances[target];
}

int main(int argc, char *argv[]) {
    if (argc < 7) {
        cerr << "Błąd wywołania - niepoprawna liczba argumentów" << endl;
        return 1;
    }

    string flag1 = argv[1];
    string pathGraph = argv[2];
    string flag2 = argv[3];
    string pathSources = argv[4];
    string flag3 = argv[5];
    string pathOutput = argv[6];

    Graph graph = readGraphFromFile(pathGraph);

    if (flag2 == "-ss" && flag3 == "-oss") {
        vector<int> sources = readSources(pathSources);
        double timeTotal = 0.0;

        for (int source : sources) {
            auto start = chrono::high_resolution_clock::now();
            radixHeapForAll(graph, source);
            auto end = chrono::high_resolution_clock::now();
            timeTotal += chrono::duration<double>(end - start).count();
        }

        double avgTime = timeTotal / sources.size();
        writeResultSources(pathOutput, pathGraph, pathSources, "radixheap", graph, graph.minEdgeCost, graph.maxEdgeCost, avgTime);

    } else if (flag2 == "-p2p" && flag3 == "-op2p") {
        vector<pair<int, int>> pairs = readPairs(pathSources);
        vector<tuple<int, int, int>> results;

        for (const auto &[i, j] : pairs) {
            int pathLength = radixHeapForPair(graph, i, j);
            results.emplace_back(i, j, pathLength);
        }

        writeResultPairs(pathOutput, pathGraph, pathSources, "radixheap", graph, graph.minEdgeCost, graph.maxEdgeCost, results);

    } else {
        cerr << "Błąd wywołania - nieznana flaga " << flag2 << " lub " << flag3 << endl;
        return 1;
    }

    return 0;
}
