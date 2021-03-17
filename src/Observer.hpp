/**
* File:         Observer.hpp
*
* Description:  Observer interface for observer pattern.
*
* Author:       074038
*
* Date:         10/03/2021
*/

#ifndef __OBSERVER_HPP
#define __OBSERVER_HPP
/**
 * Observer interface for observer pattern.
 *
 * Interface to create an observer for register to a Subject, which will
 * automatically trigger the observer's update() function when its state changes.
 */
class Observer {

public:
    /**
     * This function runs when the subject being observed runs notifyObserver function
     */
    virtual void update() = 0;

};

#endif
