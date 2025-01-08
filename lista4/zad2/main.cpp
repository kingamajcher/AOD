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
    if (option == "--size" && argc >= 5) {
        int k = stoi(argv[2]);
        int degree = stoi(argv[4]);

        BipartiteGraph graph(k, degree);
        cout << "Generated bipartite graph with |V1| = 2^" << k << ", |V2| = 2^" << k << ", degree = " << degree << endl;

        auto start = chrono::high_resolution_clock::now();
        auto flow = graph.getMaxFlow();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        cout << "Maximum matching: " << flow << endl;

        if (argc >= 6 && string(argv[5]) == "--printMatching") {
            graph.printMatching();
        }

        if (argc >= 7 && string(argv[5]) == "--JuMP" && argc == 8) {
            string filename = argv[7];
            //exportToJuMP(graph, filename);
        }
        
        cerr << "Execution time: " << elapsed.count() << "s" << endl;

    } else if (option == "--tests") {
        ofstream outFile("testResults.txt");
        if (!outFile) {
            cerr << "Error: Unable to open file for writing test results.\n";
            return 1;
        }

        for (int k = 3; k <= 10; k++) {
            cout << k << endl;
            for (int degree = 1; degree <= k; ++degree) {
                double totalTime = 0.0;
                long long totalMatching = 0;

                int counts = 20;
                for (int i = 0; i < counts; i++) {
                    BipartiteGraph graph(k, degree);
                    auto start = chrono::high_resolution_clock::now();
                    auto flow = graph.getMaxFlow();
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> elapsed = end - start;
                    
                    totalTime += elapsed.count();
                    totalMatching += flow;
                }

                outFile << k << " " << degree << " " << totalMatching / counts << " " << totalTime / counts << "\n";
            }
        }
        outFile.close();
    } else {
        cerr << "Error: Invalid arguments\n";
        return 1;
    }

    return 0;
}
