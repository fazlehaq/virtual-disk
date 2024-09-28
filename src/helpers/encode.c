#include<stdio.h>
#include<math.h>
#include"../headers/math_utils.h"
#include"../headers/encode_utils.h"
#include"../headers/types.h"

// encode returns the number of bits used to encode the given sequence
int encode(unsigned char* in, unsigned char* out,unsigned char n , unsigned char level, unsigned int bitoffset){
        int pos;
	
	if(n==0){
	        setbit(out,bitoffset+0,0);
                setbit(out,bitoffset+1,0);
                pos = 2;
                if(level == 0) { setbit(out,bitoffset+pos,0); pos++; }
                return pos;
	}

        if(n==1){
                setbit(out,bitoffset+0,0);
                setbit(out,bitoffset+1,1);
                pos = 2;
                if(level == 0) { setbit(out,bitoffset+pos,0); pos++; }
                return pos;

        }

        else if(n==2){
                setbit(out,bitoffset+0,getbit(in,0));
                setbit(out,bitoffset+1,getbit(in,1));
                pos = 2;
                if(level == 0) { setbit(out,bitoffset+pos,0); pos++; }
                return pos;
        }

        unsigned char next_n = 8;
        unsigned char next_in = n;
        unsigned char i;

        while(next_in < 128) {
                next_in = next_in << 1;
                next_n--;
        }

        pos = encode(&next_in,out,next_n,level+1,bitoffset);

        for(i=0;i<n;i++) setbit(out,bitoffset+pos+i,getbit(in,i));

        pos = pos + n;

        if (level == 0 ) { setbit(out,bitoffset+pos,0); pos++; }

        return pos;
}

ull decode(unsigned char* in,ull bitoffset) {

          ull number = 0;
          ull jump = 2;
          ull elts = 0;
          ull power;
          ull i = 0;
  
          do{
                  power = myPow(2,(jump-1));
                  elts += jump;
                  number = 0;
                  for(int k=0 ; k<jump; k++) {
                        // printf("getting %llu bit \n",i+bitoffset);
                          number += power * getbit(in,i+bitoffset);
                          i++;
                          power /= 2;
                  }
                  jump = number;
          }while(getbit(in,elts+bitoffset));
  
          return number;
}
  
ull bitsToEncode(ull n){

        if (n <= 3) {
                return 2; // For 3 or less, we need 2 bits
        } else {
        // Calculate the number of bits required to represent `n`
        ull bits = (ull)(ceil(log2(n + 1)));
        // Recursively call for the number of bits, then add 0 at the end of encoding
        return bits + bitsToEncode(bits);
        }
}
ull getNumOfBitsToEncode(ull n)  {
        return bitsToEncode(n) + 1;
}