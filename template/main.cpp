#include <iostream>
#include <string>

using namespace std;
template<typename T>
T invert(T& input){
	return -(input);
}
template<>
string invert(string& input){
	string result = "";
	for(int i = input.length()-1; i >= 0; i--){
		result = result + input[i];
	}
	return result;
}
template<typename T>
string getType(T t){

}
int main()
{
	int i = 1276666;
	int i2 = -65657;
	double d= 1.2;
	long l= 6756970900;
	short sh = 588;
	string st = "name";
	string st2 = "Oxana Zhurakovskaya";
	cout <<invert<int>(i) << endl;
	cout <<invert<int>(i2) << endl;
	cout <<invert<double>(d) << endl;
	cout <<invert<short>(sh) << endl;
	cout <<invert(l) << endl;
	cout <<invert(st) << endl;
	cout <<invert(st2) << endl;
	return 0;
}

