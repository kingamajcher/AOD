#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Error: insufficient arguments.\n";
        return 1;
    }

    string option = argv[1];
    if (option == "--size" && argc >= 3) {
        int k = stoi(argv[2]);


        Graph graph(k);
        cout << "Generated hypercube of size " << k << endl;

        auto start = chrono::high_resolution_clock::now();
        auto [maxFlow, augmentingPaths] = graph.edmondsKarp();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        cout << "Maximum flow: " << maxFlow << endl;
        cout << "Augmenting paths count: " << augmentingPaths << endl;

        if (argc >= 4 && string(argv[3]) == "--printFlow") {
            graph.printFlowDetails();
        }

        cerr << "Execution time: " << elapsed.count() << "s" << endl;

    } else if (option == "--tests") {
        ofstream outFile("testResults.txt");
        if (!outFile) {
            cerr << "Error: Unable to open file for writing test results.\n";
            return 1;
        }

        for (int k = 1; k <= 16; k++) {
            cout << k << endl;
            double totalTime = 0.0;
            long long totalFlow = 0;
            long long totalAugmentingPaths = 0;

            int counts = 20;
            for (int i = 0; i < counts; ++i) {

                Graph graph(k);
                auto start = chrono::high_resolution_clock::now();
                auto [flow, pathsCount] = graph.edmondsKarp();
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> elapsed = end - start;

                totalTime += elapsed.count();
                totalFlow += flow;
                totalAugmentingPaths += pathsCount;
            }

            outFile << k << " " << totalFlow / counts << " " << totalAugmentingPaths / counts << " " << totalTime / counts << "\n";
        }
        outFile.close();

    } else {
        cerr << "Error: Invalid arguments\n";
        return 1;
    }

    return 0;
}
