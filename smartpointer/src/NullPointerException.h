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
	NullPointerException(){message = "nullpointer exception";}
	const char* what() const noexcept(true)
	{
		return message.c_str();
	};
	private:
		std::string message;
};


#endif /* NULLPOINTEREXCEPTION_H_ */
