#include <iostream>

using namespace std;

int main()
{
    char ca[]="0123456789";
    int i, j, err, checker, check[7]={2,3,5,7,11,13,17};

    for(i=0;i<3628800;i++)
    {
        next_permutation(ca,ca+10);
        
        for(err=0,j=0;j<7;j++)
        {
            checker=100*(ca[j+1]-48)+10*(ca[j+2]-48)+(ca[j+3]-48);
            if(checker%check[j]!=0)
                {err=1;break;}
        }
        if(err==0)
            cout << ca << endl;
    }
    system("pause");   
}
