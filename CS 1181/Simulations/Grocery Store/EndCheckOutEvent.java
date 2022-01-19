// Anmol Saini

// necessary import
import java.io.*;

public class EndCheckOutEvent extends Event {

    // field
    private Lane lane;
    
    // constructor
    public EndCheckOutEvent(Customer customer, double eventTime, Lane lane) {
        super(customer, eventTime);
        this.lane = lane;
    }

    // returns the Lane corresponding to this Event
    public Lane getLane() {
        return lane;
    }

    // prints out the Customer's end checkout time and starting checkout time in the Log File
    public void print(PrintWriter pw) {
        pw.printf("Customer #%d finished checking out at %.2f (began checking out at %.2f).\n", this.getCustomer().getCustomerID(), this.getEventTime(), this.getCustomer().getEndWaitTime());
    }
}
