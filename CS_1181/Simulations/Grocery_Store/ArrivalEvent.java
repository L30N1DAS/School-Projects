// Anmol Saini

// necessary import
import java.io.*;

public class ArrivalEvent extends Event {
    
    // constructor
    public ArrivalEvent(Customer customer, double eventTime) {
        super(customer, eventTime);
    }

    // prints out the Customer's arrival time in the Log File
    public void print(PrintWriter pw) {
        pw.printf("Customer #%d arrived at %.2f.\n", this.getCustomer().getCustomerID(), this.getEventTime());
    }
}
