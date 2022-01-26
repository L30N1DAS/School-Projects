// Anmol Saini

// necessary import
import java.util.Comparator;

public class CardComparator implements Comparator<Card> {

    // field
    private ComputerPlayer player;

    // constructor
    public CardComparator(ComputerPlayer player) {
        this.player = player;
    }

    // method to sort ComputerPlayer's hand by number of occurrences of Cards in hand in descending order; integral to ComputerPlayer AI
    public int compare(Card c1, Card c2) {
        Integer card1 = player.numOfOccurrences(c1);
        Integer card2 = player.numOfOccurrences(c2);
        return (-1 * card1.compareTo(card2));
    }
}