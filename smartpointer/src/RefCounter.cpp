/*
 * RefCounter.cpp
 *
 */

#include "RefCounter.h"

/*
 * ===========================================================================
 * Hilfsklasse zum Zaehlen der Referenzen: Implementierung
 * ===========================================================================
 */

RefCounter::RefCounter(){
	RefCounter::n =0;
}
void RefCounter::inc(){
	RefCounter::n++;
}
void RefCounter::dec(){
	RefCounter::n--;
}
bool RefCounter::isZero() const{
	return n< 1;
}
unsigned int RefCounter::getRefCount() const{
	return RefCounter::n;
}
RefCounter::RefCounter(const RefCounter::RefCounter&) = delete{

}
RefCounter::RefCounter RefCounter::&operator=(const RefCounter::RefCounter& rc) = delete{
	RefCounter::n = rc.getRefCount();
}




