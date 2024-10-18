import java.util.*;

public class DFS {
    private List<List<Integer>> adjList;

    public DFS (Graph graph) {
        this.adjList = graph.getAdjacencyList();
    }
    public void DFS(int root) {
        boolean[] visited = new boolean[adjList.size()];
        int[] distance = new int[adjList.size()];

        Arrays.fill(distance, -1);

        dfsRecursive(root, visited);

        System.out.println();
    }

    private void dfsRecursive(int vertex, boolean[] visited) {
        visited[vertex] = true;
        System.out.print((vertex + 1) + " ");

        for (int neighbor : adjList.get(vertex)) {
            if (!visited[neighbor]) {
                dfsRecursive(neighbor, visited);
            }
        }
    }
}