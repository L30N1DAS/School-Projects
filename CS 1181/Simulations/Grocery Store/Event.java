// Anmol Saini

public abstract class Event implements Comparable<Event> {

    // fields
    private Customer customer;
    private double eventTime;

    // constructor
    public Event(Customer customer, double eventTime) {
        this.customer = customer;
        this.eventTime = eventTime;
    }

    // returns the Customer corresponding to this Event
    public Customer getCustomer() {
        return this.customer;
    }

    // returns the time corresponding to this Event
    public double getEventTime() {
        return this.eventTime;
    }

    // sorts Events by putting those with earlier times first
    public int compareTo(Event other) {
        if (this.eventTime < other.eventTime) {
            return -1;
        } else if (this.eventTime > other.eventTime) {
            return 1;
        } else {
            return 0;
        }
    }
}