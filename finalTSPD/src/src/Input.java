package src;

import java.util.Scanner;
import java.lang.Math;
public class Input
{
    public static void input()
    {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter dimension: ");
        int dim = in.nextInt();
        System.out.print("Enter time horizon: ");
        Configs.timeHorizon = in.nextInt();
        in.nextLine();

        Configs.xCor = new int[dim];
        Configs.yCor = new int[dim];
        Configs.releaseDate = new int[dim];
        Configs.matrix = new double[dim][dim];
        Configs.numCustoms = dim - 1;
        for (int i = 0; i < dim; i++)
        {
            String nextLine = in.nextLine();
            String[] ints = nextLine.split(" ");
            Configs.xCor[i] = Integer.parseInt(ints[0]);
            Configs.yCor[i] = Integer.parseInt(ints[1]);
            Configs.releaseDate[i] = Integer.parseInt(ints[2]);
        }
        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                if (i == j)
                {
                    Configs.matrix[i][j] = 0.0;
                }
                else
                {
                    Configs.matrix[i][j] = Math.sqrt(Math.pow((double) Configs.xCor[j] - Configs.xCor[i], 2) + Math.pow((double) Configs.yCor[j] - Configs.yCor[i], 2));
                }
            }
        }
    }
}
