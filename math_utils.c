#include<stdio.h>
#include<math.h>
#include"math_utils.h"
#include"types.h"

// Custom pow function uses unsigned long long for i/o
ull myPow(ull num, ull x){
    if (x == 1)
        return num;
    else    
        return num * myPow(num , (x-1));
}

// Custom Ceil Division
ull myCeilDiv(ull x,ull y){
	return (unsigned int) ceil(((double) x)/((double) y));
}
