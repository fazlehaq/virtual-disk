#include<stdio.h>
#include<math.h>
#include"../headers/math_utils.h"
#include"../headers/types.h"

// Custom pow function uses unsigned long long for i/o
ull myPow(ull num, ull x){
    if (x == 1)
        return num;
    else    
        return num * myPow(num , (x-1));
}

// Custom Ceil Division
ull myCeilDiv(ull x,ull y){
	// return (unsigned int) ceil(((double) x)/((double) y));
    return x/y + ((x%y == 0) ? 0 : 1);
}
