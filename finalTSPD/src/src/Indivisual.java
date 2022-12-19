package src;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.lang.Math;
public class Indivisual
{
    //init
    public ArrayList<Integer> gen;
    public ArrayList<Double> genDouble;
    public ArrayList<Integer> truck1;
    public ArrayList<Integer> truck2;
    public ArrayList<Integer> truck3;
    public double timeTruck1;
    public double timeTruck2;
    public double timeTruck3;
    public double totalTimeTruck;
    public ArrayList<Double> genDouble1;
    public ArrayList<Double> genDouble2;
    public ArrayList<Double> genDouble3;
    public ArrayList<ArrayList<Integer>> drone1;
    public ArrayList<ArrayList<Integer>> drone2;
    public ArrayList<ArrayList<Integer>> drone3;
    public int dim;
    public int dim1;
    public int dim2;
    public int dim3;

    public double fitness;



    public Indivisual()
    {
        gen = new ArrayList<>();
        genDouble = new ArrayList<>();
        truck1 = new ArrayList<>();
        truck2 = new ArrayList<>();
        truck3 = new ArrayList<>();
        genDouble1 = new ArrayList<>();
        genDouble2 = new ArrayList<>();
        genDouble3 = new ArrayList<>();
        drone1 = new ArrayList<>();
        drone2 = new ArrayList<>();
        drone3 = new ArrayList<>();
        dim = Configs.numCustoms + 3;
        dim1 = 0;
        dim2 = 0;
        dim3 = 0;
        timeTruck1 = 0.0;
        timeTruck2 = 0.0;
        timeTruck3 = 0.0;
        totalTimeTruck = 0.0;
        fitness = 0;

        queueNum = new LinkedList<>();
        queuePack = new LinkedList<>();
        queueDrone = new LinkedList<>();
        drone11 = new ArrayList<>();
        drone22 = new ArrayList<>();
        drone33 = new ArrayList<>();
        droneNum1 = new ArrayList<>();
        droneNum2 = new ArrayList<>();
        droneNum3 = new ArrayList<>();
    }

    public void initIndiv1()
    {
        for (int i = 1; i <= Configs.numCustoms; i++)
        {
            gen.add(i);
            genDouble.add(Configs.randDouble());
        }
        gen.add(0);
        gen.add(0);
        genDouble.add(Configs.randDouble());
        genDouble.add(Configs.randDouble());
        genDouble.add(Configs.randDouble());
        Collections.shuffle(gen);
        gen.add(0, 0);
        asignValue();
        initDrone();
    }

    public void initIndiv2()
    {
        graph();
        asignQueuePack();
    }

    public void initIndiv3()
    {
        for (int i = 1; i < dim1; i++)
        {
            timeTruck1 += Configs.matrix[truck1.get(i - 1)][truck1.get(i)];
        }
        for (int i = 1; i < dim2; i++)
        {
            timeTruck2 += Configs.matrix[truck2.get(i - 1)][truck2.get(i)];
        }
        for (int i = 1; i < dim3; i++)
        {
            timeTruck3 += Configs.matrix[truck3.get(i - 1)][truck3.get(i)];
        }
        timeTruck1 /= Configs.vTruck;
        timeTruck2 /= Configs.vTruck;
        timeTruck3 /= Configs.vTruck;
        totalTimeTruck = timeTruck1 + timeTruck2 + timeTruck3;
    }

    public void evaluate()
    {
        double time = 0.0;

        for (int i = 0; i < Configs.numDrones; i++)
        {
            time += queueDrone.get(i);
        }
        fitness = 1 / time;
    }
    
    private void asignValue()
    {
        int index = 0;
        do
        {
            truck1.add(gen.get(index));
            genDouble1.add(genDouble.get(index));
            ArrayList<Integer> newArray = new ArrayList<>();
            drone1.add(newArray);
            dim1++;
            index++;
        } while (index < dim && gen.get(index) != 0);
        do
        {
            truck2.add(gen.get(index));
            genDouble2.add(genDouble.get(index));
            ArrayList<Integer> newArray = new ArrayList<>();
            drone2.add(newArray);
            dim2++;
            index++;
        } while (index < dim && gen.get(index) != 0);
        do
        {
            truck3.add(gen.get(index));
            genDouble3.add(genDouble.get(index));
            ArrayList<Integer> newArray = new ArrayList<>();
            drone3.add(newArray);
            dim3++;
            index++;
        } while (index < dim && gen.get(index) != 0);
    }

    private void initDrone()
    {
        initDrone1();
        initDrone2();
        initDrone3();
    }

