#include <iostream>

using namespace std;

int check(int number);

int main()
{
    int number, sum=0;
    for(number=1;number<1000000;number+=2)
        if(check(number))  
            sum+=number;
    
    cout << "The sum is " << sum << "." << endl;
      
    system("pause");    
}

int check(int number)
{
    char decimal[6], binary[20];
    int dec_length, bin_length, i;
    
    itoa(number, decimal, 10);
    
    for(i=0;decimal[i];i++)
        dec_length=i+1;
    
    for(i=0;i<dec_length/2;i++)
        if(decimal[i]!=decimal[dec_length-i-1])
            return 0;
    
    itoa(number, binary, 2);
    
    for(i=0;binary[i];i++)
        bin_length=i+1;
    
    for(i=0;i<bin_length/2;i++)
        if(binary[i]!=binary[bin_length-i-1])
            return 0;
    
    return 1;  
}
