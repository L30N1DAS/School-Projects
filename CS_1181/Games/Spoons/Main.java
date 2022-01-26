// Anmol Saini

// necessary imports
import java.util.ArrayList;
import java.util.Collections;

class Main {

    public static void main(String[] args) {

        int numberOfComputerPlayers = 3; // determines number of ComputerPlayers; changes here effective throughout entire program

        // creates ArrayLists for deck, discardPile, players, and player hands; creates players themselves as well
        ArrayList<Card> deck = createDeck();
        ArrayList<Card> discardPile = new ArrayList<>();
        ArrayList<Player> players = new ArrayList<>();
        ArrayList<Card> playerHand = new ArrayList<>();
        Player humanPlayer = new HumanPlayer(playerHand);
        players.add(humanPlayer);
        for (int i = 0; i < numberOfComputerPlayers; i++) {
            ArrayList<Card> computerHand = new ArrayList<>();
            Player computerPlayer = new ComputerPlayer(computerHand, i + 1);
            players.add(computerPlayer);
        }

        // fill each Player's hand with four Cards
        System.out.println("Players are being dealt cards.");
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < players.size(); j++) {
                players.get(j).drawCard(deck);
            }
            System.out.println();
        }

        Collections.shuffle(players);
        // main game loop
        System.out.println("The game has begun.");
        while (true) {
            for (int i = 0; i < players.size(); i++) {
                players.get(i).takeTurn(deck, discardPile);
                System.out.println();
            }
        }
    }

    // method to create Cards and add them to deck
    public static ArrayList<Card> createDeck() {
        ArrayList<Card> deck = new ArrayList<>();
        String label = "";

        for (int i = 2; i <= 10; i++) {
            deck.add(new Card(label + i, "Hearts"));
            deck.add(new Card(label + i, "Diamonds"));
            deck.add(new Card(label + i, "Clubs"));
            deck.add(new Card(label + i, "Spades"));
        }

        for (int i = 0; i < 4; i++) {
            if (i == 0) {
                label = "Ace";
            } else if (i == 1) {
                label = "Jack";
            } else if (i == 2) {
                label = "Queen";
            } else if (i == 3) {
                label = "King";
            }

            deck.add(new Card(label, "Hearts"));
            deck.add(new Card(label, "Diamonds"));
            deck.add(new Card(label, "Clubs"));
            deck.add(new Card(label, "Spades"));
        }

        Collections.shuffle(deck);
        return deck;
    }
}