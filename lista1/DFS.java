import java.util.*;

public class DFS {
    private List<List<Integer>> adjList;
    private List<Integer> visitedVertices;
    private List<int[]> visitedTree;
    private int root;

    // constructor to initialize DFS with given graph
    public DFS (Graph graph) {
        this.adjList = graph.getAdjacencyList();
        this.visitedVertices = new ArrayList<>();
        this.visitedTree = new ArrayList<>();
    }

    // method for performing DFS starting from a given root
    public void DFS(int root) {
        boolean[] visited = new boolean[adjList.size()];
        int[] distance = new int[adjList.size()];
        this.root = root;

        Arrays.fill(distance, -1);
        dfsRecursive(root, visited);
        System.out.println();
    }
    // recursive method for performing DFS
    private void dfsRecursive(int vertex, boolean[] visited) {
        visited[vertex] = true;
        visitedVertices.add(vertex);

        for (int neighbor : adjList.get(vertex)) {
            if (!visited[neighbor]) {
                dfsRecursive(neighbor, visited);
                visitedTree.add(new int[]{vertex, neighbor});
            }
        }
    }

    // method for getting the list of visited vertices
    public List<Integer> getVisitedVertices() {
        return visitedVertices;
    }

    // method for printing visited vertices
    public void printVisitedVertices() {
        System.out.print("Visited vertices: ");
        for (int vertex : visitedVertices) {
            System.out.print((vertex + 1) + " ");
        }
        System.out.println();
    }

    // method for printing the BST tree
    public void printBFSTree() {
        Map<Integer, List<Integer>> adjacencyList = new HashMap<>();

        for (int[] edge : visitedTree) {
            adjacencyList.computeIfAbsent(edge[0], k -> new ArrayList<>()).add(edge[1]);
        }

        int treeHeight = computeHeight(root, adjacencyList);
        printTreeRecursive(root, 0, adjacencyList, new boolean[treeHeight]);
    }

    // recursive helper method
    private void printTreeRecursive(int node, int depth, Map<Integer, List<Integer>> adjacencyList, boolean[] isLastChild) {
        for (int i = 0; i < depth; i++) {
            if (isLastChild[i]) {
                System.out.print("   ");
            } else {
                System.out.print("|  ");
            }
        }
        System.out.println("+- " + (node + 1));

        List<Integer> children = adjacencyList.get(node);
        if (children == null) {
            return;
        }

        for (int i = 0; i < children.size(); i++) {
            isLastChild[depth] = (i == children.size() - 1);
            printTreeRecursive(children.get(i), depth + 1, adjacencyList, isLastChild);
        }
    }

    // helper method for computing height of a tree
    private int computeHeight(int root, Map<Integer, List<Integer>> adjacencyList) {
        if (!adjacencyList.containsKey(root)) {
            return 1;
        }

        int maxHeight = 0;
        for (int child : adjacencyList.get(root)) {
            maxHeight = Math.max(maxHeight, computeHeight(child, adjacencyList));
        }
        return maxHeight + 1;
    }
}