// Anmol Saini

// necessary imports
import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import javax.swing.border.*;

class Main extends JFrame {

    int offer = 0; // creates an `offer` integer to store the offer
    ArrayList<JButton> buttonCases = new ArrayList<>(); // creates a `buttonCases` ArrayList to store the buttons corresponding to the cases

    public Main() {

        // `root` panel to which everything else will be added
        JPanel root = new JPanel();
        root.setLayout(new BoxLayout(root, BoxLayout.Y_AXIS));

        // `header` panel for supplementary information
        JPanel header = new JPanel();
        header.setLayout(new BorderLayout());
        header.setBorder(new EmptyBorder(10, 10, 10, 10));

        // creates a `pastOffers` button to display the previous offers and adds it to the `header` panel
        JButton pastOffers = new JButton("Past Offers");
        header.add(pastOffers,BorderLayout.WEST);

        // creates a `remainList` button to display the cases remaining and adds it to the `header` panel
        JButton remainList = new JButton("Remaining Cases");
        header.add(remainList, BorderLayout.EAST); 

        // sets sizes of `header` panel and its buttons
        header.setMaximumSize(new Dimension(2000, 125));
        header.setPreferredSize(new Dimension(2000, 125));
        pastOffers.setMaximumSize(new Dimension(150, 200));
        pastOffers.setPreferredSize(new Dimension(150, 200));
        remainList.setMaximumSize(new Dimension(150, 200));
        remainList.setPreferredSize(new Dimension(150, 200));

        // `offerPanel` for the `offer`
        JPanel offerPanel = new JPanel();
        offerPanel.setLayout(new BoxLayout(offerPanel, BoxLayout.X_AXIS));

        // `value` label to store the `offer`
        JLabel value = new JLabel("Offer: $" + offer);
        value.setFont(new Font("Calibri", Font.PLAIN, 20));
        value.setForeground(Color.GREEN);
        offerPanel.add(value); // adds the `value` label to the `offerPanel` panel

        // `board` panel for the primary part of the game
        JPanel board = new JPanel();
        board.setLayout(new GridLayout(5, 5));

        // for loop to create 25 `caseButton` buttons to represent the cases; adds them to the `board` panel and `buttonCases` ArrayList
        for (int i = 1; i <= 25; i++) {
            JButton caseButton = new JButton("" + i);
            board.add(caseButton);
            buttonCases.add(caseButton);
        }

        // adds the `header`, `offerPanel`, and `board` panels to the `root` panel; adds the `root` panel to the `ContentPane`
        root.add(header);
        root.add(offerPanel);
        root.add(board);
        this.getContentPane().add(root);

        // https://docs.oracle.com/javase/tutorial/uiswing/components/dialog.html
        JOptionPane.showMessageDialog(this,
                "Click on a case to open it and remove the amount of money inside from play.\nAt intervals throughout the game, the player will be prompted with an offer and the ability to click 'Deal' (to take the offer and end the game) or 'No Deal' (to continue playing for a chance to win more money).\nThe offer is the average of the unopened cases.\nThe 'Remaining Cases' button can be clicked to see what money amounts are still in play.\nThe 'Past Offers' button can be clicked to display offers the player has received previously to gauge current performance.\nOn the last turn, when only two cases are left, the case not chosen will be the only case left in play and therefore the amount of money the player wins.\nThe entire goal of the game is to win as much money as possible by opening cases with low values.",
                "Instructions", JOptionPane.INFORMATION_MESSAGE); // creates a dialog box for the instructions when the program is run
        // end citation

        ArrayList<Integer> pastOffersList = new ArrayList<>(); // creates a `pastOffersList` ArrayList to store the offers the player has received previously
        ArrayList<Integer> cashCases = makeCashCases(); // calls the `makeCashCases` method to create a `cashCases` ArrayList to store the cash values in the cases
        ArrayList<Integer> caseList = makeCashCases(); // calls the `makeCashCases` method to create a `caseList` ArrayList to keep an ordered record of the cash values still in play

        // performed when the `pastOffers` button is clicked
        pastOffers.addActionListener(e -> {
            String pastOffersString = makePastOffersList(pastOffersList); // calls the `makePastOffersList` method
            // https://docs.oracle.com/javase/tutorial/uiswing/components/dialog.html
            JOptionPane.showMessageDialog(this, pastOffersString, "Past Offers", JOptionPane.PLAIN_MESSAGE); // creates a dialog box to display the player's past offers
            // end citation
        });

        // performed when the `remainList` button is clicked
        remainList.addActionListener(e -> {
            String remainListString = makeRemainingCasesList(caseList); // calls the `makeRemainingCasesList` method
            // https://docs.oracle.com/javase/tutorial/uiswing/components/dialog.html
            JOptionPane.showMessageDialog(this, remainListString, "Case Values Remaining", JOptionPane.PLAIN_MESSAGE); // creates a dialog box to display the cash values still in play
            // end citation
        });

        Collections.shuffle(cashCases); // shuffles the `cashCases` ArrayList (to randomly add cash values to the cases)

        for (JButton caseButton: buttonCases) {
            // performed when a `caseButton` is clicked
            caseButton.addActionListener(e -> {
                caseButton.setText("$" + cashCases.get(buttonCases.indexOf(caseButton))); // sets the text of the clicked `caseButton` to the cash value of an index in the shuffled `cashCases` ArrayList corresponding to the index of the clicked button in the `buttonCases` ArrayList
                caseButton.setEnabled(false); // renders the `caseButton` unclickable
                caseList.remove(cashCases.get(buttonCases.indexOf(caseButton))); // removes the cash value from the `caseList` ArrayList (to display only cash values still in play to the player)

                int numberOfCases = 0;
                int total = 0;
                
                // for loop to determine total amount of money and the number of cases still in play
                for (int i = 0; i < caseList.size(); i++) {
                    total = total + caseList.get(i);
                    numberOfCases++;
                }
                offer = total / numberOfCases; // calculates the `offer` as the average of the cash values still in play

                String pastOffersString = makePastOffersList(pastOffersList); // calls the `makePastOffersList` method
                String remainListString = makeRemainingCasesList(caseList); // calls the `makeRemainingCasesList` method
                
                // performed when only one case remains
                if (caseList.size() == 1) {
                    value.setText("Thanks for playing!");
                    // https://docs.oracle.com/javase/tutorial/uiswing/components/dialog.html
                    JOptionPane.showMessageDialog(this, "You won $" + offer + "!", "Congratulations",
                            JOptionPane.PLAIN_MESSAGE); // creates a dialog box to tell the user how much money they won
                    // end citation
                    this.setVisible(false); // ends the game
                }

                // performed when a certain number of cases has been opened
                else if (caseList.size() == 20 || caseList.size() == 15 || caseList.size() == 10 || caseList.size() == 7
                        || caseList.size() <= 5) {
                    // sets the text of the `value` label to the `offer` and adds it to the `pastOffersList` ArrayList
                    value.setText("Offer: $" + offer); 
                    pastOffersList.add(offer);

                    // https://mkyong.com/swing/java-swing-joptionpane-showoptiondialog-example/
                    String[] options = { "Deal", "No Deal" }; // creates an `options` Array with choices to continue or end the game
                    
                    int choice = JOptionPane.showOptionDialog(this, "Offer: $" + offer + "\n\nPast Offers:\n" + pastOffersString + "\nRemaining Cases:\n" + remainListString, "Decision Time",
                            JOptionPane.DEFAULT_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, options[0]); // creates a dialog box to give the user the option to continue or stop playing
                    
                    // performed when the user chooses to end the game
                    if (choice == 0) {
                    // end citation
                        value.setText("Thanks for playing!");
                        // https://docs.oracle.com/javase/tutorial/uiswing/components/dialog.html
                        JOptionPane.showMessageDialog(this, "You won $" + offer + "!", "Congratulations",
                                JOptionPane.PLAIN_MESSAGE); // creates a dialog box to tell the user how much money they won
                        // end citation
                        this.setVisible(false); // ends the game
                    }
                }
            });
        }

        this.setTitle("Deal or No Deal");
        this.setSize(500, 500);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new Main();
            }
        });
    }

    // method to make an ArrayList of cases containing all of the cash values; used to create the `cashCases` and `caseList` ArrayLists
    public ArrayList<Integer> makeCashCases() {
        // https://www.java67.com/2015/10/how-to-declare-arraylist-with-values-in-java.html
        ArrayList<Integer> cashCases = new ArrayList<>(Arrays.asList(1, 5, 10, 25, 50, 75, 100, 200, 300, 400, 500, 750,
                1000, 5000, 10000, 25000, 50000, 75000, 100000, 200000, 300000, 400000, 500000, 750000, 1000000)); // creates an ArrayList containing all the cash values used in the game
        // end citation
        return cashCases;
    }

    // method to make a String containing all of the past offers
    public String makePastOffersList(ArrayList<Integer> pastOffersList) {
        String pastOffersString = "";
        for (int i = 0; i < pastOffersList.size(); i++) {
            pastOffersString = pastOffersString + "$" + pastOffersList.get(i) + "\n"; // adds all of the past offers to the `pastOffersString` in the order received
        }
        return pastOffersString;
    }

    // method to make a String containing all of the cash values of the cases still in play in ascending order
    public String makeRemainingCasesList(ArrayList<Integer> caseList) {
        String remainListString = "";
        for (int i = 0; i < caseList.size(); i++) {
            remainListString = remainListString + "$" + caseList.get(i) + "\n"; // adds the cash values still in play to the `remainListString` in ascending order
        }
        return remainListString;
    }
}