int main(int argc,char *argv[])
{
   int n2=1;
   int n3=0;
   int n5=0;
   int n7=0;
   int n=104743;
   
   int state=0;
   long long t=0;
   while (1)
	{
      if (state==0)
	{
         if ((n3==0) &&( n5==0) &&( n7==0))
		{
            printf("%llu %d\n", t,n2);
            if (n2==n)
               return 0;
		}
         
         n3+=n2;
         n5+=n2;
         t+=n2;
         n2=0;
         t+=n7;
         n7=0;
         state=11;
         n5+=1;
         t+=1;
		 }
      else if (state==11){
          t+=2*n3;
         n7+=n3;
         t+=1;
         n3=0;
         state=13;
		 }
      else if (state==13){
         	 int m=n7;
		 if (n5<n7) m=n5;
         t+=m*2;
         n7-=m;
         n2+=m;
         n3+=m;
         n5-=m;
         if (n7){
            t+=1;
            state=17;
            n7-=1;
			}
         else{
            t+=1;
            state=11;
			}
			}
      else if (state==17){
         t+=1;
         if (n3) {
            state=19;
            n3-=1;
			}
         else
            state=0; 
			}
      else if (state==19){
         t+=n2*2;
         n5+=n2;
         n2=0;
         t+=1;
         n7+=1;
         state=11;
		 }
	} 
   return 0;
}