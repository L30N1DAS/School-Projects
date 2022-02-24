//-----------------------------------------------------------------
// Name: Anmol Saini
// Project 3: Linked Sequence Data Structure
//      This file contains the functions implemented for sequences.
//-----------------------------------------------------------------

#include "sequence.h"
#include <exception>

//-------------------------------------------
// Sequence: Constructor for the sequence
//      Returns: none
//      Parameters:
//      sz (size_type) - size of the sequence
//-------------------------------------------
Sequence::Sequence( size_type sz )
{
    // Local variables
    SequenceNode* newNode;      // pointer to the newly created node of the sequence
    
    // initializes the member data
    numElts = sz;
    head = NULL;
    tail = NULL;

    // creates a new node if the sequence has a size greather than zero
    if (sz > 0) {
        head = tail = new SequenceNode();
        // creates new nodes and links them to the previous nodes
        for (int i = 0; i < sz - 1; i++) {
            newNode = new SequenceNode();
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }
}

//-----------------------------------------------------------------------------------
// Sequence: Copy Constructor for the sequence
//      Returns: none
//      Parameters:
//          s (Sequence&) - the sequence off of which the new sequence is being based
//-----------------------------------------------------------------------------------
Sequence::Sequence( const Sequence& s )
{
    // Local variables
    SequenceNode* sCurrent;     // pointer to the nodes of the old sequence
    SequenceNode* current;      // pointer to the nodes of the new sequence
    SequenceNode* tmp;          // pointer to the node before the current node

    // initializes the member data
    numElts = s.numElts;
    head = NULL;
    tail = NULL;

    // creates a node for the new sequence if the old sequence is not empty
    if (s.head != NULL) {
        sCurrent = s.head;
        head = new SequenceNode(s.head->elt);
        current = head;
        sCurrent = sCurrent->next;
        // for each of the nodes in the old sequence creates a node in the new sequence with the same item value
        while (sCurrent != NULL) {
            tmp = current;
            current = current->next;
            current = new SequenceNode(sCurrent->elt);
            tmp->next = current;
            current->prev = tmp;
            sCurrent = sCurrent->next;
        }
        tail = current;
    }  
}

//---------------------------------------
// ~Sequence: Destructor for the sequence
//      Returns: none
//      Parameters: none
//---------------------------------------
Sequence::~Sequence()
{
    // Local variables
    SequenceNode* current;      // pointer to a node of the sequence
    SequenceNode* nextNode;     // pointer to the node after the current node

    // sets current to the first node in the sequence if it is not empty
    if (head != NULL) {
        current = head;
        // deletes every node in the sequence
        while (current != NULL) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
}

//-------------------------------------------------------------------------------------------
// operator=: sets a sequence equal to a provided sequence
//      Returns: a reference to the sequence that is being set equal to the provided sequence
//      Parameters: 
//          s (Sequence&) - the sequence to which another sequence is being set equal
//-------------------------------------------------------------------------------------------
Sequence& Sequence::operator=( const Sequence& s )
{
    // Local variables
    SequenceNode* sCurrent;     // pointer to the nodes of the old sequence
    SequenceNode* current;      // pointer to the nodes of the new sequence
    SequenceNode* tmp;          // pointer to the node before the current node

    clear(); // empties the sequence

    // creates a node for the new sequence if the old sequence is not empty
    if (s.head != NULL) {
        sCurrent = s.head;
        head = new SequenceNode(s.head->elt);
        current = head;
        sCurrent = sCurrent->next;
        // for each of the nodes in the old sequence creates a node in the new sequence with the same item value
        while (sCurrent != NULL) {
            tmp = current;
            current = current->next;
            current = new SequenceNode(sCurrent->elt);
            tmp->next = current;
            current->prev = tmp;
            sCurrent = sCurrent->next;
        }
        tail = current;
    }
    numElts = s.numElts;
    return(*this);
}

//---------------------------------------------------------------
// operator[]: allows access to a particular item in the sequence
//      Returns: the desired item
//      Parameters:
//          position (size_type) - the index of the desired item
//---------------------------------------------------------------
Sequence::value_type& Sequence::operator[]( size_type position )
{
    // Local variables
    SequenceNode* current;      // pointer to the node corresponding to the specified index

    current = head;

    // throws an exception for invalid indexes
    if (position < 0 || position >= size()) {
        throw exception();
    }

    // updates the pointer to the node corresponding to the specified index
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    return current->elt;
}

//-----------------------------------------------------------------
// push_back: adds a new item to the end of the sequence
//      Returns: none
//      Parameters:
//          value (value_type&) - the value of the item to be added
//-----------------------------------------------------------------
void Sequence::push_back( const value_type& value )
{
    // Local variables
    SequenceNode* current;      // pointer to the old tail

    // creates a new node with the specified value if the sequence is empty
    if (head == NULL) {
        head = new SequenceNode(value);
        tail = head;
        numElts++;
    }

    // creates a new node after the tail node if the sequence is not empty
    else {
        current = tail;
        tail->next = new SequenceNode(value);
        tail = tail->next;
        tail->prev = current;
        numElts++;
    }
}

//------------------------------------------------------
// pop_back: removes the item at the end of the sequence
//      Returns: none
//      Parameters: none
//------------------------------------------------------
void Sequence::pop_back()
{
    // throws an exception if the sequence is empty
    if (size() == 0) {
        throw exception();
    }

    // deletes the node if there is only one
    else if (size() == 1) {
        delete tail;
        head = NULL;
        tail = NULL;
        numElts--;
    }

    // deletes the last node in the sequence if there are multiple
    else if (size() > 1) {
        tail = tail->prev;
        delete tail->next;
        tail->next = NULL;
        numElts--;
    }
}

//----------------------------------------------------------------------------------------
// insert: adds a new item at the specified location of the sequence
//      Returns: none
//      Parameters:
//          position (size_type) - the index of the location where the item is to be added
//          value (value_type) - the value of the item to be added
//----------------------------------------------------------------------------------------
void Sequence::insert( size_type position, value_type value )
{
    // Local variables
    SequenceNode* newNode;      // pointer to the node being inserted into the sequence
    SequenceNode* current;      // pointer to the node after the new node

    // throws an exception for invalid indexes
    if (position < 0 || position > size()) {
        throw exception();
    }

    // creates a new node with the specified value if the sequence is empty
    else if (head == NULL && tail == NULL) {
        head = new SequenceNode(value);
        tail = head;
        numElts++;
    }

    // creates a new node at the beginning of the sequence if the index is zero
    else if (position == 0) {
        newNode = new SequenceNode(value);
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        numElts++;
    }

    // creates a new node at the end of the sequence if the index is equal to its size
    else if (position == size()) {
        newNode = new SequenceNode(value);
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        numElts++;
    } 

    // creates a new node at the specifed index if none of the above conditions are met,
    // i.e., it is being inserted somewhere other than the beginning or end of the sequence
    else {
        current = head;
        // updates the current pointer to the node after the insertion location of the new node
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        // creates the new node with the specified value at the specified index
        // and connects it to the rest of the sequence
        newNode = new SequenceNode(value);
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        numElts++;
    }
}

//-----------------------------------------------------
// front: returns the item at the front of the sequence
//      Returns: the item at the front of the sequence
//      Parameters: none
//-----------------------------------------------------
const Sequence::value_type& Sequence::front() const
{
    // throws an exception if the sequence is empty
    if (head == NULL) {
        throw exception();
    }

    // returns the item at the beginning of the sequence if it is not empty
    else {
        return head->elt;
    }
}

//---------------------------------------------------
// back: returns the item at the back of the sequence
//      Returns: the item at the back of the sequence
//      Parameters: none
//---------------------------------------------------
const Sequence::value_type& Sequence::back() const
{
    // throws an exception if the sequence is empty
    if (tail == NULL) {
        throw exception();
    }

    // returns the item at the end of the sequence if it is not empty
    else {
        return tail->elt;
    }
}

//-------------------------------------------
// empty: determines if the sequence is empty
//      Returns: none
//      Parameters: none
//-------------------------------------------
bool Sequence::empty() const
{
    // returns 1 if the sequence is empty
    if (head == NULL) {
        return true;
    }

    // returns 0 if the sequence is not empty
    else {
        return false;
    }
}

//--------------------------------------------------
// size: returns the size of the sequence
//      Returns: the number of items in the sequence
//      Parameters: none
//--------------------------------------------------
Sequence::size_type Sequence::size() const
{
    return numElts;
}

//---------------------------------------------------------
// clear: empties the sequence by removing all of the items
//      Returns: none
//      Parameters: none
//---------------------------------------------------------
void Sequence::clear()
{
    // Local variables
    SequenceNode* current;      // pointer to the nodes of the sequence
    SequenceNode* tmp;          // pointer to the node before the current node

    current = head;

    // deletes every node in the sequence
    while (current != NULL) {
        tmp = current;
        current = current->next;
        delete tmp;
    }

    // sets the sequence's head and tail pointers to NULL
    // and its number of items to zero
    head = NULL;
    tail = NULL;
    numElts = 0;
}

//-------------------------------------------------------------------------------------------
// erase: removes the specified number of sequential items starting at the specified location
//      Returns: none
//      Parameters:
//          position (size_type) - the index of the first item to be removed
//          count (size_type) - the number of items to be removed
//-------------------------------------------------------------------------------------------
void Sequence::erase( size_type position, size_type count )
{
    // Local variables
    SequenceNode* killNode;     // pointer to the nodes to be deleted
    SequenceNode* aliveNode;    // pointer to the nodes not to be deleted
    SequenceNode* tmp;          // pointer to the node after the node being deleted

    // throws an exception for invalid indexes
    // or if an attempt is made to erase items past the end of the sequence
    if (position < 0 || position >= size() || count > size() - position) {
        throw exception();
    }

    killNode = head;

    // updates killNode to the node corresponding to the specified index
    for (int i = 0; i < position; i++) {
        killNode = killNode->next;
    }

    // deletes the node if there is only one node in the sequence
    if (killNode == head && killNode == tail) {
        if (count != 0) {
            delete killNode;
            numElts--;
            head = NULL;
            tail = NULL;
        }
    }

    // deletes every node in the sequence
    // if the first node to be deleted is the first node in the sequence
    // and if the number of nodes to be deleted equals the number of nodes in the sequence
    else if (killNode == head && count == size()) {
        clear();
    }

    // deletes the specified number of nodes
    // if the first node to be deleted is the first node in the sequence
    else if (killNode == head) {
        for (int i = 0; i < count; i++) {
            tmp = killNode->next;
            tmp->prev = NULL;
            head = tmp;
            delete killNode;
            numElts--;
            killNode = tmp;
        }
    }

    // deletes the last node in the sequence
    // if the first (and only) node to be deleted is the last node of the sequence
    else if (killNode == tail) {
        if (count != 0) {
            tail = killNode->prev;
            tail->next = NULL;
            delete killNode;
            numElts--;
        }
    }

    // deletes every successive node in the sequence starting at the specified index
    // if the number of nodes to be deleted
    // equals the total number of nodes minus the starting index
    else if (count == size() - position) {
        tail = killNode->prev;
        tail->next = NULL;
        while (killNode != NULL) {
            tmp = killNode->next;
            delete killNode;
            numElts--;
            killNode = tmp;
        }
    }

    // deletes the specified number of nodes starting at the specified index
    // if none of the above conditions are met,
    // i.e., the first node to be deleted is neither the first nor last node in the sequence
    // and the last node to be deleted is not the last node in the sequence
    else {
        aliveNode = killNode->prev;
        for (int i = 0; i < count; i++) {
            tmp = killNode->next;
            tmp->prev = aliveNode;
            aliveNode->next = tmp;
            delete killNode;
            numElts--;
            killNode = tmp;
        }
    }
}

//-------------------------------------------------------------------
// operator<<: prints out the sequence (uses the print function)
//      Returns: the output stream
//      Parameters:
//          os (ostream&) - the output stream
//          s (Sequence&) - a reference to the sequence being printed
//-------------------------------------------------------------------
ostream& operator<<( ostream& os, Sequence& s )
{
    s.print(os); // calls the print function on the sequence passing it the output stream
    return os;
}

//-----------------------------------------------------------------
// print: prints out the sequence (used by the operator<< function)
//      Returns: none
//      Parameters:
//          os (ostream&) - the output stream
//-----------------------------------------------------------------
void Sequence::print(ostream& os) const
{
    // Local variables
    SequenceNode* current;      // pointer to the nodes of the sequence

    current = head;

    // prints out all of the items in the sequence
    while (current != NULL) {
        os << current->elt << " ";
        current = current->next;
    }
}