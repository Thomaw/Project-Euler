#include<stdio.h>
#include<time.h>
typedef unsigned long long u;
u choix(int n){
  u  A = 15,B = 43,C = 41,D = 1;
  for(int i = 0;i < n - 1;++i) A *= 16;
  for(int i = 0;i < n - 1;++i) B *= 15;
  for(int i = 0;i < n - 1;++i) C *= 14;
  for(int i = 0;i < n;++i) D *= 13;
  
  return (A - B + C - D);
            
}
int main(){
    clock_t time = clock();
    u result = 0;
    for(int i = 3;i <= 16;++i) result += choix(i);
    time = clock() - time;
    printf("%llX in %.0lf ms.\n",result,time+.0);
    //3D58725572C62302 in 0 ms.
    return 0;
    
}