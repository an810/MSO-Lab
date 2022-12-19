package src;

import java.util.Random;
public class Configs
{
    public static int numTrucks = 3;
    public static int numDrones = 3;
    public static int POP_SIZE = 10;
    public static int numCustoms;
    public static double vTruck = 30.0;
    public static double vDrone = 45.0;
    public static double timeLimitDrone = 0.5;
    public static int droneCapacity = 3;
    public static int timeHorizon;
    public static int[] xCor;
    public static int[] yCor;
    public static int[] releaseDate;
    public static double[][] matrix;
    public static int randInt(int lowerBound, int upperBound)
    {
        Random rand = new Random();
        int r = rand.nextInt(upperBound - lowerBound) + lowerBound;

        return r;
    }

    public static double randDouble()
    {
        Random rand = new Random();
        double r = rand.nextDouble();

        return r;
    }
}
