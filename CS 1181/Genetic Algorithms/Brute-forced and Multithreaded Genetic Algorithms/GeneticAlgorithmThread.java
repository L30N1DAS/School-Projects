// Anmol Saini

// necessary imports
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class GeneticAlgorithmThread extends Thread {

    // fields
    private static Random rng = new Random();
    private ArrayList<Chromosome> population;
    private ArrayList<Chromosome> nextGen = new ArrayList<>();
    private int start;
    private int end;

    // constructor
    public GeneticAlgorithmThread(ArrayList<Chromosome> population, int start, int end) {
        this.population = population;
        this.start = start;
        this.end = end;
    }

    // Thread's run method
    public void run() {
        // cycles for the appropriate number of epochs
        for (int z = start; z < end; z++) {
            // makes copies of the Chromosomes to add to the next generation
            for (int i = 0; i < population.size(); i++) {
                Chromosome chromosomeCopy = new Chromosome();
                // makes copies of the Items in the Chromosomes to add to to the copies of the Chromosomes
                for (int j = 0; j < population.get(i).size(); j++) {
                    Item itemCopy = new Item(population.get(i).get(j));
                    chromosomeCopy.add(itemCopy);
                }
                nextGen.add(chromosomeCopy);
            }

            Collections.shuffle(nextGen);
            // creates a child Chromosome by randomly pairing members of the generation
            for (int i = 0; i < population.size(); i += 2) {
                Chromosome child = nextGen.get(i).crossover(nextGen.get(i + 1));
                nextGen.add(child);
            }

            // exposes 10% of the generation to mutation
            int numOfExposures = (int) Math.ceil(nextGen.size() * .1);
            Collections.shuffle(nextGen);
            ArrayList<Chromosome> exposedPreviously = new ArrayList<>();
            for (int i = 0; i < numOfExposures; i++) {
                int rand = -1;
                do {
                    rand = rng.nextInt(nextGen.size());
                } while (exposedPreviously.contains(nextGen.get(rand)));
                nextGen.get(rand).mutate();
                exposedPreviously.add(nextGen.get(rand));
            }

            // adds the n fittest individuals in the generation to the population (n is the number of members in the population when it was initialized)
            Collections.sort(nextGen);
            population.clear();
            for (int i = 0; i < Main.POP_SIZE; i++) {
                population.add(nextGen.get(i));
            }
            nextGen.clear();
        }

        Collections.sort(population);
    }

    // combines the fittest individuals determined by each Thread into one ArrayList
    public void determineEliteChromosomes(int distributedPopulationSize, ArrayList<Chromosome> elitePopulation) {
        for (int i = 0; i < distributedPopulationSize; i++) {
            elitePopulation.add(population.get(i));
        }
    }
}