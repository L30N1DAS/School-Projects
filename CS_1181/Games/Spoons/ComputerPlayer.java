// Anmol Saini

// necessary imports
import java.util.ArrayList;
import java.util.Collections;

public class ComputerPlayer extends Player {

    // field
    private int id;

    // constructor
    public ComputerPlayer(ArrayList<Card> hand, int id) {
        super(hand);
        this.id = id;
    }

    // method to determine number of times a Card with a particular label exists in the ComputerPlayer's hand
    public int numOfOccurrences(Card thisCard) {
        int count = 0;
        for (int i = 0; i < this.getHand().size(); i++) {
            if (thisCard.getLabel().equals(this.getHand().get(i).getLabel())) {
                count++;
            }
        }
        return count;
    }

    // gets the ComputerPlayer's id
    public int getId() {
        return id;
    }

    // ComputerPlayer's modified method for drawing Cards
    @Override
    public void drawCard(ArrayList<Card> deck) {
        System.out.println("CPU " + id + " drew a card.");
        super.drawCard(deck);
    }

    // ComputerPlayer's modified method for picking up discarded Cards
    @Override
    public void pickupDiscardedCard(ArrayList<Card> discardPile) {
        System.out.println("CPU " + id + " picked up the " + discardPile.get(discardPile.size() - 1));
        super.pickupDiscardedCard(discardPile);
    }

    // ComputerPlayer's modifed method for discarding Cards
    @Override
    public void discardCard(Card c, ArrayList<Card> discardPile) {
        System.out.println("CPU " + id + " discarded the " + c);
        super.discardCard(c, discardPile);
    }

    // ComputerPlayer's method for taking a turn
    @Override
    public void takeTurn(ArrayList<Card> deck, ArrayList<Card> discardPile) {
        // ends game if victory conditions are met
        if (this.victory()) {
            System.out.println("CPU " + this.getId() + " wins!");
            System.out.println("CPU " + this.getId() + "'s hand:");
            for (int j=0; j<this.getHand().size(); j++) {
                System.out.println("\t" + this.getHand().get(j));
            }
            System.exit(0);
        }

        // adds Cards back to deck when deck gets empty
        if (deck.isEmpty()) {
            for (int j = 0; j < discardPile.size(); j++) {
                deck.add(discardPile.get(0));
                discardPile.remove(0);
            }
            Collections.shuffle(deck);
            System.out.println("The deck has been replenished.");
        }

        // requires drawing Card from deck if discardPile is empty or gives choice to ComputerPlayer if not empty
        if (discardPile.isEmpty()) {
            this.drawCard(deck);
        } else { // ComputerPlayer AI implemented here
            Collections.sort(this.getHand(), new CardComparator(this));
            int occurrencesOfDiscardedCard = this.numOfOccurrences(discardPile.get(discardPile.size() - 1));
            int maxOccurrencesInHand = this.numOfOccurrences(this.getHand().get(0));

            if ((occurrencesOfDiscardedCard == maxOccurrencesInHand) || (occurrencesOfDiscardedCard == 1 && maxOccurrencesInHand != 3)) {
                this.pickupDiscardedCard(discardPile);
            } else {
                this.drawCard(deck);
            }
        }

        Collections.sort(this.getHand(), new CardComparator(this));
        this.discardCard(this.getHand().get(this.getHand().size() - 1), discardPile); // discards Card selected by ComputerPlayer

        // ends game if victory conditions are met
        if (this.victory()) {
            System.out.println("CPU " + this.getId() + " wins!");
            System.out.println("CPU " + this.getId() + "'s hand:");
            for (int j=0; j<this.getHand().size(); j++) {
                System.out.println("\t" + this.getHand().get(j));
            }
            System.exit(0);
        }
    }
}