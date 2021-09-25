#include <stdio.h>
#include <math.h>
 
int main()
{
	int i,p,n,x,y,res,P,depth=26,pow2=1<<depth;
        double dx,diff,sq,y1,y2,fx,area=0.0;
 
	for(p=0;2*p<pow2;p++)  {
		x=p;
		y=0;
		P=pow2;
		for(i=0;i<depth;i++)  {
			res=x&(P-1);
			if(res>P-res)  res=P-res;
                        y+=res;
                        P>>=1;
 
                }
                        fx=(double) y/pow2;
                        dx=(double) p/pow2-0.25;
			sq=sqrt(1.0/16.0-dx*dx);
                        y1=0.5+sq;
                        y2=0.5-sq;
                        if(fx>=y2)  {
                           if(fx<y1)  area+=(double) (fx-y2)/pow2;
                           else       area+=(double) (y1-y2)/pow2;
                        }
 
	}
	printf("area=%.8lf\n",area);
	return 0;
}