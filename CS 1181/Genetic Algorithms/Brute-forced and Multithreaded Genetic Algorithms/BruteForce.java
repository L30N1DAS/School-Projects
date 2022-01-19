// Anmol Saini

// necessary imports
import java.util.ArrayList;
import java.io.*;

public class BruteForce {

    public static void main(String[] args) throws IOException {

        ArrayList<Item> items = Main.readData("items.txt");
        ArrayList<Item> optimalSet = new ArrayList<>();

        // determines the optimalSet of Items by calling the corresponding method
        try {
            optimalSet = getOptimalSet(items);
        } catch (InvalidArgumentException e) {
            System.out.println(e.getMessage());
        }

        // displays the Items in the optimalSet
        System.out.println("The optimal set:");
        for (int i = 0; i < optimalSet.size(); i++) {
            System.out.println(optimalSet.get(i));
        }
    }

    // recursively calculates the optimal set of Items (the one with the greatest fitness)
    public static ArrayList<Item> getOptimalSet(ArrayList<Item> items) throws InvalidArgumentException {

        // throws a custom exception if there are too many Items
        if (items.size() > 10) {
            throw new InvalidArgumentException();
        }

        // base case
        // returns the `items` ArrayList if empty
        if (items.size() == 0) {
            return items;
        }

        // recursive step

        // determines the fitness of all the Items
        ArrayList<Item> bestSubset = new ArrayList<>();
        for (int i = 0; i < items.size(); i++) {
            bestSubset.add(items.get(i));
        }
        int bestFitness = calculateFitness(bestSubset);

        // determines the fitness of all the Items except with one removed one at a time
        // does this recursively
        // updates the most optimal set and fitness if necessary
        for (int i = 0; i < items.size(); i++) {
            ArrayList<Item> removedItemList = new ArrayList<>();
            for (int j = 0; j < items.size(); j++) {
                if (i != j) {
                    removedItemList.add(items.get(j));
                }
            }
            ArrayList<Item> attemptedBetterSubset = getOptimalSet(removedItemList);
            int attemptedBetterFitness = calculateFitness(attemptedBetterSubset);
            if (attemptedBetterFitness > bestFitness) {
                bestSubset.clear();
                for (int j = 0; j < attemptedBetterSubset.size(); j++) {
                    bestSubset.add(attemptedBetterSubset.get(j));
                }
                bestFitness = attemptedBetterFitness;
            }
        }

        // returns the most optimal set
        return bestSubset;
    }

    // determines the total fitness of the specified Items based on their totalWeight and totalValue
    public static int calculateFitness(ArrayList<Item> items) {

        double totalWeight = 0.0;
        int totalValue = 0;

        for (int i = 0; i < items.size(); i++) {
            totalWeight += items.get(i).getWeight();
            totalValue += items.get(i).getValue();
        }

        if (totalWeight > 10.0) {
            return 0;
        } else {
            return totalValue;
        }
    }
}