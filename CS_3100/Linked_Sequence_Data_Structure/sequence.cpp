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
    numElts = sz;
    head = NULL;
    tail = NULL;

    if (sz > 0) {
        head = tail = new SequenceNode();
        for (int i = 0; i < sz - 1; i++) {
            SequenceNode* tmp = new SequenceNode();
            tmp->prev = tail;
            tail->next = tmp;
            tail = tmp;
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
    numElts = s.numElts;
    head = NULL;
    tail = NULL;

    if (s.head != NULL) {
        SequenceNode* sCurrent = s.head;
        head = new SequenceNode(s.head->elt);
        SequenceNode* current = head;
        sCurrent = sCurrent->next;
        while (sCurrent != NULL) {
            SequenceNode* tmp = current;
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
    if (head != NULL) {
        SequenceNode* current = head;
        SequenceNode* nextNode;
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
    clear();
    if (s.head != NULL) {
        SequenceNode* sCurrent = s.head;
        head = new SequenceNode(s.head->elt);
        SequenceNode* current = head;
        sCurrent = sCurrent->next;
        while (sCurrent != NULL) {
            SequenceNode* tmp = current;
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
    SequenceNode* current = head;
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
    if (head == NULL) {
        head = new SequenceNode(value);
        tail = head;
    }

    else {
        SequenceNode* current = tail;
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
    if (size() == 0) {
        throw exception();
    }

    if (size() == 1) {
        delete tail;
        head = NULL;
        tail = NULL;
        numElts--;
    }

    if (size() > 1) {
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
    if (position < 0 || position > size()) {
        throw exception();
    }

    else if (head == NULL && tail == NULL) {
        head = new SequenceNode(value);
        tail = head;
        numElts++;
    }

    else if (position == 0) {
        SequenceNode* newNode = new SequenceNode(value);
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        numElts++;
    }

    else if (position == size()) {
        SequenceNode* newNode = new SequenceNode(value);
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        numElts++;
    } 

    else {
        SequenceNode* current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        SequenceNode* newNode = new SequenceNode(value);
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
    if (head == NULL) {
        throw exception();
    }

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
    if (tail == NULL) {
        throw exception();
    }

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
    if (head == NULL) {
        return true;
    }
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
    SequenceNode* current = head;
    SequenceNode* tmp = current;
    while (current != NULL) {
        current = current->next;
        delete tmp;
        tmp = current;
    }
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
    if (position < 0 || position > size()) {
        throw exception();
    }
    
    else if (count > size() - position) {
        throw exception();
    }

    SequenceNode* killNode = head;
    for (int i = 0; i < position; i++) {
        killNode = killNode->next;
    }

    if (killNode == head && killNode == tail) {
        if (count != 0) {
            delete killNode;
            numElts--;
            head = NULL;
            tail = NULL;
        }
    }

    else if (killNode == head && count == size()) {
        clear();
    }

    else if (killNode == head) {
        SequenceNode* aliveNode;
        for (int i = 0; i < count; i++) {
            aliveNode = killNode->next;
            aliveNode->prev = NULL;
            head = aliveNode;
            delete killNode;
            numElts--;
            killNode = aliveNode;
        }
    }

    else if (killNode == tail) {
        if (count != 0) {
            tail = killNode->prev;
            tail->next = NULL;
            delete killNode;
            numElts--;
        }
    }

    else if (count == size() - position) {
        SequenceNode* tmp = killNode;
        tail = killNode->prev;
        tail->next = NULL;
        while (killNode != NULL) {
            tmp = killNode->next;
            delete killNode;
            numElts--;
            killNode = tmp;
        }
    }

    else {
        SequenceNode* aliveNode = killNode->prev;
        SequenceNode* tmp;
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
    s.print(os);
    return os;
}

//-----------------------------------------------------------------
// print: prints out the sequence (used by the operator<< function)
//      Returns: none
//      Parameters:
//          os (ostream&) - the output stream
//-----------------------------------------------------------------
void Sequence::print(ostream& os) const {
    SequenceNode* current = head;
    while (current != NULL) {
        os << current->elt << " ";
        current = current->next;
    }
}