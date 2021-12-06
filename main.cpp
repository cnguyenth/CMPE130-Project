#include "sha1.h"

int main() {
    sha1 test;
    test.set();
    test.hash(test);
}
#include "SHA1.h"
#include "md5.h"
#include "SHA2-256.h"
#include "SHA3-256.h"

int main() {

    //SHA1
    SHA1 sha1;
    sha1.set();
    sha1.hash(sha1);

    //MD5
    MD5 md5;
    string input_md5;
    cout << "(MD5)Enter a string to hash: ";
    cin >> input_md5;
    string myHash = md5(input_md5);
    cout << "Result = " << myHash << endl << endl;

    //SHA2_256
    SHA256 sha2_256;
    string input_sha2;
    cout << "(SHA2)Enter a string to hash: ";
    cin >> input_sha2;
    string myHash2 = sha2_256(input_sha2);
    cout << "Result = " << myHash2 << endl << endl;
    

    //SHA3_256
    SHA3 sha3_256;
    string input_sha3;
    cout << "(SHA3)Enter a string to hash: ";
    cin >> input_sha3;
    string myHash3 = sha3_256(input_sha3);
    cout << "Result = " << myHash3 << endl << endl;

    return 0;
}
