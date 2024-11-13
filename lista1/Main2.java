import java.io.*;

public class Main2 {
    public static void main(String[] args) {
        try {
            if (args.length < 1) {
                System.err.println("Usage: java Main2 <input-file>");
                System.exit(1);
            }
            String path = args[0];
            Graph graph = new Graph(path);

            long startTime = System.nanoTime();
            TopologicalSort ts = new TopologicalSort(graph);
            long endTime = System.nanoTime();
            ts.printTopologicalOrder();

            System.out.println("\nDuration: " + (endTime - startTime) + " ns");

        } catch (IOException e) {
            System.err.println("Error while trying to load file: " + e.getMessage());
        }
    }
}