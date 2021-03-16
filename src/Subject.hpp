/**
* File:         Subject.hpp
*
* Description:  Subject interface for observer pattern.
*
* Author:       gowth6m
*
* Date:         10/03/2021
*/

#ifndef __SUBJECT_HPP
#define __SUBJECT_HPP

#include "Observer.hpp"

/**
 * The Subject interface  for Observer pattern where Observers
 * watch this and update depending on the states on this.
 *
 * Allows a derived class to accept observers (which implemented
 * Observer interface) to register in order to trigger automatic
 * updates whenever the state of the subject changes.
 */
class Subject {

public:

    /**
     * Registers an Concrete Observer to a Subject.
     *
     * @param observer: observer to register to this Subject
     */
    virtual void registerObserver(Observer *observer) = 0;

    /**
     * To unregister a Concrete Observer from a Subject. This is used in the
     * destructor of the class implementing this interface to free memory.
     *
     * @param observer: observer that is registered to this Subject
     */
    virtual void removeObserver(Observer *observer) = 0;

    /**
     * Notifies all registered Concrete Observers to this Subject, which then
     * runs the Observers' update function.
     */
    virtual void notifyObservers() = 0;

};

#endif
