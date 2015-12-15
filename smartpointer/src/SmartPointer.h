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
    T *operator->() const throw(NullPointerException);
    T &operator*() const throw(NullPointerException);

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
    operator bool() const{
		return pObj != nullptr;
    }

private:
    // Pointer to the current object
    T* pObj;

    // Pointer to the reference counter (used for the current object)
    RefCounter *rc;

    /** Auxiliary function: decrements reference counter and deletes object and
     *reference counter, if necessary
     */
    void deleteObject();
};

/*
 * ===========================================================================
 * Eigentliche Smartpointer-Klasse (Implementierung: Template -> .h)
 * ===========================================================================
 */
template<typename T>
SmartPointer<T>::SmartPointer(T * const p) : pObj(nullptr), rc(nullptr) {
	if(p != nullptr && pObj != p){
		*this = p;
	}

}

template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer& sp): pObj(nullptr), rc(nullptr){
	if(sp && *this != sp){
		*this = sp;
	}
	else {
		pObj = nullptr;
		rc = nullptr;
	}
}

template<typename T>
SmartPointer<T>::~SmartPointer(){
	deleteObject();
}

template<typename T>
T* SmartPointer<T>::operator->() const throw(NullPointerException) {
	if(pObj==nullptr){
		throw NullPointerException();
	}
	return pObj;
}

template<typename T>
T& SmartPointer<T>::operator*() const throw(NullPointerException){
	if(pObj==nullptr){
		throw NullPointerException();
	}
	return *pObj;
}

template<typename T>
const T *SmartPointer<T>::getObject() const{
	return pObj;
}

template<typename T>
const RefCounter *SmartPointer<T>::getRefCounter() const{
	return rc;
}

template<typename T>
const SmartPointer<T>& SmartPointer<T>::operator=(T * const p){
	if(pObj != p){
		if(*this ){
			deleteObject();
		}

		if(p == nullptr || p == 0){
			pObj = nullptr;
			rc = nullptr;
		} else {
			pObj = p;
			rc = new RefCounter;
			rc->inc();
		}

	}

	return *this;
}

template<typename T>
const SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& sp){
	if((*this != sp) || !sp){
		deleteObject();
		pObj = const_cast<T*>(sp.getObject());
		rc =  const_cast<RefCounter*>(sp.getRefCounter());
		if(rc){
			rc->inc();
		}

	}

	return *this;
}

template<typename T>
bool SmartPointer<T>::operator==(const SmartPointer& sp) const{

	return pObj==sp.getObject() && rc == sp.getRefCounter();

	return false;
}

template<typename T>
bool SmartPointer<T>::operator!=(const SmartPointer& sp) const{
	return !(*this == sp);
}

template<typename T>
void SmartPointer<T>::deleteObject(){
	if(rc != nullptr){
		rc->dec();
		if(rc->isZero()){
			delete pObj;
			delete rc;
		}

	}

}
#endif  // SMARTPOINTER_H

