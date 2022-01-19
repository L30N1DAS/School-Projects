// Anmol Saini

public class Card {
    
    // fields
    private String label;
    private String suit;

    // constructor
    public Card(String label, String suit) {
        this.label = label;
        this.suit = suit;
    }

    // gets the Card's label
    public String getLabel() {
        return this.label;
    }

    // determines how the Card will be printed out
    public String toString() {
        return label + " of " + suit;
    }
}
