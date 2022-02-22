#include "Sequence.h"
#include <exception>

Sequence::Sequence( size_type sz )
{
    numElts = sz;
    head = NULL;
    tail = NULL;

    if (sz > 0) {
        head = tail = new SequenceNode(0);
        for (int i = 0; i < sz - 1; i++) {
            SequenceNode* tmp = new SequenceNode(i+1);
            tmp->prev = tail;
            tail->next = tmp;
            tail = tmp;
        }
    }
}

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

Sequence::value_type& Sequence::operator[]( size_type position )
{
    SequenceNode* current = head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    return current->elt;
}

void Sequence::push_back( const value_type& value )
{
    SequenceNode* current = tail;
    tail->next = new SequenceNode(value);
    tail = tail->next;
    tail->prev = current;
    numElts++;
}

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

const Sequence::value_type& Sequence::front() const
{
    return head->elt;
}

const Sequence::value_type& Sequence::back() const
{
    return tail->elt;
}

bool Sequence::empty() const
{
    if (head == NULL) {
        return true;
    }
    else {
        return false;
    }
}

Sequence::size_type Sequence::size() const
{
    return numElts;

    // int count = 0;
    // SequenceNode* current = head;
    // while (current != NULL) {
    //     count++;
    //     current = current->next;
    // }
    // return count;
}

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
            aliveNode->prev = NULL; // this doesn't exist when at last item
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

    else {
        
    }
}

// void Sequence::killNode( SequenceNode& node ) {

// }

ostream& operator<<( ostream& os, Sequence& s )
{
    s.print(os);
    return os;
}

void Sequence::print(ostream& os) const {
    SequenceNode* current = head;
    while (current != NULL) {
        os << current->elt << " ";
        current = current->next;
    }
}