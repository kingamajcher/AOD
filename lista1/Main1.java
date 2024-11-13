import java.util.*;
import java.io.*;

public class Main1 {
    public static void main(String[] args) {
        try {
            if (args.length < 2) {
                System.err.println("Usage: java Main1 <input-file> <search type> <parameters ( -t for tree)>");
                System.exit(1);
            }
            String path = args[0];
            Graph graph = new Graph(path);

            if (args[1].equals("BFS")) {
                System.out.println("\nBFS");
                BFS bfs = new BFS(graph);
                int startingVertex = graph.getAdjacencyList().get(0).get(0) - 1;
                long startTime = System.nanoTime();
                bfs.BFS(startingVertex);
                long endTime = System.nanoTime();
                bfs.printVisitedVertices();
                if (args.length == 3 && args[2].equals("-t")) {
                    bfs.printBFSTree();
                }
                System.out.println("\nDuration: " + (endTime - startTime) + " ns");
            }
            else if (args[1].equals("DFS")) {
                System.out.println("\nDFS");
                DFS dfs = new DFS(graph);
                int startingVertex = graph.getAdjacencyList().get(0).get(0) - 1;
                long startTime = System.nanoTime();
                dfs.DFS(startingVertex);
                long endTime = System.nanoTime();
                dfs.printVisitedVertices();
                if (args.length == 3 && args[2].equals("-t")) {
                    dfs.printDFSTree();
                }
                System.out.println("\nDuration: " + (endTime - startTime) + " ns");
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