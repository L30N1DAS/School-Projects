// Anmol Saini

public class Customer {
    
    // fields
    private double arrivalTime;
    private int orderSize;
    private double timePerItem;
    private int customerID;
    private double endCheckOutTime;
    private double checkOutTime;

    // constructor
    public Customer(double arrivalTime, int orderSize, double timePerItem, int customerID) {
        this.arrivalTime = arrivalTime;
        this. orderSize = orderSize;
        this.timePerItem = timePerItem;
        this.customerID = customerID;
    }

    // returns the Customer's arrival time
    public double getArrivalTime() {
        return arrivalTime;
    }

    // returns the Customer's order sized
    public int getOrderSize() {
        return orderSize;
    }

    // returns the Customer's shopping time per item
    public double getTimePerItem() {
        return timePerItem;
    }

    // returns the Customers ID
    public int getCustomerID(){
        return customerID;
    }

    // determines the Customer's end shopping time as the sum of the arrival time and product of the order size and shopping time per item
    public double getEndShoppingTime() {
        return arrivalTime + orderSize * timePerItem;
    }

    // sets the Customer's end checkout time
    public void setEndCheckOutTime(double endCheckOutTime) {
        this.endCheckOutTime = endCheckOutTime;
    }

    // sets the Customer's checkout time
    public void setCheckOutTime(double checkOutTime) {
        this.checkOutTime = checkOutTime;
    }

    // determines the Customer's wait time as the difference between [the quantity of difference of the end checkout time and end shopping time] and checkout time
    public double getWaitTime() {
        double timeInLine = endCheckOutTime - this.getEndShoppingTime();
        timeInLine = Math.round(timeInLine * 100) / 100.0;
        checkOutTime = Math.round(checkOutTime * 100) / 100.0;
        double waitTime = timeInLine - checkOutTime;
        return waitTime;
    }

    // determines the Customer's end wait time as the difference between the end checkout time and checkout time
    public double getEndWaitTime() {
        double endWaitTime = endCheckOutTime - checkOutTime;
        return endWaitTime;
    }
}