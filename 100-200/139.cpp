#include <iostream>

#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X, Y) ((X) > (Y) ? (Y) : (X))

unsigned long count = 0;

void triangle(unsigned long x, unsigned long y, unsigned long z) {
    
    unsigned long perim = x + y + z;
    
    if( perim > 1e8 )
        return;
    
    if ( z % (MAX(x, y) - MIN(x, y)) == 0 ) {
        std::cout << "Found primitive: (" << x << ", "
                  << y << ", " << z << ")" << std::endl;
        count += 1e8 / perim;
    }
    
    triangle( x-2*y+2*z,  2*x-y+2*z,  2*x-2*y+3*z);
    triangle( x+2*y+2*z,  2*x+y+2*z,  2*x+2*y+3*z);
    triangle(-x+2*y+2*z, -2*x+y+2*z, -2*x+2*y+3*z);  
}

int main() {
    triangle(3, 4, 5);
    std::cout << count << std::endl;
    return 0;
}