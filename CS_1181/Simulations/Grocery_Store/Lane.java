// Anmol Saini

// necessary import
import java.util.ArrayList;

public abstract class Lane extends ArrayList<Customer> implements Comparable<Lane> {

    // fields
    private double checkOutTimePerItem;
    private double paymentProcessingTime;
    private boolean expressType;
    private int totalLaneCount = 0;
    private int currentLaneCount = 0;
    private int maxLaneCount = currentLaneCount;
    private double totalWaitTime = 0.0;

    // constructor
    public Lane(double checkOutTimePerItem, double paymentProcessingTime, boolean expressType) {
        this.checkOutTimePerItem = checkOutTimePerItem;
        this.paymentProcessingTime = paymentProcessingTime;
        this.expressType = expressType;
    }

    // returns whether the Lane is Regular or Express
    public boolean getExpressType() {
        return expressType;
    }

    // determines the Customer's checkout time as the sum between payment processing time and the product of the checkout time per item and order size
    public double getCustomerCheckOutTime(Customer customer) {
        return checkOutTimePerItem * customer.getOrderSize() + paymentProcessingTime;
    }

    // determines the total number of Customers that have entered a Lane
    public void incrementTotalLaneCount() {
        totalLaneCount++;
    }

    // returns the total number of Customers that have entered a Lane
    public int getTotalLaneCount() {
        return totalLaneCount;
    }

    // determines the current number of Customers in a Lane (used when a Customer is added to a Lane)
    public void incrementCurrentLaneCount() {
        currentLaneCount++;
    }
    
    // determines the current number of Customers in a Lane (used when a Customer is removed from a Lane)
    public void decrementCurrentLaneCount() {
        currentLaneCount--;
    }

    // returns the current number of Customers in a Lane
    public int getCurrentLaneCount() {
        return currentLaneCount;
    }

    // determines the maximum number of Customers that have been in a Lane at a single time
    public void setMaxLaneCount() {
        if (currentLaneCount > maxLaneCount) {
            maxLaneCount = currentLaneCount;
        }  
    }

    // returns the maximum number of Customers that have been in a Lane at a single time
    public int getMaxLaneCount() {
        return maxLaneCount;
    }

    // determines the total wait time of all the Customers that have entered a Lane
    public void setTotalWaitTime(double waitTime) {
        totalWaitTime += waitTime;
    }

    // returns the total wait time of all the Customers that have entered a Lane
    public double getTotalWaitTime() {
        return totalWaitTime;
    }

    // sorts Lanes by putting those with fewer Customers first and Express Lanes before Regular Lanes when sizes are the same
    public int compareTo(Lane other) {
        if (this.size() < other.size()) {
            return -1;
        } else if (this.size() > other.size()) {
            return 1;
        } else {
            if (this.size() == other.size() && this.getExpressType()) {
                return -1;
            } else if (this.size() == other.size() && other.getExpressType()) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}