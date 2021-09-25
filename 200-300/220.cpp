#include <stdio.h>
#include <string.h>

typedef long long LL;

LL X[64],Y[64],P[64];

int main(){
	int i;
	LL x,y,p,tar,ox,oy;
	
	tar=1000000000000LL;
	
	//scanf("%lld",&tar);

	x=0; y=1; p=1; i=2;
	X[1]=x; Y[1]=y; P[1]=1;
	while (p<10000000000000LL){
		ox=x; oy=y;
		x=ox+oy;
		y=oy-ox;
		p=p+p;
		X[i]=x; Y[i]=y; P[i]=p; i++;
		printf(" %lld (%lld,%lld) %lld\n",p,x,y,P[i-1]);
	}
	LL tarx,tary;
	tarx=0; tary=0; x=1; y=1; i--;
	int dir=0;
	while (tar>0){
		if (tar>P[i]){
			printf("[%lld %lld] %d %lld %lld\n",X[i+1]*x,Y[i+1]*y,i+1,x,y);
			switch(dir){
				case 0: x= X[i+1]; y= Y[i+1]; break;
				case 1: x= Y[i+1]; y=-X[i+1]; break;
				case 2: x=-X[i+1]; y=-Y[i+1]; break;
				case 3: x=-Y[i+1]; y= X[i+1]; break;
			}
			tarx+=x; tary+=y;
			tar=P[i+1]-tar;
			dir=(dir+3)%4;
		}
		i--;
	}
	printf("<%lld,%lld>\n",tarx,tary);
	return 0;
}