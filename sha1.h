#ifndef SHA1_H
#define SHA1_H

#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <sstream>

using namespace std;

class sha1{
public:
	//Default constructor
	sha1();
	//Constructor with parameter
	sha1(string text);
	//Change input of a sha1 variable
	void set();
	//Circular left shift function
	friend bitset<32> cLShift(bitset<32> X, int n);
	//SHA1 Compression Function for void hash
	friend void compression(bitset<32>* result, bitset<32>* w);
	//SHA1 Hashing Algorithm
	void hash(const sha1 text);
private:
	string data;
};

#endif SHA1_H
