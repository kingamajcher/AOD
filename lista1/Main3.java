import java.io.*;
import java.util.*;

public class Main3 {
    public static void main(String[] args) {
        try {
            if (args.length < 1) {
                System.err.println("Usage: java Main3 <input-file>");
                System.exit(1);
            }
            String path = args[0];
            Graph graph = new Graph(path);

            StronglyConnectedComponents sccFinder = new StronglyConnectedComponents(graph);

            int numSCCs = sccFinder.getNumberOfSCCs();
            List<Integer> sccSizes = sccFinder.getSizesOfSCCs();

            System.out.println("Number of Strongly Connected Components: " + numSCCs);
            System.out.println("Sizes of Strongly Connected Components: " + sccSizes);

            if (graph.getVerticesNum() <= 200) {
                sccFinder.printSCCs();
            }

        } catch (IOException e) {
            System.err.println("Error while trying to load file: " + e.getMessage());
        }
    }
}