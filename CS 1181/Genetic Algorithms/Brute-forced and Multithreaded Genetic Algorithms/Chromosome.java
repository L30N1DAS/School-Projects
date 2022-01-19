// Anmol Saini

// necessary imports
import java.util.Random;
import java.util.ArrayList;

public class Chromosome extends ArrayList<Item> implements Comparable<Chromosome> {

    // fields
    private static Random rng;
    public static long dummy = 0;

    // empty constructor
    public Chromosome() {

    }

    // constructor
    public Chromosome(ArrayList<Item> items) {

        // creates a Chromosome out of the Items and randomly sets each Item as included or not included
        for (Item i : items) {
            Item copyItem = new Item(i); 

            Chromosome.rng = new Random();
            int upperBound = 10;
            int rand = rng.nextInt(upperBound) + 1;

            if (rand < 6) {
                copyItem.setIncluded(false);
            } else {
                copyItem.setIncluded(true);
            }

            super.add(copyItem);
        }
    }

    // crosses over a Chromosome with another one and produces a new child Chromosome that exhibits characterics of either parent randomly
    public Chromosome crossover(Chromosome other) {

        Chromosome child = new Chromosome();

        for (int i = 0; i < this.size(); i++) {
            Chromosome.rng = new Random();
            int upperBound = 10;
            int rand = rng.nextInt(upperBound) + 1;

            if (rand < 6) {
                Item itemCopy = new Item(this.get(i));
                child.add(itemCopy);
            } else {
                Item itemCopy = new Item(other.get(i));
                child.add(itemCopy);
            }
        }

        return child;
    }

    // exposes a Chromosome to mutation and mutates randomly
    public void mutate() {

        for (int i = 0; i < this.size(); i++) {
            Chromosome.rng = new Random();
            int upperBound = 10;
            int rand = rng.nextInt(upperBound) + 1;

            // mutates a gene (the included field of an Item) in the Chromosome depending on the value of the random number; occurs once for each gene
            if (rand == 1) {
                this.get(i).setIncluded(!this.get(i).isIncluded());
            }
        }
    }

    // determines the fitness of a Chromosome based on the totalWeight and totalValue of the included Items
    public int getFitness() {

        dummy = 0;
        for (int i = 0; i < this.size() * 1000; i++) {
            dummy += i;
        }

        double totalWeight = 0.0;
        int totalValue = 0;

        for (int i = 0; i < this.size(); i++) {
            if (this.get(i).isIncluded()) {
                totalWeight += this.get(i).getWeight();
                totalValue += this.get(i).getValue();
            }
        }

        if (totalWeight > 10.0) {
            return 0;
        } else {
            return totalValue;
        }
    }

    // compares Chromosomes, placing those with higher fitness values before others in a list
    public int compareTo(Chromosome other) {
        if (this.getFitness() > other.getFitness()) {
            return -1;
        } else if (this.getFitness() < other.getFitness()) {
            return 1;
        } else {
            return 0;
        }
    }

    // displays the information related to a Chromosome
    public String toString() {

        String info = "";

        for (int i = 0; i < this.size(); i++) {
            if (this.get(i).isIncluded()) {
                info += this.get(i).toString() + " ";
            }
        }

        return info + "-> " + this.getFitness();
    }
}