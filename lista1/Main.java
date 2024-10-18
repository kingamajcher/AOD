import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        try {
            if (args.length < 1) {
                System.err.println("Usage: java Main <input-file>");
                System.exit(1);
            }
            String path = args[0];
            System.out.println(path);
            Graph graph = new Graph(path);
            graph.printGraph();
            System.out.println("Is the graph directed? " + (graph.isDirected() ? "Yes" : "No"));

            DFS dfs = new DFS(graph);
            dfs.DFS(graph.getAdjacencyList().get(0).get(0) - 1);
        } catch (IOException e) {
            System.err.println("Error while trying to load file: " + e.getMessage());
        }
    }
}