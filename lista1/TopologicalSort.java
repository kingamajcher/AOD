import java.util.*;

public class TopologicalSort {
    private Stack<Integer> topologicalOrder = new Stack<>();
    private List<List<Integer>> adjList;
    private boolean[] visited;
    private boolean[] recursionStack;
    private int numVertices;
    private boolean hasCycle = false;

    // constructor of TopologicalSort class
    public TopologicalSort(Graph graph) {
        this.adjList = graph.getAdjacencyList();
        this.numVertices = adjList.size();
        this.topologicalOrder = new Stack<>();
        this.visited = new boolean[numVertices];
        this.recursionStack = new boolean[numVertices];  // Initialize the recursion stack

        for (int vertex = 0; vertex < numVertices; vertex++) {
            if (!visited[vertex]) {
                DFS(vertex);
            }
        }
    }

    // recursive method for performing DFS and detecting cycles
    private void DFS(int vertex) {
        visited[vertex] = true;
        recursionStack[vertex] = true;

        for (int neighbor : adjList.get(vertex)) {
            if (!visited[neighbor]) {
                DFS(neighbor);
            } else if (recursionStack[neighbor]) {
                // If the neighbor is in the recursion stack, a cycle exists
                hasCycle = true;
                return;
            }
        }

        recursionStack[vertex] = false;
        topologicalOrder.push(vertex);
    }

    // method to check if the graph contains a cycle
    public boolean hasCycle() {
        return hasCycle;
    }

    // method for getting the topological order
    public Stack<Integer> getTopologicalOrder() {
        if (hasCycle) {
            throw new IllegalStateException("Cannot perform topological sort on a graph with cycles.");
        }
        return topologicalOrder;
    }

    // method for printing the topological order
    public void printTopologicalOrder() {
        if (hasCycle) {
            System.out.println("Cannot perform topological sort on a graph with cycles.");
            return;
        }

        if (numVertices <= 200) {
            System.out.print("Topological Sort: ");
            while (!topologicalOrder.isEmpty()) {
                System.out.print((topologicalOrder.pop() + 1) + " ");  // Print in reverse order
            }
            System.out.println();
        }
        else {
            System.out.println("Topological sort performed. " +
                    "Graph has more than 200 vertices so their order is not printed.");
        }

    }
}