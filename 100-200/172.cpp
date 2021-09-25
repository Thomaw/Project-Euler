#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
long long x=0;

long long f[19];
f[0]=1;
for(int i=1;i<=18;i++)
   {f[i]=f[i-1]*i;}


for(int i0=0;i0<=3;i0++){
for(int i1=0;i1<=3;i1++){
for(int i2=0;i2<=3;i2++){
for(int i3=0;i3<=3;i3++){
for(int i4=0;i4<=3;i4++){
for(int i5=0;i5<=3;i5++){
for(int i6=0;i6<=3;i6++){
for(int i7=0;i7<=3;i7++){
for(int i8=0;i8<=3;i8++){
for(int i9=0;i9<=3;i9++){
	
if(i0+i1+i2+i3+i4+i5+i6+i7+i8+i9==18)
	{
	x=x+f[18]/f[i0]/f[i1]/f[i2]/f[i3]/f[i4]/f[i5]/f[i6]/f[i7]/f[i8]/f[i9];
	if(i0>0)
		{
		x=x-f[17]/f[i0-1]/f[i1]/f[i2]/f[i3]/f[i4]/f[i5]/f[i6]/f[i7]/f[i8]/f[i9];
		}
	}

}}}}}}}}}}

cout<<x;

return 0;
}