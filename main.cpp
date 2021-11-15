#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

void sha1(const string str){
        cout << "Original message: " << str << endl;

        vector<bitset<8> > binaryStr;
        for (int i = 0; i < str.size(); i++)
        {
              binaryStr.push_back(bitset<8>(str[i]));
        }

        cout << "Original message to binary: " << endl;
        for(unsigned i = 0; i< binaryStr.size(); i++) 
        {
                cout << binaryStr[i] << " ";
        }
        cout << endl;

        int length = binaryStr.size() * 8; //size = 1 byte or 8 bits
        cout << "Length = " << length << endl << endl;
        
        binaryStr.push_back(bitset<8>(128)); //128 = 10000000 in binary. Adds the '1' bit then some of the following zero's to message
        int numPadBits = 448 - (8 + length);
        numPadBits = numPadBits/8; 
        for(unsigned i = 0; i < numPadBits; i++)
        {
                binaryStr.push_back(bitset<8>(0));
        }
        cout << "Pad the message so its length is equal to 448mod512: " << endl;
        for(unsigned i = 0; i < binaryStr.size(); i++) 
        {
                cout << binaryStr[i] << " ";
        }
        cout << endl;

        bitset<64> binaryLength = bitset<64>(length);   //a 64 bit value which represents the original length        
        //break up 64 bit bitset into 8 bits so they can be put in vector
        for(int i = 56; i >= 8; i = i - 8)
        {
                binaryStr.push_back(bitset<8>((binaryLength >> i).to_ulong()));
        }
        binaryStr.push_back(bitset<8>(binaryLength.to_ulong()));

        cout << "64-bit value is added to the message: " << endl;
        for(unsigned i = 0; i < binaryStr.size(); i++) 
        {
                cout << binaryStr[i] << " ";
        }
        cout << endl;

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
