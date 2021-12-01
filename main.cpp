#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>
using namespace std;

void printVec(const vector<bitset<8> > vec)
{
    for (unsigned i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}

//circular left shift functiontion
bitset<32> cLShift(bitset<32> X, int n) {
    bitset<32> result = (X << n) | (X >> (32 - n));
    return result;
}

//compression function
void compression(bitset<32> *result, bitset<32> *w) {
    bitset<32> a = result[0];
    bitset<32> b = result[1];
    bitset<32> c = result[2];
    bitset<32> d = result[3];
    bitset<32> e = result[4];

    int round = 0;

#define sha1helper(function,value) \
			{ \
                a = bitset<32>( cLShift(a, 5).to_ulong() + (function).to_ulong() + e.to_ulong() + value.to_ulong() + w[round].to_ulong() ); \
				b = a; \
				c = cLShift(b, 30); \
				d = c;  \
                e = d;  \
			}

    while (round < 16)
    {
        sha1helper((b & c) | (~b & d), bitset<32> (0x5a827999))
            ++round;
    }
    while (round < 20)
    {
        w[round] = cLShift((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
        sha1helper((b & c) | (~b & d), bitset<32> (0x5a827999))
            ++round;
    }
    while (round < 40)
    {
        w[round] = cLShift((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
        sha1helper(b ^ c ^ d, bitset<32> (0x6ed9eba1))
            ++round;
    }
    while (round < 60)
    {
        w[round] = cLShift((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
        sha1helper((b & c) | (b & d) | (c & d), bitset<32> (0x8f1bbcdc))
            ++round;
    }
    while (round < 80)
    {
        w[round] = cLShift((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
        sha1helper(b ^ c ^ d, bitset<32> (0xca62c1d6))
            ++round;
    }

#undef sha1helper
    result[0] = bitset<32> (result[0].to_ulong() + a.to_ulong());
    result[1] = bitset<32> (result[1].to_ulong() + b.to_ulong());
    result[2] = bitset<32> (result[2].to_ulong() + c.to_ulong());
    result[3] = bitset<32> (result[3].to_ulong() + d.to_ulong());
    result[4] = bitset<32> (result[4].to_ulong() + e.to_ulong());
}



void sha1(const string str) {
    cout << "Original message: " << str << endl;

    cout << "Original message to binary: " << endl;
    vector<bitset<8> > binaryStr;
    for (int i = 0; i < str.size(); i++)
    {
        binaryStr.push_back(bitset<8>(str[i]));
    }
    printVec(binaryStr);

    int length = binaryStr.size() * 8; //size = 1 byte or 8 bits
    cout << "Length = " << length << endl << endl;

    cout << "Pad the message so its length is equal to 448mod512: " << endl;
    binaryStr.push_back(bitset<8>(128)); //128 = 10000000 in binary. Adds the '1' bit then some of the following zero's to message
    int numPadBits = 448 - (8 + length);
    numPadBits = numPadBits / 8;
    for (unsigned i = 0; i < numPadBits; i++)
    {
        binaryStr.push_back(bitset<8>(0));
    }
    printVec(binaryStr);

    cout << "64-bit valueue is added to the message: " << endl;
    bitset<64> binaryLength = bitset<64>(length);   //a 64 bit valueue which represents the original length        
    for (int i = 56; i >= 8; i = i - 8)        //break up 64 bit bitset into 8 bits so they can be put in vector
    {
        binaryStr.push_back(bitset<8>((binaryLength >> i).to_ulong()));
    }
    binaryStr.push_back(bitset<8>(binaryLength.to_ulong()));
    printVec(binaryStr);
    cout << endl;

    cout << "Break the 512-bit message into 16 32-bit words" << endl;
    bitset<32> W[80];
    int Wsize = 0;
    for (unsigned i = 0; i < 64; i = i + 4)
    {
        //combine four 8-bit numbers into one 32-bit number
        W[Wsize] = bitset<32> (binaryStr[i].to_ulong() << 24 | binaryStr[i + 1].to_ulong() << 16 | binaryStr[i + 2].to_ulong() << 8 | binaryStr[i + 3].to_ulong());
        Wsize++;
    }
    for (unsigned i = 0; i < Wsize; i++)
    {
        cout << "W[" << i << "] = " << W[i] << endl;
    }
    cout << endl << endl;

    //Result array
    bitset<32> result[] = { 0x01234567, 0x89ABCDEF, 0xFECDBA98, 0x76543210, 0xC3D2E1F0};

    compression(result, W);
    cout << "Result = ";
    stringstream backtohex;
    backtohex << hex << uppercase << result[0].to_ulong() << result[1].to_ulong() << result[2].to_ulong() << result[3].to_ulong() << result[4].to_ulong();
    cout << backtohex.str() << endl;

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

int main() {
    string str = "This is a string for testing the hash functiontion";
    sha1(str);

    // string input;
    // while(1)
    // {
    //         cout << "Enter a string to hash: ";
    //         cin >> input;
    //         sha1(input);
    // }
    return 0;
}
