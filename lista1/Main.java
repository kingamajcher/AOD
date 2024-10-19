import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        try {
            if (args.length < 2) {
                System.err.println("Usage: java Main <input-file> <search type>");
                System.exit(1);
            }
            String path = args[0];
            Graph graph = new Graph(path);
            graph.printGraph();
            System.out.println("Is the graph directed? " + (graph.isDirected() ? "Yes" : "No"));

            if (args[1].equals("BFS")) {
                System.out.println("\nBFS");
                BFS bfs = new BFS(graph);
                int startingVertex = graph.getAdjacencyList().get(0).get(0) - 1;
                bfs.BFS(startingVertex);
                bfs.printVisitedVertices();
                bfs.printBFSTree();
            }
            else if (args[1].equals("DFS")) {
                System.out.println("\nDFS");
                DFS dfs = new DFS(graph);
                dfs.DFS(graph.getAdjacencyList().get(0).get(0) - 1);
                dfs.printVisitedVertices();
                dfs.printBFSTree();
            }
            else {
                System.err.println("Invalid search type: " + args[1]);
                System.exit(1);
            }

        } catch (IOException e) {
            System.err.println("Error while trying to load file: " + e.getMessage());
        }
    }
}