// Anmol Saini

// necessary imports
import java.util.Random;
import java.util.ArrayList;

public class Chromosome extends ArrayList<Item> implements Comparable<Chromosome> {
  
  private static Random rng; // field for random number generation

  // empty constructor
  public Chromosome() {

  }

  // constructor
  public Chromosome(ArrayList<Item> items) {

    for (Item i: items) {
      Item copyItem = new Item(i); // creates a copy of each item in the `items` ArrayList
      
      Chromosome.rng = new Random(); // creates the random number generator
      int upperBound = 10; // creates an upper bound of 10 for the random number generator
      int rand = rng.nextInt(upperBound) + 1; // creates a random number between 1 (inclusive) and 11 (exclusive)

      // sets the copy's included field to true or false based on the value of the random number
      if (rand < 6) {
        copyItem.setIncluded(false);
      } else {
        copyItem.setIncluded(true);
      }

      super.add(copyItem); // adds each copy to the super class
    } 
  }

  // crosses over a Chromosome with another one and produces a new child Chromosome that exhibits characterics of either parent randomly
  public Chromosome crossover(Chromosome other) {

    Chromosome child = new Chromosome(); // creates a child Chromosome

    for (int i = 0; i < this.size(); i++) {
      // deals with random number generation (specified in more detial in the constructor)
      Chromosome.rng = new Random();
      int upperBound = 10;
      int rand = rng.nextInt(upperBound) + 1;

      // passes characterics of the parents on to the child depending on the value of the random number
      if (rand < 6) {
        Item itemCopy = new Item(this.get(i));
        child.add(itemCopy);
      } else {
        Item itemCopy = new Item(other.get(i));
        child.add(itemCopy);
      }
    }

    return child; // returns the created child
  }

  // exposes a Chromosome to mutation and mutates randomly
  public void mutate() {
    
    for (int i = 0; i < this.size(); i++) {
      // deals with random number generation (specified in more detial in the constructor)
      Chromosome.rng = new Random();
      int upperBound = 10;
      int rand = rng.nextInt(upperBound) + 1;

      // mutates a gene (the included field) in the Chromosome depending on the value of the random number; occurs once for each gene
      if (rand == 1) {
        this.get(i).setIncluded(!this.get(i).isIncluded());
      }
    }
  }

  // determines the fitness of a Chromosome based on the total weight and total value of the included items
  public int getFitness() {

    double totalWeight = 0.0; // initializes the total weight of the items in the Chromosome to 0.0
    int totalValue = 0; // initializes the total value of the items in the Chromosome to 0

    for (int i = 0; i < this.size(); i++) {
      if (this.get(i).isIncluded()) {
        totalWeight += this.get(i).getWeight(); // adds the weight of each included item to the total weight
        totalValue += this.get(i).getValue(); // adds the value of each included item to the total value
      }
    }
    // returns either 0 or the total value based on the total weight
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

    String info = ""; // initializes an empty String

    for (int i = 0; i < this.size(); i++) {
      if (this.get(i).isIncluded()) {
        info += this.get(i).toString() + " "; // adds the contents of the toString() method in the Item class for each included item in the Chromosome to the empty String (which is no longer empty...)
      }
    }
    
    return info + "-> " + this.getFitness(); // returns the no-longer-empty String followed by the Chromosome's fitness
  }
}