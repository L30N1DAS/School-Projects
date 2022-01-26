// Anmol Saini

// necessary imports
import java.io.*;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.Collections;

public class Main {
    
    public static void main(String[] args) throws IOException {

        PrintWriter printWriter = new PrintWriter("Project 3 data/Log File.txt");
        ArrayList<Customer> customers = readData("Project 3 data/arrival.txt");

        PriorityQueue<Event> events = new PriorityQueue<>();
        ArrayList<Lane> lanes = new ArrayList<>();

        // creates the RegularLanes
        for (int i=0; i<6; i++) {
            Lane regularLane = new RegularLane();
            lanes.add(regularLane);
        }
        // creates the ExpressLanes
        for (int i=0; i<2; i++) {
            Lane expressLane = new ExpressLane();
            lanes.add(expressLane);
        }

        // creates an ArrivalEvent and EndShoppingEvent for each Customer and adds the Events to the events PriorityQueue
        for (int i=0; i<customers.size(); i++) {
            Event arrivalEvent = new ArrivalEvent(customers.get(i), customers.get(i).getArrivalTime());
            Event endShoppingEvent = new EndShoppingEvent(customers.get(i), customers.get(i).getEndShoppingTime());
            events.offer(arrivalEvent);
            events.offer(endShoppingEvent);
        }

        double totalWaitTime = 0.0;

        // performs the actions of all the events
        while (!events.isEmpty()) {
            Event thisEvent = events.poll();

            // ArrivalEvent information
            if (thisEvent instanceof ArrivalEvent) {
                ((ArrivalEvent) thisEvent).print(printWriter);
            }

            // EndShoppingEvent information
            if (thisEvent instanceof EndShoppingEvent) {
                int laneIndex = 0;
                ((EndShoppingEvent) thisEvent).print(printWriter);
                Collections.sort(lanes);
                // adds the Customer corresponding to this Event to the first Lane in the ArrayList if they have 12 or fewer items
                if (thisEvent.getCustomer().getOrderSize() <= 12) {
                    lanes.get(0).add(thisEvent.getCustomer());
                    lanes.get(0).incrementTotalLaneCount();
                    lanes.get(0).incrementCurrentLaneCount();
                } 
                // adds the Customer corresponding to this Event to the earliest RegularLane in the ArrayList if they have more than 12 items
                else {
                    for (int i=0; i<lanes.size(); i++) {
                        if (thisEvent.getCustomer().getOrderSize() > 12 && (!lanes.get(i).getExpressType())) {
                            lanes.get(i).add(thisEvent.getCustomer());
                            lanes.get(i).incrementTotalLaneCount();
                            lanes.get(i).incrementCurrentLaneCount();
                            laneIndex = i;
                            break;
                        }
                    }
                }
                // creates an EndCheckOutEvent for the Customer corresponding to this Event if they are the only Customer in their Lane; adds it to the events PriorityQueue
                if (lanes.get(laneIndex).size() == 1) {
                    double endCheckOutTime = lanes.get(laneIndex).getCustomerCheckOutTime(thisEvent.getCustomer()) + thisEvent.getCustomer().getEndShoppingTime();
                    thisEvent.getCustomer().setEndCheckOutTime(endCheckOutTime);
                    double checkOutTime = lanes.get(laneIndex).getCustomerCheckOutTime(thisEvent.getCustomer());
                    thisEvent.getCustomer().setCheckOutTime(checkOutTime);
                    Event endCheckOutEvent = new EndCheckOutEvent(thisEvent.getCustomer(), endCheckOutTime, lanes.get(laneIndex));
                    events.offer(endCheckOutEvent);
                    lanes.get(laneIndex).setTotalWaitTime(thisEvent.getCustomer().getWaitTime());
                }
            }

            // EndCheckOutEvent information
            if (thisEvent instanceof EndCheckOutEvent) {
                ((EndCheckOutEvent) thisEvent).print(printWriter);
                int laneIndex = lanes.indexOf(((EndCheckOutEvent) thisEvent).getLane());
                lanes.get(laneIndex).setMaxLaneCount();
                lanes.get(laneIndex).remove(thisEvent.getCustomer());
                lanes.get(laneIndex).decrementCurrentLaneCount();
                // creates an EndCheckOutEvent for the Customer who was formerly behind the Customer corresponding to this Event (if there was one); adds it to the events PriorityQueue
                if (!(lanes.get(laneIndex).isEmpty())) {
                    Customer next = lanes.get(laneIndex).get(0);
                    double endCheckOutTime = lanes.get(laneIndex).getCustomerCheckOutTime(next) + thisEvent.getEventTime();
                    next.setEndCheckOutTime(endCheckOutTime);
                    double checkOutTime = lanes.get(laneIndex).getCustomerCheckOutTime(next);
                    next.setCheckOutTime(checkOutTime);
                    Event endCheckOutEvent = new EndCheckOutEvent(next, endCheckOutTime, lanes.get(laneIndex));
                    events.offer(endCheckOutEvent);
                    lanes.get(laneIndex).setTotalWaitTime(next.getWaitTime());
                }
            }
        }

        // beginning of mathematical analysis / end of events
        printWriter.println("\nSummary:");
        int numberOfCustomers = 0;

        // determines the total number of Customers and the total wait time of all the Customers
        for (Customer c: customers) {
            numberOfCustomers++;
            totalWaitTime += c.getWaitTime();
        }
        printWriter.println("The total number of customers served is " + numberOfCustomers + ".");

        // determines the total number of Customers that passed through a particular Lane
        for (int i=0; i<lanes.size(); i++) {
            int laneNumber = i + 1;
            if (!(lanes.get(i).getExpressType())) {
                printWriter.println("The total number of customers that passed through Regular Lane " + laneNumber + " is " + lanes.get(i).getTotalLaneCount() + ".");
            } else if (lanes.get(i).getExpressType()) {
                printWriter.println("The total number of customers that passed through Express Lane " + laneNumber + " is " + lanes.get(i).getTotalLaneCount() + ".");
            }
        }

        // determines the average wait time of all the Customers that passed through a particular Lane
        for (int i=0; i<lanes.size(); i++) {
            int laneNumber = i + 1;
            if (!(lanes.get(i).getExpressType())) {
                printWriter.printf("The average wait time of the customers that passed through Regular Lane %d is %.2f.\n", laneNumber, lanes.get(i).getTotalWaitTime() / lanes.get(i).getTotalLaneCount());
            } else if (lanes.get(i).getExpressType()) {
                printWriter.printf("The average wait time of the customers that passed through Express Lane %d is %.2f.\n", laneNumber, lanes.get(i).getTotalWaitTime() / lanes.get(i).getTotalLaneCount());
            }
        }

        int maxLengthSum = 0;
        // determines the maximum number of Customers that were in a particular Lane at any point in time
        for (int i=0; i<lanes.size(); i++) {
            int laneNumber = i + 1;
            if (!(lanes.get(i).getExpressType())) {
                printWriter.println("The maximum length of Regular Lane " + laneNumber + " is " + lanes.get(i).getMaxLaneCount() + ".");
                maxLengthSum += lanes.get(i).getMaxLaneCount();
            } else if (lanes.get(i).getExpressType()) {
                printWriter.println("The maximum length of Express Lane " + laneNumber + " is " + lanes.get(i).getMaxLaneCount() + ".");
                maxLengthSum += lanes.get(i).getMaxLaneCount();
            }
        }
        double averageMaxLength = (double) maxLengthSum / lanes.size();
        printWriter.println("The average maximum length of all the Lanes is " + Math.round(averageMaxLength) + ".");

        double averageWaitTime = totalWaitTime / customers.size();
        printWriter.printf("The average wait time of all the customers is %.2f.\n", averageWaitTime);

        printWriter.close();
    }

    // reads in the data file and creates Customer objects out of the data
    public static ArrayList<Customer> readData(String filename) throws FileNotFoundException {

        Scanner fileIn = new Scanner(new File(filename));

        ArrayList<Customer> customers = new ArrayList<>();

        int customerID = 0;
        while(fileIn.hasNextLine()) {
            String currentLine = fileIn.nextLine();
            Scanner scLine = new Scanner(currentLine);
            
            double arrivalTime = Double.parseDouble(scLine.next());
            int orderSize = Integer.parseInt(scLine.next());
            double timePerItem = Double.parseDouble(scLine.next());

            scLine.close();

            customerID++;

            Customer customer = new Customer(arrivalTime, orderSize, timePerItem, customerID);
            customers.add(customer);
        }

        fileIn.close();

        return customers;
    }
}