#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int numbers[50000];

bool works(int k);

int main(){
    int num = 27;
    
    for(int i = 0; i < 124; i++, num += 2)while(!works(num))num += 2;
    system("PAUSE");
    return 0;
}

bool works(int k){
     numbers[0] = numbers[1] = numbers[2] = 1;
     for(int i = 3; i < 50000; i++){
             numbers[i] = (numbers[i-1]+numbers[i-2]+numbers[i-3]) % k;
             if(numbers[i] == 0)return false;
     }
     cout << k << " works" << endl;
     return true;
}