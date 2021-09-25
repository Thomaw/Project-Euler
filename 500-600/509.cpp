#include <iostream>
#include <vector>

using namespace std;
const uint64_t LIM=123456787654321LL;
const uint64_t MASK=1234567890LL;

int main()
{
    vector<uint64_t> sg;
    uint64_t temp,i,j,total;
    temp=LIM;
    while(temp!=0)
    {
        sg.push_back(temp);
        temp>>=1;
    }
    for(i=0;i<sg.size()-1;i++) sg[i]=(sg[i]-sg[i+1])%MASK;
    total=0;
    for(i=0;i<sg.size();i++) for(j=0;j<sg.size();j++) total=(sg[i]*sg[j]%MASK*sg[i^j]+total)%MASK;
    temp=LIM%MASK;
    total=(temp*temp%MASK*temp+MASK-total)%MASK;
    cout << total << endl;
    return 0;
}
