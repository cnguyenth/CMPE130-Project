#include "sha1.h"

int main() {
    sha1 test;
    test.set();
    test.hash(test);
}
