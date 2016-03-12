#include "tools/G_Vector.h"

int main(int argc, char** argv) {
    CVector<int> a(5), b(5); 
    a[1] = 567;
    a[2] = 4;
    a[4] = -7;

    b[2] = 19;
    b[4] = 6;

    a.dump();
    b.dump();
    
    printf("a = a + b * 8");

    a = a + b * 8;
    
    a.dump();

    a[6] = 67;  // must cause an error

    return 0;
}
