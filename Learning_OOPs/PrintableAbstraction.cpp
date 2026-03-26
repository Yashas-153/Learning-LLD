#include<iostream>
using namespace std;

class Printable{
public:
    virtual void print()=0;
    virtual void scan()=0;

    virtual ~Printable() {
        cout<<"called destructor"<<endl;
    } // Good to have destructor for base class

};

class Document : public Printable{
public:
    void print() override {
        cout<<"Document is Printing"<<endl;
    }

    void scan() override{
        cout<<"Document is Scanning"<<endl;
    }
};

class Photo : public Printable{
public:
    void print() override {
        cout<<"Photo is Printing"<<endl;
    }

    void scan() override{
        cout<<"Photo is Scanning"<<endl;
    }
};

int main(){

    Printable *p1 = new Document();
    Printable *p2 = new Photo();

    p1->scan();
    p1->print();

    p2->scan();
    p2->print();

    delete p1;
    delete p2;
    return 0;
}

/*
----------------------Output------------------------

Document is Scanning
Document is Printing
Photo is Scanning
Photo is Printing
called destructor
called destructor
*/