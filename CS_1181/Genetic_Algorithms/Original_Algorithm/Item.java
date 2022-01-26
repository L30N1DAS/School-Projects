// Anmol Saini

public class Item {

  // fields
  private final String name;
  private final double weight;
  private final int value;
  private boolean included;

  // constructor
  public Item(String name, double weight, int value) {
    this.name = name;
    this.weight = weight;
    this.value = value; 
    this.included = false;
  }

  // sets this item's fields to be the same as the other item's
  public Item(Item other) {
    this.name = other.name;
    this.weight = other.weight;
    this.value = other.value;
    this.included = other.included;
  }

  // getter method for weight
  public double getWeight() {
    return this.weight;
  }

  // getter method for value
  public int getValue() {
    return this.value;
  }

  // getter method for included
  public boolean isIncluded() {
    return this.included;
  }

  // setter method for included
  public void setIncluded(boolean included) {
    this.included = included;
  }

  // displays the information related to an item
  public String toString() {
    return name + " (" + weight + " lbs, $" + value + ")";
  }
}