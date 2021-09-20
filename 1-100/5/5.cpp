#include<iostream.h>
#include<conio.h>
void main()
{
  clrscr();
  long i,n;
  int j;
  cout<<"Wait....";
  for(i=2;i<1000000000;i++)
  {
    for(j=20;j>0;j--)
    {
      if(i%j!=0)
	break;
      else
	n=i;
    }
    if(j==0)
     break;
  }
  cout<<"\n\nThe no is "<<n;
  getch();
}
