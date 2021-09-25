#include <stdio.h>
#include <math.h>

/*
y*( 4*r - y ) = n;
*/

int main(){
	int n,y,r,sqr,acc,count=0;
	
	for(n=1;n<50000000;n++){
	
		sqr=(int)sqrt((double)n);
		sqr++;
		acc=0;
	
		for(y=1;y<sqr;y++){
			if(n%y==0){
				if( (n/y+y)%4==0 ){
					r=(n/y+y)/4;
					if(r<y){
						acc++;
					}
					if(r<n/y && n/y!=y){
						acc++;
					}
				}
			}
			if(acc>1)
				break;
		}

		if(acc==1) count++;
		
		if(n%1000000==0) printf("%d",n);
	}
	
	printf("%d\n",count);
	return 0;
}