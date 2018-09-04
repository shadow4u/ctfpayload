#include "stdio.h"
#include "stdlib.h"
//x64
void main(){
   malloc(1);
   unsigned long long *a;
   unsigned long long x[10];
   printf("%p %p",&a,&x[0]);
   x[1]=0x40;//self.size
   a=&x[2];
   x[9]=0x40;//next.presize
   x[10]=0x50;//next.selfsize
   free(a);
}
