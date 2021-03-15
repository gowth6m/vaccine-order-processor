//
// Created by Gowtham Ravindrathas on 15/03/2021.
//

#ifndef VACCINEORDERSYSTEM_SUBJECT_HPP
#define VACCINEORDERSYSTEM_SUBJECT_HPP

#include "Observer.hpp"

class Subject {

public:

    virtual void registerObserver(Observer *observer) = 0;

    virtual void removeObserver(Observer *observer) = 0;

    virtual void notifyObservers() = 0;

};

#endif //VACCINEORDERSYSTEM_SUBJECT_HPP
