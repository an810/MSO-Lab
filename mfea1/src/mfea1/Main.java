package mfea1;
import java.util.ArrayList;
import java.util.List;

//import tasks.Knapsack;
import tasks.TSP;

public class Main {
    public static void main(String[] args) {
        List<Task> tasks = new ArrayList<>();
        tasks.add(new TSP("C:\\Users\\Admin\\eclipse-workspace\\mfea1\\src\\data\\tsp\\a280.tsp"));
        tasks.add(new TSP("C:\\Users\\Admin\\eclipse-workspace\\mfea1\\src\\data\\tsp\\kroA150.tsp"));
        MFEA g = new MFEA(tasks, 50, 0.3, 50);
        g.run(50);
    }
}
