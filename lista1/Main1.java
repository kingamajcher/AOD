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
                bfs.BFS(startingVertex);
                bfs.printVisitedVertices();
                if (args.length == 3 && args[2].equals("-t")) {
                    bfs.printBFSTree();
                }
            }
            else if (args[1].equals("DFS")) {
                System.out.println("\nDFS");
                DFS dfs = new DFS(graph);
                dfs.DFS(graph.getAdjacencyList().get(0).get(0) - 1);
                dfs.printVisitedVertices();
                if (args.length == 3 && args[2].equals("-t")) {
                    dfs.printDFSTree();
                }
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