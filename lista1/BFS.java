import java.util.*;

public class BFS {
    private List<List<Integer>> adjList;

    public BFS (Graph graph) {
        this.adjList = graph.getAdjacencyList();
    }
    public void BFS(int root) {
        boolean[] visited = new boolean[adjList.size()];
        int[] distance = new int[adjList.size()];
        int[] predecessor = new int[adjList.size()];
        Queue<Integer> queue = new LinkedList<>();

        Arrays.fill(distance, -1);
        Arrays.fill(predecessor, -1);

        visited[root] = true;
        distance[root] = 0;
        queue.add(root);

        while (!queue.isEmpty()) {
            int vertex = queue.poll();
            System.out.print((vertex + 1) + " ");

            for (int neighbor : adjList.get(vertex)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    distance[neighbor] = distance[vertex] + 1;
                    predecessor[neighbor] = vertex;
                    queue.add(neighbor);
                }
            }
        }
        System.out.println();
    }
}