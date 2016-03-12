#include "tools/G_Vector.h"

int main(int argc, char** argv) {
    CVector<int> a(5), b(5);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    b[0] = 5;
    b[1] = 6;
    b[2] = 7;

    a.dump();

    b.dump();

    printf("a=a+b\n");
    a = a + b;
    a.dump();
    
    printf("b = a*4\n");
    b = a * 4;
    b.dump();

    printf("a=a+b\n");
    a = a + b;
    a.dump();

    return 0;
}
