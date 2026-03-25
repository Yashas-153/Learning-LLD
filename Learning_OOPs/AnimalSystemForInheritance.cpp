#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <set>
#include <string> 
using namespace std;

class Animal{
public:
    virtual void sound(){
        cout<<"Animal Make sound"<<endl;
    }
    void fly(){
        cout<<"Some animals can fly"<<endl;
    }

    void bark(){
        cout<<"Animals cant bark"<<endl;
    }
};
class Dog : public Animal{
public:
    void sound(){
        cout<<"Dog can bark"<<endl;
    }
    void bark(){
        cout<<"Dog is barking"<<endl;
    }
};
int main(){
    Dog *d = new Dog(); // Create dog object in heap memory
    Animal *ad = new Dog();  // Creates a dog object of Animal pointer type, helps in polymorphism
    Dog dog; // Creates dog object in stack memory (Scope Sensitive), Polymorphism happens when accessed via base pointer/reference.”
    Animal a = Dog(); // THis will create a new dog object of type animal in stack memory which will 
                    // not be able access functions of dog class as this slices the object only to Animals
    // Dog *ad = new Animal() // This cannot be done as we are trying to do Base → Derived which is not allowed
    d->sound();
    ad->sound(); // An animal type pointer and compiler allows to call only animal member function, since sound is virtual
                // at runtime it calls dog class soung
    // Animal a;
    ad->bark(); // As Animal Bark function is not virtual, no compile time binding happens so will call animals bark function
    ad->fly(); // Dog can fly as animal can fly,
    d->fly();
    dog.sound();
    return 0;
}


/*
---------- Output -------------
Dog can bark
Dog can bark
Animals cant bark
Some animals can fly
Some animals can fly
Dog can bark
*/