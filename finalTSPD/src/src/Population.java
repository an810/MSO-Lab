package src;

import java.util.ArrayList;
public class Population {
    public static ArrayList<Indivisual> pop = new ArrayList<>(Configs.POP_SIZE);

    public static void initPop() {
        for (int i = 0; i < Configs.POP_SIZE; i++) {
            Indivisual indiv = new Indivisual();
            indiv.initIndiv1();
            indiv.initIndiv2();
            indiv.initIndiv3();
            pop.add(indiv);
        }
    }
    public static void printPop() {
        for (Indivisual indiv : pop) {
            int dim1 = indiv.dim1;
            int dim2 = indiv.dim2;
            int dim3 = indiv.dim3;

            System.out.println("Indivisual " + String.valueOf(pop.indexOf(indiv) + 1));

            System.out.println("Gen :" + indiv.gen);

            System.out.print("Drone1: ");
            for (int i = 0; i < dim1; i++)
            {
                System.out.print(indiv.truck1.get(i) + ": " + indiv.drone1.get(i) + " ");
            }
            System.out.println();

            System.out.print("Drone2: ");
            for (int i = 0; i < dim2; i++)
            {
                System.out.print(indiv.truck2.get(i) + ": " + indiv.drone2.get(i) + " ");
            }
            System.out.println();

            System.out.print("Drone3: ");
            for (int i = 0; i < dim3; i++)
            {
                System.out.print(indiv.truck3.get(i) + ": " + indiv.drone3.get(i) + " ");
            }
            System.out.println();

            System.out.print("Graph1: " + indiv.drone11);
            System.out.println();

            System.out.print("Graph2: " + indiv.drone22);
            System.out.println();

            System.out.print("Graph3: " + indiv.drone33);
            System.out.println();

            for (int j = 0; j < Configs.numDrones; j++)
            {
                System.out.println("Drone " + String.valueOf(j + 1) + ": " + indiv.queueDrone.get(j));
            }

            System.out.println("TimeTruck1: " + indiv.timeTruck1);
            System.out.println("TimeTruck2: " + indiv.timeTruck2);
            System.out.println("TimeTruck3: " + indiv.timeTruck3);
            System.out.println("TimeTotalTruck: " + indiv.totalTimeTruck);
        }
    }

    public static void printFitnesses()
    {
        for (int i = 0; i < Configs.POP_SIZE; i++)
        {
            System.out.println(pop.get(i).fitness);
        }
    }

    public static void printReleaseDate()
    {
        for (int i = 1; i <= Configs.numCustoms; i++)
        {
            System.out.println(Configs.releaseDate[i]);
        }
    }

    public static void printTotalReleaseDate()
    {
        System.out.print("Total Release Date: ");
        double total = 0.0;
        for (int i = 1; i <= Configs.numCustoms; i++)
        {
            total += Configs.releaseDate[i];
        }
        total /= 60;
        System.out.println(total);
    }
}