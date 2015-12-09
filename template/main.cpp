#include <iostream>
#include <string>

using namespace std;

/**
 * a)Funktion invert(), die zu einem übergebenen numerischen Wert den negativen
 * Wert zurückgibt. Realisieren Sie die Funktion als Template-Funktion.
 */

template<typename T>
T invert(T& input){
	return -(input);
}
/** b) Spezialisieren Sie das eben erstellte Funktionstemplate, so daß invert() auch für string aufgerufen werden
 * kann. In diesem Fall soll der String umgekehrt werden und zurückgeliefert werden, d.h. für die Eingabe
 * von „abcde“ soll „edcba“ zurück geliefert werden.
 */
template<>
string invert(string& input){
	string result = "";
	for(int i = input.length()-1; i >= 0; i--){
		result = result + input[i];
	}
	return result;
}
/**
 * c) Schreiben Sie eine weitere Template-Funktion string getType(T t) mit Template-Spezialisierungen, die
 * den Typ des Parameters t als String zurückgibt. Für nicht bekannte Typen soll der String „unbekannter
 * Typ“ zurückgeliefert werden. Implementieren Sie mind. 3 Spezialisierungen.
 */

template<typename T> //generic
string getType(T t){
	return "unknown";
}
template<>
string getType<int>(int t){ //<int> kann ausgelassen werden
	return "int";
}
template<>
string getType<string>(string t){
	return "string";
}
template<>
string getType<double>(double t){
	return "double";
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
	cout <<"int: " << invert<int>(i) << endl;
	cout <<"negativ int2: " << invert<int>(i2) << endl;
	cout <<"double: " << invert<double>(d) << endl;
	cout <<"short: " << invert<short>(sh) << endl;
	cout <<"long: " << invert(l) << endl;
	cout <<"string: " << st << " -> "<< invert<string>(st) << endl;
	cout <<"string: " << st2 << " -> "<< invert(st2) << endl;
	cout <<"get type(i): " << getType(i) << endl;
	cout <<"get type(st): " << getType(st) << endl;
	cout <<"get type(d): " << getType(d) << endl;
	cout <<"get type(l): " << getType(l) << endl;
	cout <<"get type('a'): " << getType('a') << endl;
	return 0;
}

