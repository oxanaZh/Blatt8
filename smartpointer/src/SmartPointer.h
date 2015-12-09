/*
 * SmartPointer.h
 *
 */

#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <cstddef>
#include <cassert>

#include "RefCounter.h"
#include "NullPointerException.h"

/*
 * ===========================================================================
 * Eigentliche Smartpointer-Klasse (Schnittstelle)
 * ===========================================================================
 */
template<class T>
class SmartPointer {
public:
    // Constructs new SmartPointer
    SmartPointer(T * const p = nullptr);
    SmartPointer(const SmartPointer&);

    // Destructs the owned object if no more SmartPointer links to it
    virtual ~SmartPointer();

    // Dereferences pointer to the managed object
    T *operator->() const;
    T &operator*() const;

    // Returns a pointer to the managed object
    const T *getObject() const;

    // Returns the number of SmartPointer objects referring to the same managed object
    const RefCounter *getRefCounter() const;

    // Assigns the SmartPointer
    const SmartPointer &operator=(T * const p);
    const SmartPointer &operator=(const SmartPointer&);

    // Compares with another SmartPointer or with nullptr
    bool operator==(const SmartPointer&) const;
    bool operator!=(const SmartPointer&) const;

    // Checks if there is associated managed object
    operator bool() const;

private:
    // Pointer to the current object
    T* pObj;

    // Pointer to the reference counter (used for the current object)
    RefCounter *rc;

    // Auxiliary function: decrements reference counter and deletes object and
    // reference counter, if necessary
    void deleteObject();
};

/*
 * ===========================================================================
 * Eigentliche Smartpointer-Klasse (Implementierung: Template -> .h)
 * ===========================================================================
 */

SmartPointer::SmartPointer(T * const p = nullptr){
	pObj = p;
	rc = new RefCounter;
	if(p != nullptr){
		rc.inc();
	}

}
SmartPointer::SmartPointer(const SmartPointer::SmartPointer& sp){
	SmartPointer::pObj = sp.getObject();
	SmartPointer::rc = sp.getRefCounter();
   SmartPointer::rc.inc();
}
virtual SmartPointer::~SmartPointer(){
	if(SmartPointer::rc.isZero()){
		//löschen inhalt und pointer selbst
		SmartPointer::deleteObject();
	} else {
		//löschen nur pointer und rc.dec()

	}
}
T SmartPointer::*operator->() const{

}
T SmartPointer::&operator*() const{

}
const T SmartPointer::*getObject() const{

}
const RefCounter SmartPointer::*getRefCounter() const{

}
const SmartPointer SmartPointer::&operator=(T * const p){

}
const SmartPointer SmartPointer::&operator=(const SmartPointer&){

}
bool SmartPointer::operator==(const SmartPointer& sp) const{
	return (SmartPointer::*pObj==sp.getObject()) && (SmartPointer::rc == sp.getRefCounter());
}
bool SmartPointer::operator!=(const SmartPointer&) const{
	return !((SmartPointer::*pObj==sp.getObject()) && (SmartPointer::rc == sp.getRefCounter())) ;
}
operator bool() const{

}
void SmartPointer::deleteObject(){

}
#endif  // SMARTPOINTER_H