    private void initDrone1()
    {
        for (int i = 0; i < dim1; i++)
        {
            double value = genDouble1.get(i);
            if (truck1.get(i) != 0)
            {
                for (int j = 0; j <= i; j++)
                {
                    if (value > (double) j / (i + 1) && value <= (double) (j + 1) / (i + 1))
                    {
                        drone1.get(j).add(truck1.get(i));
                    }
                }
            }
        }
    }

    private void initDrone2()
    {
        for (int i = 0; i < dim2; i++)
        {
            double value = genDouble2.get(i);
            if (truck2.get(i) != 0)
            {
                for (int j = 0; j <= i; j++)
                {
                    if (value > (double) j / (i + 1) && value <= (double) (j + 1) / (i + 1))
                    {
                        drone2.get(j).add(truck2.get(i));
                    }
                }
            }
        }
    }

    private void initDrone3()
    {
        for (int i = 0; i < dim3; i++)
        {
            double value = genDouble3.get(i);
            if (truck3.get(i) != 0)
            {
                for (int j = 0; j <= i; j++)
                {
                    if (value > (double) j / (i + 1) && value <= (double) (j + 1) / (i + 1))
                    {
                        drone3.get(j).add(truck3.get(i));
                    }
                }
            }
        }
    }

    //evaluation
    public LinkedList<Integer> queueNum;
    public LinkedList<Double> queuePack;
    public LinkedList<Double> queueDrone;

    public ArrayList<Integer> droneNum1;
    public ArrayList<Integer> droneNum2;
    public ArrayList<Integer> droneNum3;
    public ArrayList<ArrayList<Integer>> drone11;
    public ArrayList<ArrayList<Integer>> drone22;
    public ArrayList<ArrayList<Integer>> drone33;
    public double[] timeUpdate1;
    public double[] timeUpdate2;
    public double[] timeUpdate3;
    public ArrayList<ArrayList<Double>> timeFinish1;
    public ArrayList<ArrayList<Double>> timeFinish2;
    public ArrayList<ArrayList<Double>> timeFinish3;

    private void graph()
    {
        timeFinish1 = new ArrayList<>();
        timeFinish2 = new ArrayList<>();
        timeFinish3 = new ArrayList<>();

        asignDrone1();
        asignDrone2();
        asignDrone3();
    }

    private void asignDrone1()
    {
        for (int i = 0; i < dim1; i++)
        {
            int size = drone1.get(i).size();
            if (size != 0)
            {
                ArrayList<Integer> newArray = drone1.get(i);
                ArrayList<Double> newArray1 = new ArrayList<>(newArray.size());

                drone11.add(newArray);
                timeFinish1.add(newArray1);
                droneNum1.add(truck1.get(i));
            }
        }
    }

    private void asignDrone2()
    {
        for (int i = 0; i < dim2; i++)
        {
            int size = drone2.get(i).size();
            if (size != 0)
            {
                ArrayList<Integer> newArray = drone2.get(i);
                ArrayList<Double> newArray1 = new ArrayList<>(newArray.size());

                drone22.add(newArray);
                timeFinish2.add(newArray1);
                droneNum2.add(truck2.get(i));
            }
        }
    }

    private void asignDrone3()
    {
        for (int i = 0; i < dim3; i++)
        {
            int size = drone3.get(i).size();
            if (size != 0)
            {
                ArrayList<Integer> newArray = drone3.get(i);
                ArrayList<Double> newArray1 = new ArrayList<>(newArray.size());

                drone33.add(newArray);
                timeFinish3.add(newArray1);
                droneNum3.add(truck3.get(i));
            }
        }
    }

    private void asignQueuePack()
    {
        int size1 = drone11.size();
        int size2 = drone22.size();
        int size3 = drone33.size();
        for (int i = 0; i < Configs.numDrones; i++)
        {
            queueDrone.add(0.0);
        }
        timeUpdate1 = new double[drone11.size()];
        timeUpdate2 = new double[drone22.size()];
        timeUpdate3 = new double[drone33.size()];
        if (drone11.size() > 0)
        {
            timeUpdate1[0] = 0.0;
        }
        if (drone22.size() > 0)
        {
            timeUpdate2[0] = 0.0;
        }
        if (drone33.size() > 0)
        {
            timeUpdate3[0] = 0.0;
        }

        int index = 0;
        while (index < size1 || index < size2 || index < size3)
        {
            asignQueuePackOneTime(index);
            asignQueueDroneOneTime(index);
            index++;
        }
    }

