/*
 * main.cpp
 *
 */

#include <cstdlib>
#include <iostream>

#include "SmartPointer.h"

class A {
	public:
		A() {
			i= 10;
		}
		int getI(){return i;}
		void setI(int x){i = x;}
	private:
	int i;
};

int main(){
	SmartPointer<A> sp1 { new A };
	cout <<"sp1->getI(): "<<sp1->getI() << endl;
	sp1->setI(20);
	cout <<"sp1->getI(): "<< sp1->getI() << endl;
	SmartPointer<A> sp2 = sp1;
	cout <<"sp2->getI(): "<< sp2->getI() << endl;
	cout<<"sp1 ref couter: " << sp1.getRefCounter()->getRefCount() << endl;
	SmartPointer<A> sp3 = sp2;
	cout <<"sp3->getI(): "<< sp3->getI() << endl;
	cout<<"sp1 ref couter: " << sp1.getRefCounter()->getRefCount()  << endl;
	sp1 = new A;
	cout <<"sp1 = new A; sp1->getI(): "<<sp1->getI()<<endl;
	cout <<"  sp2 ref couter: " << sp2.getRefCounter()->getRefCount() << endl;
	{
		SmartPointer<A> temp = sp1;
		cout<<"with temp: sp1 ref couter: " << sp1.getRefCounter()->getRefCount() << endl;
	}
	cout <<"after delete temp: sp1 ref couter: " << sp1.getRefCounter()->getRefCount() << endl;

	sp1 = nullptr;
	try{
		cout << "sp1->getI()" << sp1->getI() << endl;
	} catch(NullPointerException npe){
		cout << npe.what() << endl;
	}
	return 0;
}
