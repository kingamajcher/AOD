import java.io.*;
import java.util.*;

public class Graph {
    private boolean directed; // true -directed graph, false - undirected graph
    private int n: // number of vertices
    private int m; // number of edges
    private List<List<Integer>> adjList; // adjacency list

    public Graph(String filename) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(filename));
        String line = br.readLine();

        // reading the type of graph
        if (line.equals("D")) {
            directed = true;
        }
        else if (line.equals("U")) {
            directed = false;
        }
        else {
            throw new IOException(filename + " is not a valid graph file");
        }

        // reading the number of vertices
        n = Integer.parseInt(br.readLine());
        if (n <= 0) {
            throw new IOException(filename + " is not a valid graph file");
        }

        // reading the number of edges
        m = Integer.parseInt(br.readLine());
        if (m <= 0) {
            throw new IOException(filename + " is not a valid graph file");
        }

        // initializing adjacency list
        adjList = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adjList.add(new ArrayList<>());
        }

        //reading pairs of vertices and adding edges
        for (int i = 0; i < m; i++) {
            line = br.readLine();
            String[] tokens = line.split(" ");
            int e1 = Integer.parseInt(tokens[0] - 1);
            int e2 = Integer.parseInt(tokens[1] - 1);

            addEdge(e1, e2);
        }

        br.close();
    }

    // adding edges to graph
    private void addEdge(int e1, int e2) {
        adjList.get(e1).add(e2);
        if (!directed) {
            adjList.get(e2).add(e1);
        }
    }

    // printing the graph
    public void printGraph() {
        for (int i = 0; i < n; i++) {
            System.out.print("Vertex: " + (i + 1) + ": ");
            for (int neighbor : adjList.get(i)) {
                System.out.print((neighbor + 1) + " ");
            }
            System.out.println();
        }
    }

    // chcecking whether graph is directed
    public boolean isDirected() {
        return directed;
    }
}