    private void asignQueuePackOneTime(int index)
    {
        int size1 = drone11.size();
        int size2 = drone22.size();
        int size3 = drone33.size();

        if (index < size1)
        {
            int size = drone11.get(index).size();
            double time = 0.0;
            int timeUpdate1Index = 0;

            if (index > 0)
            {
                double distance = Configs.matrix[droneNum1.get(index - 1)][droneNum1.get(index)];
                time = distance / Configs.vTruck - distance / Configs.vDrone;
                timeUpdate1Index = index - 1;
            }
            for (int i = 0; i < size; i++)
            {
                queueNum.addLast(drone11.get(index).get(i));
                queuePack.addLast(Math.max((double) Configs.releaseDate[drone11.get(index).get(i)] / 60, timeUpdate1[timeUpdate1Index] + time));
            }
        }
        if (index < size2)
        {
            int size = drone22.get(index).size();
            double time = 0.0;
            int timeUpdate2Index = 0;

            if (index != 0)
            {
                double distance = Configs.matrix[droneNum2.get(index - 1)][droneNum2.get(index)];
                time = distance / Configs.vTruck - distance / Configs.vDrone;
                timeUpdate2Index = index - 1;
            }
            for (int i = 0; i < size; i++)
            {
                queueNum.addLast(drone22.get(index).get(i));
                queuePack.addLast(Math.max((double) Configs.releaseDate[drone22.get(index).get(i)] / 60, timeUpdate2[timeUpdate2Index] + time) / 60);
            }
        }
        if (index < size3)
        {
            int size = drone33.get(index).size();
            double time = 0.0;
            int timeUpdate3Index = 0;

            if (index != 0)
            {
                double distance = Configs.matrix[droneNum3.get(index - 1)][droneNum3.get(index)];
                time = distance / Configs.vTruck - distance / Configs.vDrone;
                timeUpdate3Index = index - 1;
            }
            for (int i = 0; i < size; i++)
            {
                queueNum.addLast(drone33.get(index).get(i));
                queuePack.addLast(Math.max((double) Configs.releaseDate[drone33.get(index).get(i)] / 60, timeUpdate3[timeUpdate3Index] + time));
            }
        }
    }

    private void asignQueueDroneOneTime(int index)
    {
        int i = 0;
        int times = Configs.randInt(1, Configs.droneCapacity + 1);
        if (queueDrone.get(0) <= queueDrone.get(1) && queueDrone.get(0) <= queueDrone.get(2))
        {
            double t = queueDrone.get(0);
            cycle1(index, i, times, t);
        }
        else if (queueDrone.get(1) <= queueDrone.get(0) && queueDrone.get(1) <= queueDrone.get(2))
        {
            double t = queueDrone.get(1);
            cycle2(index, i, times, t);
        }
        else
        {
            double t = queueDrone.get(2);
            cycle3(index, i, times, t);
        }
        if (index < timeFinish1.size())
        {
            processTimeUpdate1(index);
        }
        if (index < timeFinish2.size())
        {
            processTimeUpdate2(index);
        }
        if (index < timeFinish3.size())
        {
            processTimeUpdate3(index);
        }
    }

    private void cycle1(int index, int i, int times, double t)
    {
        ArrayList<Integer> nums = new ArrayList<>();

        while (queuePack.size() > 0 && i < times)
        {
            double r = queuePack.getFirst();
            queuePack.removeFirst();
            nums.add(queueNum.getFirst());
            queueNum.removeFirst();
            if (t < r)
            {
                t = r;
            }

            i++;
        }

        double valueDrone = t;
        for (int j = 0; j < nums.size(); j++)
        {
            valueDrone += updateTimeFinish(index, nums.get(j), j + 1, t);
        }
        queueDrone.set(0, queueDrone.get(0) + valueDrone);

        if (queuePack.size() > 0)
        {
            i = 0;
            times = Configs.randInt(1, Configs.droneCapacity + 1);
            if (queueDrone.get(0) <= queueDrone.get(1) && queueDrone.get(0) <= queueDrone.get(2))
            {
                t = queueDrone.get(0);
                cycle1(index, i, times, t);
            }
            else if (queueDrone.get(1) <= queueDrone.get(0) && queueDrone.get(1) <= queueDrone.get(2))
            {
                t = queueDrone.get(1);
                cycle2(index, i, times, t);
            }
            else
            {
                t = queueDrone.get(2);
                cycle3(index, i, times, t);
            }
        }
    }

    private void cycle2(int index, int i, int times, double t)
    {
        ArrayList<Integer> nums = new ArrayList<>();

        while (queuePack.size() > 0 && i < times)
        {
            double r = queuePack.getFirst();
            queuePack.removeFirst();
            nums.add(queueNum.getFirst());
            queueNum.removeFirst();
            if (t < r)
            {
                t = r;
            }

            i++;
        }

        double valueDrone = t;
        for (int j = 0; j < nums.size(); j++)
        {
            valueDrone += updateTimeFinish(index, nums.get(j), j + 1, t);
        }
        queueDrone.set(1, queueDrone.get(1) + valueDrone);

        if (queuePack.size() > 0)
        {
            i = 0;
            times = Configs.randInt(1, Configs.droneCapacity + 1);
            if (queueDrone.get(0) <= queueDrone.get(1) && queueDrone.get(0) <= queueDrone.get(2))
            {
                t = queueDrone.get(0);
                cycle1(index, i, times, t);
            }
            else if (queueDrone.get(1) <= queueDrone.get(0) && queueDrone.get(1) <= queueDrone.get(2))
            {
                t = queueDrone.get(1);
                cycle2(index, i, times, t);
            }
            else
            {
                t = queueDrone.get(2);
                cycle3(index, i, times, t);
            }
        }
    }

