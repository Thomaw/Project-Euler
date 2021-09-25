#include <iostream>
using namespace std; 

int main ()
{
    unsigned long int copiedNumber, reversedNumber = 0, reversibleCounter = 0, sum = 0;
    bool isReversible = 0;
    
    for (unsigned long int number = 1; number < 1000000000; number ++) 
    {
        reversedNumber = 0;
        sum = 0;
        
        if (number % 10 == 0) 
        {
           continue;           
        }
        
        copiedNumber = number;
        
        while (copiedNumber > 0)
        {
           reversedNumber *= 10;
           reversedNumber += (copiedNumber % 10);
           copiedNumber /= 10;     
        }
        
        sum = reversedNumber + number;
        
        while (sum > 0)
        {
           if (sum % 2 == 1)
           {
              isReversible = 1;
           }
           
           else 
           {
              isReversible = 0;
              break;
           }        
           
           sum /= 10;
        }
        
        if (isReversible == 1)
        {
           reversibleCounter ++;                 
        }      
    }
    
    cout << reversibleCounter << endl;
    
    system ("PAUSE");
    return 0;
}