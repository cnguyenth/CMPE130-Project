#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

void printVec(const vector<bitset<8> > vec)
{
        for(unsigned i = 0; i < vec.size(); i++) 
        {
                cout << vec[i] << " ";
        }
        cout << endl;
}

void sha1(const string str){
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
        numPadBits = numPadBits/8; 
        for(unsigned i = 0; i < numPadBits; i++)
        {
                binaryStr.push_back(bitset<8>(0));
        }
        printVec(binaryStr);

        cout << "64-bit value is added to the message: " << endl;
        bitset<64> binaryLength = bitset<64>(length);   //a 64 bit value which represents the original length        
        for(int i = 56; i >= 8; i = i - 8)        //break up 64 bit bitset into 8 bits so they can be put in vector
        {
                binaryStr.push_back(bitset<8>((binaryLength >> i).to_ulong()));
        }
        binaryStr.push_back(bitset<8>(binaryLength.to_ulong()));
        printVec(binaryStr);
        cout << endl;

        cout << "Break the 512-bit message into 16 32-bit words" << endl;
        vector<bitset<32> > W;
        for(unsigned i = 0; i < 64; i = i+4)
        {
                //combine four 8-bit numbers into one 32-bit number
                W.push_back(binaryStr[i].to_ulong() << 24 | binaryStr[i+1].to_ulong() << 16 | binaryStr[i+2].to_ulong() << 8 | binaryStr[i+3].to_ulong() ); 
        }
        for(unsigned i = 0; i < W.size(); i++) 
        {
                cout << "W[" << i << "] = " << W[i] << endl;
        }        
        cout << endl << endl;

        // length = binaryStr.size() * 8; //size = 1 byte or 8 bits
        // cout << "Length = " << length << endl;

        // string testString = binaryStr[0].to_string();
        // cout << "Test: " << testString << endl;

}

int main() {
        string str = "This is a string for testing the hash function";
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
