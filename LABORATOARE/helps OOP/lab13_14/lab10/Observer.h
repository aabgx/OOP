//
// Created by Laura on 5/25/2022.
//

#ifndef UNTITLED_OBSERVER_H
#define UNTITLED_OBSERVER_H
#include <algorithm>
#include <iostream>
/*
  Abstract class
  update method need to be implemented by observers
*/
class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() {};
};
/*
  Observable or Subject - class that notify changes in it's state
  Derive from this class if you want to provide notifications
*/
#include <vector>
#include <algorithm>
class Observable {
private:
    /*Non owning pointers to observer instances*/
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }
    void removeObserver(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }
    void notify() const {
        //for (const auto& obs : observers) {
        //	obs->update();
        //}
        std::for_each(observers.begin(), observers.end(), [](Observer* obs) {
            obs->update();
        });
    }
};
#endif //UNTITLED_OBSERVER_H
