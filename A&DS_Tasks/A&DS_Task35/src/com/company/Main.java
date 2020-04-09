package com.company;

import java.io.*;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(new File("in.txt"));
        FileWriter out = new FileWriter("out.txt");

        int m = sc.nextInt();
        int n = sc.nextInt();
        int numCombination = 1 << m;
        int numShifts = m - 1;

        boolean[][] transitionMatrix = new boolean[numCombination][numCombination];

        for (int i = 0; i < numCombination; i++) {
            for (int j = 0; j < numCombination; j++) {
                transitionMatrix[i][j] = isTransition(i, j, numShifts);
            }
        }

        BigInteger[][] resultMatrix = new BigInteger[n][numCombination];

        for (int i = 0; i < numCombination; i++) {
            resultMatrix[0][i] = BigInteger.valueOf(1);
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < numCombination; j++) {
                resultMatrix[i][j] = BigInteger.valueOf(0);

                for (int k = 0; k < numCombination; k++) {
                    if (transitionMatrix[j][k]) {
                        resultMatrix[i][j] = resultMatrix[i][j].add(resultMatrix[i - 1][k]);
                    }
                }
            }
        }

        BigInteger result = BigInteger.valueOf(0);

        for (int i = 0; i < numCombination; i++) {
            result = result.add(resultMatrix[n - 1][i]);
        }

        out.write(String.valueOf(result));

        out.close();
    }

    private static boolean isTransition(int a, int b, int numShifts) {
       for (int i = 0; i < numShifts; i++) {
            if ((((a & 3) == 0) && ((b & 3) == 0)) || (((a & 3) == 3) && ((b & 3) == 3))) {
                return false;
            }

            a = a >> 1;
            b = b >> 1;
        }

        return true;
    }
}
