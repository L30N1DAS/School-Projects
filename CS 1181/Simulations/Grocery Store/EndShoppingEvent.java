// Anmol Saini

// necessary import
import java.io.*;

public class EndShoppingEvent extends Event {
    
    // constructor
    public EndShoppingEvent(Customer customer, double eventTime) {
        super(customer, eventTime);
    }

    // prints out the Customer's end shopping time in the Log File
    public void print(PrintWriter pw) {
        pw.printf("Customer #%d finished shopping at %.2f.\n", this.getCustomer().getCustomerID(), this.getEventTime());
    }
}