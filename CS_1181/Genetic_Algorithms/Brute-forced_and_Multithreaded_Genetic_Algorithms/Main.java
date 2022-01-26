// Anmol Saini

/*
Analysis:
Note that my program yields a fitness close to 7600 more regularly when NUM_EPOCHS is set to 10000.
I have left it at 1000 for this submission, however, as that was the value specified in the directions.
As such, my fitness values will be 0 somewhat often.
If the grader chooses to check my results having set NUM_EPOCHS to 10000, I would recommend first removing the `dummy` code from the getFitness() method in the Chromosome class.
I tried running my program with 10000 epochs and 1 Thread along with that code and got a fitness of 7500 but an absurd total run time of 168044 ms.

For this analysis, I intend to run my program 10 times for 1, 2, 3, and 4 Threads each.
To avoid bias, I will not discriminate against runs that yield a fitness of 0.

1 Thread        Fitness        Total Time (ms)

1st run:        0              7469
2nd run:        0              6589
3rd run:        0              6591
4th run:        7600           17085
5th run:        7600           14684
6th run:        7500           13716
7th run:        4100           7483
8th run:        7500           13103
9th run:        7500           17074
10th run:       7500           13769
Average:        4930           11756.3

2 Threads       Fitness        Total Time (ms)

1st run:        7500           8164
2nd run:        7500           7532
3rd run:        7500           8485
4th run:        0              3361
5th run:        0              3363
6th run:        0              3390
7th run:        7500           9143
8th run:        0              3366
9th run:        7600           6179
10th run:       0              3358
Average:        3760           5634.1

3 Threads       Fitness        Total Time (ms)

1st run:        0              2311
2nd run:        7500           5429
3rd run:        7500           3558
4th run:        0              2276
5th run:        0              2445
6th run:        0              2290
7th run:        0              2254
8th run:        6000           2611
9th run:        7500           3242
10th run:       7500           5178
Average:        3600           3159.4

4 Threads       Fitness        Total Time (ms)

1st run:        7500           3215
2nd run:        6000           2031
3rd run:        4700           1937
4th run:        0              1803
5th run:        0              1901
6th run:        7500           4334
7th run:        4500           1955
8th run:        7500           3330
9th run:        7500           2735
10th run:       0              2428
Average:        4520           2566.9
*/

// necessary imports
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.io.*;

public class Main {

    // constants
    public static final int POP_SIZE = 100;
    public static final int NUM_EPOCHS = 1000;
    public static final int NUM_THREADS = 4;

    public static void main(String[] args) throws IOException, InterruptedException {

        long startTime = System.currentTimeMillis();

        ArrayList<Item> items = readData("more_items.txt");
        ArrayList<Chromosome> population = initializePopulation(items, POP_SIZE);
        ArrayList<Thread> threads = new ArrayList<>();
        ArrayList<Chromosome> eliteChromosomes = new ArrayList<>();

        int distributedEpochs = NUM_EPOCHS / NUM_THREADS;
        int distributedPopulationSize = POP_SIZE / NUM_THREADS;

        // creates the Threads and sets them to run for the appropriate number of epochs
        for (int i = 0; i < NUM_THREADS - 1; i++) {
            ArrayList<Chromosome> copyPopulation = copyPopulation(population);
            Thread thisThread = new GeneticAlgorithmThread(copyPopulation, i * distributedEpochs,
                    (i + 1) * distributedEpochs);
            threads.add(thisThread);
        }
        ArrayList<Chromosome> copyPopulation = copyPopulation(population);
        Thread thisThread = new GeneticAlgorithmThread(copyPopulation, (NUM_THREADS - 1) * distributedEpochs,
                NUM_EPOCHS);
        threads.add(thisThread);

        // start all of the Threads
        for (Thread t : threads) {
            t.start();
        }

        // waits until all of the Threads have finished
        for (Thread t : threads) {
            t.join();
        }

        // determines the Chromosomes with the most optimal fitness values
        for (int i = 0; i < NUM_THREADS; i++) {
            ((GeneticAlgorithmThread) threads.get(i)).determineEliteChromosomes(distributedPopulationSize, eliteChromosomes);
        }

        Collections.sort(eliteChromosomes);
        System.out.println("The fittest individual:\n" + eliteChromosomes.get(0));

        long endTime = System.currentTimeMillis();
        System.out.println("Total Time: " + (endTime - startTime) + " ms");
    }

    // reads in the specified data file in main and creates Item objects out of the data
    public static ArrayList<Item> readData(String filename) throws FileNotFoundException {

        Scanner fileIn = new Scanner(new File(filename));
        ArrayList<Item> items = new ArrayList<>();

        while (fileIn.hasNextLine()) {
            String currentLine = fileIn.nextLine();
            Scanner scLine = new Scanner(currentLine);
            scLine.useDelimiter(", |\n");

            String name = scLine.next();
            double weight = Double.parseDouble(scLine.next());
            int value = Integer.parseInt(scLine.next());

            scLine.close();

            Item item = new Item(name, weight, value);
            items.add(item);
        }

        fileIn.close();

        return items;
    }

    // initializes the population
    public static ArrayList<Chromosome> initializePopulation(ArrayList<Item> items, int populationSize) {

        ArrayList<Chromosome> population = new ArrayList<>();

        // makes the population out of Chromosomes which are made out of the Items
        for (int i = 0; i < populationSize; i++) {
            Chromosome individual = new Chromosome(items); 
            population.add(individual);
        }

        return population;
    }

    // makes copies of the population to pass into the Threads
    public static ArrayList<Chromosome> copyPopulation(ArrayList<Chromosome> population) {

        ArrayList<Chromosome> populationCopy = new ArrayList<>();

        // makes copies of the Chromosomes to add to the copy of the population
        for (int i = 0; i < population.size(); i++) {
            Chromosome chromosomeCopy = new Chromosome();
            // makes copies of the Items in the Chromosomes to add to the copies of the Chromosomes
            for (int j = 0; j < population.get(i).size(); j++) {
                Item itemCopy = new Item(population.get(i).get(j));
                chromosomeCopy.add(itemCopy);
            }
            populationCopy.add(chromosomeCopy);
        }

        return populationCopy;
    }
}