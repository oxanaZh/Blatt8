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
	n =0;
}
void RefCounter::inc(){
	n++;
}
void RefCounter::dec(){
	if(n>0){n--;}
}
bool RefCounter::isZero() const{
	return n< 1;
}
unsigned int RefCounter::getRefCount() const{
	return n;
}




