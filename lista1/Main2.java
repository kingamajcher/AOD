import java.io.*;

public class Main2 {
    public static void main(String[] args) {
        try {
            if (args.length < 1) {
                System.err.println("Usage: java Main <input-file>");
                System.exit(1);
            }
            String path = args[0];
            Graph graph = new Graph(path);

            TopologicalSort ts = new TopologicalSort(graph);
            ts.printTopologicalOrder();

        } catch (IOException e) {
            System.err.println("Error while trying to load file: " + e.getMessage());
        }
    }
}