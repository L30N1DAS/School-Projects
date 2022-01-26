// Anmol Saini

// necessary import
import java.util.ArrayList;

public abstract class Player {

    // field
    private ArrayList<Card> hand;

    // constructor
    public Player(ArrayList<Card> hand) {
        this.hand = hand;
    }

    // method to have Players draw Cards
    public void drawCard(ArrayList<Card> deck) {
        Card drawnCard = deck.get(deck.size() - 1);
        hand.add(drawnCard);
        deck.remove(drawnCard);
    }

    // method to have Players pickup discarded Cards
    public void pickupDiscardedCard(ArrayList<Card> discardPile) {
        Card pickedupCard = discardPile.get(discardPile.size() - 1);
        hand.add(pickedupCard);
        discardPile.remove(pickedupCard);
    }

    // method to have Players discard Cards
    public void discardCard(Card c, ArrayList<Card> discardPile) {
        hand.remove(c);
        discardPile.add(c);
    }

    // gets the Player's hand
    public ArrayList<Card> getHand() {
        return this.hand;
    }

    // determines victory conditions; ends the program
    public boolean victory() {
        Card firstCard = hand.get(0);
        for (int i = 1; i < hand.size(); i++) {
            if (!(firstCard.getLabel().equals(hand.get(i).getLabel()))) {
                return false;
            }
        }
        return true;
    }

    // abstract method to have Players take their turns
    public abstract void takeTurn(ArrayList<Card> deck, ArrayList<Card> discardPile);
}
