#ifndef ITERATOR_H
#define ITERATOR_H
#include "Calendar.h"
#include "Task.h"

/*!
 * \file Iterator.h
 * \brief Header file that describes all the classes needed to implement the Iterator Design Pattern.
 * In order to provide an existing class with Iterator services, simply follow these steps :
        - have your class inheritate with Aggregator<AggregatedItemsType>.
        - Initialize the Aggregator part of your class with the address of your class's item container.

    With that you can :
        - get a simple iterator using the inherited method : getIterator().
        - get a custom iterator iterating only on a specific part of the items aggregated :
            - that belong to a derived type : this->template getIterator<specificType>();
            - that pass a specific test : getIterator(IterationStrategy); IterationStrategy is an object
            of class Iterator<TestedItemType>::IterationStrategy. This object has to define the virtual
            method "test".
            - combine both to iterate on a specific type of items which match a custom condition.
 */

template<class ObjectType>
class Iterator {
protected:
    typedef std::vector<ObjectType*> ItemContainer;
    ItemContainer currentItem;
    Iterator(const ItemContainer& t):currentItem(t){}
    template<class ANY>
    friend class Aggregator;
public:
    Iterator() : currentItem(0){}
    virtual ~Iterator(){}

    bool isDone() const { return currentItem.size()==0;}
    void next(){
        if (isDone()) throw CalendarException("Error : next on a finished iterator");
        currentItem.pop_back();
    }

    ObjectType& current() const {
        if (isDone()) throw CalendarException("Error, indirection on a finished iterator");
        return *currentItem.back();
    }
};

template<class TestedItemType>
class IterationStrategy {
public:
    virtual bool test(TestedItemType* tested) const = 0;
};


template<class ItemType>
class Aggregator {
    Aggregator(const Aggregator& f);
    Aggregator& operator=(const Aggregator& f);
    typedef std::vector<ItemType*> ItemsContainer;
    ItemsContainer* items;
protected:
    Aggregator(ItemsContainer* i): items(i){}
    virtual ~Aggregator(){}

public:
    template<class IteratorItemType = ItemType>
    Iterator<IteratorItemType> getIterator(const IterationStrategy<ItemType>* strategy = 0) { //here take out compositeTask parameter and override this method in taskFactory with a compositeTask parameter/ OR : make composite tasks agregators
        if (items->empty()) throw CalendarException("Error : Trying to get iterator on an empty Aggregator");
        std::vector<IteratorItemType*> toSend;
        IteratorItemType* temp = 0;
        for (typename ItemsContainer::iterator it = items->begin(); it!=items->end(); ++it) {
            temp = dynamic_cast<IteratorItemType*>(*it);
            if (temp) {
                if (!strategy) toSend.push_back(temp); // if there no strategy were given
                else {
                        if (strategy->test(temp)) {toSend.push_back(temp);}
                        else {continue;}
                     }
            }
        }
        return Iterator<IteratorItemType>(toSend);
    }
};


#endif // ITERATOR_H
