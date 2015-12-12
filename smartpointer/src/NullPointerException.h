/*
 * NullPointerException.h
 *
 */

#ifndef NULLPOINTEREXCEPTION_H_
#define NULLPOINTEREXCEPTION_H_

#include <stdexcept>
#include <string>
using namespace std;
class NullPointerException : public std::exception {
	public:
	const char* what(){return message.c_str();};
	private:
	std::string message = "nullpointer exception";
};


#endif /* NULLPOINTEREXCEPTION_H_ */

