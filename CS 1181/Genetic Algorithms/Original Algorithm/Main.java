// Anmol Saini

// necessary imports
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;
import java.io.*;

public class Main {

  public static void main(String[] args) throws IOException {

    Random rng = new Random(); // creates random number generator

    ArrayList<Item> items = readData("more_items.txt"); // calls the `readData(String filename)` method, which makes the data in the file accessible to the rest of the program
    
    ArrayList<Chromosome> population = initializePopulation(items, 10); // calls the `initializePopulation(ArrayList<Item> items, int populationSize)` method, which creates the initial population

    ArrayList<Chromosome> nextGen = new ArrayList<>(); // creates an ArrayList for the each successive generation one at a time; interacts with the population

    // cycles through 20 generations
    for (int z = 0; z < 10000; z++) {
      // process for adding the members of the population to the next generation
      for (int i = 0; i < population.size(); i++) {
        Chromosome copy = new Chromosome();
        for (int j = 0; j < population.get(i).size(); j++) {
          Item itemCopy = new Item(population.get(i).get(j));
          copy.add(itemCopy);
        }
        nextGen.add(copy);
      }

      Collections.shuffle(nextGen); // shuffles the individuals within the generation to randomize crossover and the production of offspring

      // performs the crossover by pairing each member of the generation with another and creating one child for each pair and adding that child to the generation
      for (int i = 0; i < population.size(); i += 2) {
        Chromosome child = nextGen.get(i).crossover(nextGen.get(i+1));
        nextGen.add(child);
      }

      int numOfExposures = (int) Math.ceil(nextGen.size() * .1); // determines how many members compose 10% of the generation to be exposed to mutation

      Collections.shuffle(nextGen); // shuffles the individuals within the generation to randomize exposure to mutation and mutation itself

      ArrayList<Chromosome> exposedPreviously = new ArrayList<>(); // creates an ArrayList of individuals who have already been exposed to mutation in this generation so they will not be exposed multiple times
      
      // exposes the correct number of individuals to mutation and marks them as already having been exposed in this generation
      for (int i = 0; i < numOfExposures; i++) {
        int rand = -1;
        // cycles until an individual that has not been exposed yet is chosen
        do {
          rand = rng.nextInt(nextGen.size()); // generates a random number between 0 (inclusive) and the size of the generation (normally 15 (exclusively)) and chooses the individual within the generation that corresponds to the index equal to the random number
          // technically unncecessary since the generation was shuffled but I had it set up already; besides, adds an extra level of randomness to the process of mutation
        } while (exposedPreviously.contains(nextGen.get(rand)));

        nextGen.get(rand).mutate();
        exposedPreviously.add(nextGen.get(rand));
      }

      Collections.sort(nextGen); // sorts the generation in descending order of fitness

      population.clear(); // empties the population

      // adds the the 10 fittest individuals in the generation to the population
      for (int i = 0; i < 10; i++) {
        population.add(nextGen.get(i));
      }

      nextGen.clear(); // empties the generation
    }
    
    Collections.sort(population); // sorts the population in descending order of fitness
    // appears unnecessary since the generation had already been sorted when the 10 fittest individuals were added to the population but was explicitly specified in the directions
    System.out.println("The fittest individual:\n" + population.get(0)); // displays the fittest individual
  }

  // method to read in the data from the file, converting it into an ArrayList of type `Item` and returning it
  public static ArrayList<Item> readData(String filename) throws FileNotFoundException {
    
    Scanner fileIn = new Scanner(new File(filename)); // initializes the scanner connected to the file
    
    ArrayList<Item> items = new ArrayList<>(); // initializes the ArrayList (its purpose is explained at the beginning of the method)

    // this section continues as long as there is content in the file
    while (fileIn.hasNextLine()) {
      String currentLine = fileIn.nextLine(); // takes the next line of the file (starting with the first and ultimately continuing until every line has been taken once)
      Scanner scLine = new Scanner(currentLine); // initializes a scanner connected to that line
      scLine.useDelimiter(", |\n"); // uses a delimiter on the line to make storing the data in it more convenient

      String name = scLine.next(); // stores the first part of the line as a name
      double weight = Double.parseDouble(scLine.next()); // stores the second part of the line as a weight
      int value = Integer.parseInt(scLine.next()); // stores the third part of the line as a value

      scLine.close(); // closes the scanner connected to the line

      Item item = new Item(name, weight, value); // creates an `Item` object using the information gathered from the line
      items.add(item); // adds all of these objects to the ArrayList created above
    }

    fileIn.close(); // closes the scanner connected to the file

    return items; // returns the ArrayList, which should now be full of all the objects it will ever contain
  }

  // method to initialize the population by making an ArrayList out of it and returning it
  public static ArrayList<Chromosome> initializePopulation(ArrayList<Item> items, int populationSize) {
    
    ArrayList<Chromosome> population = new ArrayList<>(); // creates an ArrayList of type `Chromosome` to hold the population

    for (int i = 0; i < populationSize; i++) {
      Chromosome individual = new Chromosome(items); // creates as many Chromosome objects as are needed based on the desired size of the ititial population; much of the information relating to the objects of type `Item` plays a role here
      population.add(individual); // adds all of these objects to the population
    }

    return population; // returns the population, which should be full of the objects it is supposed to contain at base
  }
}