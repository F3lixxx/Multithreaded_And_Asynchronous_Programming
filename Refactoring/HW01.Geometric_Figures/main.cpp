#include <iostream>
#include "shape.h"
#include "transform.h"

int main (){
    transform transform1;
    transform1.scale(1);
    transform1.scaleX(2);
    transform1.scaleY(3);
    transform1.scaleZ(4);
    transform1.shift(10,20,30);

    return 0;
}
