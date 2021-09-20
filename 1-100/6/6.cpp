#include <iostream>
using namespace std;

int main()
{
    int sum = 0;
    int squareSum;
    int enter;
    int sumSquare = 0;
    cout<<"Enter a number: ";
    cin>>enter;
    cin.ignore();
    for(int i = 0; i < (enter + 1); i++)
    {
            sum = sum + i;
            sumSquare = sumSquare + i * i;
    }
    squareSum = sum * sum;
    cout<<"squareSum: " <<squareSum <<endl;
    cout<<"SumSquare: " <<sumSquare <<endl;
    cout<<"SumSqaure - sqaureSum = " <<squareSum - sumSquare;
    cin.ignore();
    return 0;
}