    private void cycle3(int index, int i, int times, double t)
    {
        ArrayList<Integer> nums = new ArrayList<>();

        while (queuePack.size() > 0 && i < times)
        {
            double r = queuePack.getFirst();
            queuePack.removeFirst();
            nums.add(queueNum.getFirst());
            queueNum.removeFirst();
            if (t < r)
            {
                t = r;
            }

            i++;
        }

        double valueDrone = t;
        for (int j = 0; j < nums.size(); j++)
        {
            valueDrone += updateTimeFinish(index, nums.get(j), j + 1, t);
        }
        queueDrone.set(2, queueDrone.get(2) + valueDrone);

        if (queuePack.size() > 0)
        {
            i = 0;
            times = Configs.randInt(1, Configs.droneCapacity + 1);
            if (queueDrone.get(0) <= queueDrone.get(1) && queueDrone.get(0) <= queueDrone.get(2))
            {
                t = queueDrone.get(0);
                cycle1(index, i, times, t);
            }
            else if (queueDrone.get(1) <= queueDrone.get(0) && queueDrone.get(1) <= queueDrone.get(2))
            {
                t = queueDrone.get(1);
                cycle2(index, i, times, t);
            }
            else
            {
                t = queueDrone.get(2);
                cycle3(index, i, times, t);
            }
        }
    }

    private double updateTimeFinish(int index, int num, int scale, double t)
    {
        double theTime = 0.0;

        if (index < drone11.size())
        {
            for (int i = 0; i < drone11.get(index).size(); i++)
            {
                if (num == drone11.get(index).get(i))
                {
                    double time = 0.0;
                    if (index != 0)
                    {
                        double distance = Configs.matrix[droneNum1.get(index - 1)][droneNum1.get(index)];
                        time = distance / Configs.vDrone;
                    }
                    theTime = scale * time;
                    timeFinish1.get(index).add(t + scale * time);
                }
            }
        }

        if (index < drone22.size())
        {
            for (int i = 0; i < drone22.get(index).size(); i++)
            {
                if (num == drone22.get(index).get(i))
                {
                    double time = 0.0;
                    if (index != 0)
                    {
                        double distance = Configs.matrix[droneNum2.get(index - 1)][droneNum2.get(index)];
                        time = distance / Configs.vDrone;
                    }
                    theTime = scale * time;
                    timeFinish2.get(index).add(t + scale * time);
                }
            }
        }

        if (index < drone33.size())
        {
            for (int i = 0; i < drone33.get(index).size(); i++)
            {
                if (num == drone33.get(index).get(i))
                {
                    double time = 0.0;
                    if (index != 0)
                    {
                        double distance = Configs.matrix[droneNum3.get(index - 1)][droneNum3.get(index)];
                        time = distance / Configs.vDrone;
                    }
                    theTime = scale * time;
                    timeFinish3.get(index).add(t + scale * time);
                }
            }
        }

        return theTime;
    }
    private void processTimeUpdate1(int index)
    {
        double max = 0.0;
        int timeFinishSize = timeFinish1.get(index).size();

        for (int i = 0; i < timeFinishSize; i++)
        {
            double timeFinishI = timeFinish1.get(index).get(i);
            if (max < timeFinishI)
            {
                max = timeFinishI;
            }
        }
        timeUpdate1[index] = max;
    }

    private void processTimeUpdate2(int index)
    {
        double max = 0.0;
        int timeFinishSize = timeFinish2.get(index).size();

        for (int i = 0; i < timeFinishSize; i++)
        {
            double timeFinishI = timeFinish2.get(index).get(i);
            if (max < timeFinishI)
            {
                max = timeFinishI;
            }
        }
        timeUpdate2[index] = max;
    }

    private void processTimeUpdate3(int index)
    {
        double max = 0.0;
        int timeFinishSize = timeFinish3.get(index).size();

        for (int i = 0; i < timeFinishSize; i++)
        {
            double timeFinishI = timeFinish3.get(index).get(i);
            if (max < timeFinishI)
            {
                max = timeFinishI;
            }
        }
        timeUpdate3[index] = max;
    }


}
