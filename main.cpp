#include <iostream>
#include <vector>
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
        cout << "Length = " << length << endl;
        
        //binaryStr.push_back(128);

        // string testString = binaryStr[0].to_string();
        // cout << "Test: " << testString << endl;


}

int main() {
        string str = "This is a string for testing the hash function";
        sha1(str);
        return 0;
}
