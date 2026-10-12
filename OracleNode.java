// This is the script emulates the Oracle Node
// 1. Contructs graph topology from the oracle-node-config-file

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class OracleNode {

    public static void main(String[] args) throws FileNotFoundException {
        if (args.length != 1) {
            System.out.println("Usage : java OracleNode <Config-file>");
            return;
        }

        File file = new File(args[0]);

        System.out.println("Configuration File : " + file);

        List<String[]> rows = new ArrayList<>();

        try (Scanner sc = new Scanner(file)) {
            while (sc.hasNextLine()) {
                String line = sc.nextLine().trim();

                if (line.isEmpty() || line.startsWith("#")) {
                    continue;
                }

                String[] values = line.split("\\s+");
                rows.add(values);
            }
        }

        if (rows.isEmpty()) {
            System.out.println("Error: Empty configuration file");
            return;
        }

        int n = rows.get(0).length + 1;

        System.out.println("Number of nodes: " + n);

        if (n > 26) {
            System.out.println("Error: Maximum 26 nodes allowed");
            return;
        }

        if (rows.size() != n - 1) {
            System.out.println("Error: Incorrect number of rows");
            return;
        }

        for (int i = 0; i < rows.size(); i++) {
            int expected = n - i - 1;

            if (rows.get(i).length != expected) {
                System.out.println("Error: Invalid number of entries in row " + i);
                return;
            }
        }

        int[][] cost = new int[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cost[i][j] = -1;
            }

            cost[i][i] = 0;
        }

        for (int i = 0; i < rows.size(); i++) {
            for (int j = 0; j < rows.get(i).length; j++) {
                int neighbor = i + j + 1;
                int c = Integer.parseInt(rows.get(i)[j]);

                cost[i][neighbor] = c;
                cost[neighbor][i] = c;
            }
        }

    }
}
