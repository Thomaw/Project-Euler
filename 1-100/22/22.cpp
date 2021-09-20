#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

int main()
{
    int i, j, n, tempsum=0, totsum=0;    
        
    string names[5163];
    
    ifstream readfile("names4.txt");
    for(i=0;!readfile.fail();i++)
    {
        readfile >> names[i];
    }
    readfile.close();  
    
    for(n=0;n<5163;n++)
    {
        for(tempsum=0, j=0;names[n][j];j++)
            tempsum+=int(names[n][j])-64;
    totsum+=tempsum*(n+1);
    }

    cout << totsum << endl;

    system("pause"); 
}
