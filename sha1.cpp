#include "SHA1.h"

//Default constructor
SHA1::SHA1() {
	data = "";
}

//Constructor with parameter
SHA1::SHA1(string text) {
	data = text;
}

//Change input of a SHA1 variable
void SHA1::set() {
	cout << "(SHA1)Enter a string to hash: ";
	cin >> data;
}

//Circular left shift function
bitset<32> cLShift(bitset<32> X, int n) {
    bitset<32> result = (X << n) | (X >> (32 - n));
    return result;
}

//SHA1 Compression Function for void hash
void compression(bitset<32>* result, bitset<32>* w) {
    bitset<32> a = result[0];
    bitset<32> b = result[1];
    bitset<32> c = result[2];
    bitset<32> d = result[3];
    bitset<32> e = result[4];

    int round = 0;

#define SHA1helper(function,value) \
			{ \
                const bitset<32>t = bitset<32>( cLShift(a, 5).to_ullong() + (function).to_ullong() + e.to_ullong() + value.to_ullong() + w[round].to_ullong() ); \
                e = d; \
                d = c; \
				c = cLShift(b, 30); \
				b = a;  \
                a = t; \
			}

    while (round < 16)
    {
        SHA1helper((b & c) | (~b & d), bitset<32>(0x5a827999))
            ++round;
    }
    while (round < 20)
    {
        w[round] = cLShift((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
        SHA1helper((b & c) | (~b & d), bitset<32>(0x5a827999))
            ++round;
    }
    while (round < 40)
    {
        w[round] = cLShift((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
        SHA1helper(b ^ c ^ d, bitset<32>(0x6ed9eba1))
            ++round;
    }
    while (round < 60)
    {
        w[round] = cLShift((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
        SHA1helper((b & c) | (b & d) | (c & d), bitset<32>(0x8f1bbcdc))
            ++round;
    }
    while (round < 80)
    {
        w[round] = cLShift((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
        SHA1helper(b ^ c ^ d, bitset<32>(0xca62c1d6))
            ++round;
    }

#undef SHA1helper

    result[0] = bitset<32>(result[0].to_ullong() + a.to_ulong());
    result[1] = bitset<32>(result[1].to_ullong() + b.to_ulong());
    result[2] = bitset<32>(result[2].to_ullong() + c.to_ulong());
    result[3] = bitset<32>(result[3].to_ullong() + d.to_ulong());
    result[4] = bitset<32>(result[4].to_ullong() + e.to_ulong());
}

//SHA1 Hashing Algorithm
void SHA1::hash(const SHA1 text) {
    //cout << "Original message: " << text.data<< endl;
    //cout << "Original message to binary: " << endl;
    vector<bitset<8> > binaryStr;
    for (unsigned int i = 0; i < text.data.size(); i++)
    {
        binaryStr.push_back(bitset<8>(text.data[i]));
    }
    //printVec(binaryStr);

    int length = binaryStr.size() * 8; //size = 1 byte or 8 bits
    //cout << "Length = " << length << endl << endl;

    //cout << "Pad the message so its length is equal to 448mod512: " << endl;
    binaryStr.push_back(bitset<8>(128)); //128 = 10000000 in binary. Adds the '1' bit then some of the following zero's to message
    int numPadBits = 448 - (8 + length);
    numPadBits = numPadBits / 8;
    for (int i = 0; i < numPadBits; i++)
    {
        binaryStr.push_back(bitset<8>(0));
    }
    //printVec(binaryStr);

    //cout << "64-bit value is added to the message: " << endl;
    bitset<64> binaryLength = bitset<64>(length);   //a 64 bit value which represents the original length        
    for (int i = 56; i >= 8; i = i - 8)        //break up 64 bit bitset into 8 bits so they can be put in vector
    {
        binaryStr.push_back(bitset<8>((binaryLength >> i).to_ulong()));
    }
    binaryStr.push_back(bitset<8>(binaryLength.to_ulong()));
    //printVec(binaryStr);
    //cout << endl;
    //cout << "Break the 512-bit message into 16 32-bit words" << endl;
    bitset<32> W[80];
    int Wsize = 0;
    for (unsigned i = 0; i < 64; i = i + 4)
    {
        //combine four 8-bit numbers into one 32-bit number
        W[Wsize] = bitset<32>(binaryStr[i].to_ulong() << 24 | binaryStr[i + 1].to_ulong() << 16 | binaryStr[i + 2].to_ulong() << 8 | binaryStr[i + 3].to_ulong());
        Wsize++;
    }
    /*for (unsigned i = 0; i < Wsize; i++)
    {
        cout << "W[" << i << "] = " << W[i] << endl;
    }
    cout << endl << endl;
    */

    //Result array
    bitset<32> result[] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0 };

    compression(result, W);
    cout << "Result = ";
    stringstream backtohex;
    backtohex << hex << uppercase << result[0].to_ulong() << result[1].to_ulong() << result[2].to_ulong() << result[3].to_ulong() << result[4].to_ulong();
    cout << backtohex.str() << endl;
    cout << endl;

    //Buffer
    //If w is necessary, I was unsure of what to declare it as
    //unsigned int w[80];

    //testing out code
    // int hextest = 0xFECDBA98;
    // bitset<32> test = bitset<32>(hextest);
    // cout << "hex to bitset = " << test << endl;
    // cout << "After left shift = " << cLShift(test, 3) << endl;
    // cout << "Back to hex = ";
    // stringstream backtohex;
    // backtohex << hex << uppercase << test.to_ulong();
    // cout << backtohex.str() << endl;

    // length = binaryStr.size() * 8; //size = 1 byte or 8 bits
    // cout << "Length = " << length << endl;

    // string testString = binaryStr[0].to_string();
    // cout << "Test: " << testString << endl;
}
