#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
using namespace std;

template <class t1, class t2>
class priorityQ
{
public:
    priorityQ();
    void push_back(const t1&, const t2&);
    void pop_front();
    void increaseKey(const t1&, const t2&);
    t2 get_front_priority() const;
    t1 get_front_key() const;
    bool isEmpty() const;
private:
	struct priorityType
    {
        t1 key;         // string
        t2 priority;    // mercType
    };

    // max heap
    void bubbleUp(std::size_t);
    void bubbleDown(std::size_t);

    std::vector<priorityType> heapArray; // the list of elements that maintains the priority queue
    std::unordered_map<t1, std::size_t> itemToPQ; // maps a key to the index in the heapArray
};

// constructor; intializes empty priority queue
template <class t1, class t2>
priorityQ<t1, t2>::priorityQ()
{
    heapArray = std::vector<priorityType>(); // empty vector
}

// inserts a new priotyType object to end of queue
template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1& key, const t2& priority)
{
    // insert obj at end of heapAppray
    priorityType newObj = {key, priority};
    heapArray.push_back(newObj);

    // map the key to last index of heapArray 
    itemToPQ[key] = heapArray.size()-1;
    bubbleUp(heapArray.size()-1);
}

// assigns last element to root node
template <class t1, class t2>
void priorityQ<t1, t2>::pop_front()
{
    if(heapArray.empty()){
        return;
    }

    // get last element
    priorityType temp = heapArray.back(); 
    
    // insert at root
    heapArray[0] = temp;
    heapArray[0].priority = temp.priority;
    itemToPQ[temp.key] = 0;

    // remove from end of heapArray and bubble down
    heapArray.pop_back();
    bubbleDown(0);
}

// update itemToPQ map with higher priority item
template <class t1, class t2>
void priorityQ<t1, t2>::increaseKey(const t1& key, const t2& priority)
{
    // get index of key
    size_t index = itemToPQ[key];

    // update value field of element in heapArray
    heapArray[index].priority += priority;

    // call bubbleUp using index of key
    bubbleUp(index);
}

// returns priority of root element
template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const
{
    return heapArray[0].priority;
}

// returns key of root element
template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const
{
    return heapArray[0].key;
}

// returns true if priority queue is empty
template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const
{
    if(heapArray.empty()){
        return true;
    }
    return false;
}

// performs standard bubble up procedure - moves up from an index
template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index)
{
    // compute parent index
    size_t parent = index / 2;

    if(index == 0){ // if item is at root
        return;
    }

    // compare parent and child's value
    if(heapArray[index].priority > heapArray[parent].priority){
        // swap if needed
        std::swap(heapArray[index], heapArray[parent]);
        std::swap(itemToPQ[heapArray[index].key], itemToPQ[heapArray[parent].key]);
        bubbleUp(parent);
    }
}

// performs standard bubble down procedure - moves down from an index
template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index)
{
    // compute children indices
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if(left >= heapArray.size()){ // leaf node
        return;
    }

    // compare children and parent's value
    // find bigger child
    if(heapArray[left].priority > heapArray[right].priority){
        // left child is larger -> swap left child
        if(heapArray[left].priority > heapArray[index].priority){
            // swap if needed
            std::swap(heapArray[index], heapArray[left]);
            std::swap(itemToPQ[heapArray[index].key], itemToPQ[heapArray[left].key]);
            bubbleDown(left);
        }
    } else {
        // right child is larger -> swap right child
        if(heapArray[right].priority > heapArray[index].priority){
            // swap if needed
            std::swap(heapArray[index], heapArray[right]);
            std::swap(itemToPQ[heapArray[index].key], itemToPQ[heapArray[right].key]);
            bubbleDown(right);
        }
    }
}