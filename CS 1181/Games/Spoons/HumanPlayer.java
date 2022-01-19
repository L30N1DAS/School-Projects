// Anmol Saini

// necessary imports
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class HumanPlayer extends Player {

    Scanner in = new Scanner(System.in);

    // constructor
    public HumanPlayer(ArrayList<Card> hand) {
        super(hand);
    }

    // HumanPlayer's modified method for drawing Cards
    @Override
    public void drawCard(ArrayList<Card> deck) {
        System.out.println("You drew the " + deck.get(deck.size() - 1));
        super.drawCard(deck);
    }

    // HumanPlayer's modified method for picking up discarded Cards
    @Override
    public void pickupDiscardedCard(ArrayList<Card> discardPile) {
        System.out.println("You picked up the " + discardPile.get(discardPile.size() - 1));
        super.pickupDiscardedCard(discardPile);
    }

    // HumanPlayer's modifed method for discarding Cards
    @Override
    public void discardCard(Card c, ArrayList<Card> discardPile) {
        System.out.println("You discarded the " + c);
        super.discardCard(c, discardPile);
    }

    // HumanPlayer's method for taking a turn
    @Override
    public void takeTurn(ArrayList<Card> deck, ArrayList<Card> discardPile) {
        // displays Cards
        System.out.println("Your cards are: ");
        for (int i = 0; i < this.getHand().size(); i++) {
            System.out.println("\t" + this.getHand().get(i));
        }

        // ends game if victory conditions are met
        if (this.victory()) {
            System.out.println("You win!");
            System.exit(0);
        }

        // adds Cards back to deck when deck gets empty
        if (deck.isEmpty()) {
            for (int i = 0; i < discardPile.size(); i++) {
                deck.add(discardPile.get(0));
                discardPile.remove(0);
            }
            Collections.shuffle(deck);
            System.out.println("The deck has been replenished.");
        }

        // requires drawing Card from deck if discardPile is empty or gives choice to HumanPlayer if not empty
        if (discardPile.isEmpty()) {
            System.out.println("The discard pile is currently empty -- you must draw a card.");
            this.drawCard(deck);
        } else {
            System.out.print("The top card in the discard pile is the " + discardPile.get(discardPile.size() - 1)
                    + "\nDo you want to pick up the " + discardPile.get(discardPile.size() - 1)
                    + " (1) or draw a card (2)? ");
            int choice = -1;
            while (choice != 1 || choice != 2) {
                try {
                    choice = in.nextInt();
                } catch (Exception e) {
                    System.out.print("Invalid choice! Please try again: ");
                    in.nextLine();
                    continue;
                }
                if (choice < 1 || choice > 2) {
                    System.out.print("Invalid choice! Please try again: ");
                    continue;
                }
                break;
            }
            if (choice == 1) {
                this.pickupDiscardedCard(discardPile);
            } else if (choice == 2) {
                this.drawCard(deck);
            }
        }

        // displays current Cards
        System.out.println("Now your cards are: ");
        for (int i = 0; i < this.getHand().size(); i++) {
            System.out.println("\t" + (i + 1) + ". " + this.getHand().get(i));
        }

        // discards Card selected by HumanPlayer
        System.out.print("Which one do you want to discard? ");
        boolean validChoice = false;
        int choice = -1;
        while (!validChoice || choice < 1 || choice > 5) {
            validChoice = true;
            try {
                choice = in.nextInt();
            } catch (Exception e) {
                validChoice = false;
                System.out.print("Invalid choice! Please try again: ");
                in.nextLine();
            }
            if (validChoice && (choice < 1 || choice > 5)) {
                System.out.print("Invalid choice! Please try again: ");
            }
        }
        this.discardCard(this.getHand().get(choice - 1), discardPile);

        // ends game if victory conditions are met
        if (this.victory()) {
            System.out.println("You win!");
            System.exit(0);
        }
    }
}
