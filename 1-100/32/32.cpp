
#include<stdio.h>

long sum;
int num;
char s[15]={1},stat[9900],string[5];

void one_digit(void);
void two_digits(void);
void three_digits(void);
void four_digits(void);

void one_digit(){
  int i;
  for(i=2;i<9;i++){
    if(i!=5){
      s[i]=1;
      num=i;
      four_digits();
      s[i]=0;
      }
    }
  }

void two_digits(){
  int i,j;
  for(i=1;i<8;i++){
    s[i]=1;
    for(j=2;j<10;j++){
      if(!s[j]&&j!=5){
	s[j]=1;
	num=i*10+j;
	three_digits();
	s[j]=0;
	}
      }
    s[i]=0;
    }
  }

void three_digits(){
  int i,j,k,l,m=0,n;
  for(i=1,l=num%10;i<10;i++){
    if(!s[i]){
      s[i]=1;
      for(j=1;j<10;j++){
	if(!s[j]){
	  s[j]=1;
	  for(k=2;k<10;k++){
	    if(!s[k]&&!s[(k*l)%10]&&(k*l)%10!=k){
	      m=num*(i*100+j*10+k);
	      if(m>9876) break;
	      s[k]=1;
	      sprintf(string,"%i",m);
	      for(n=0;n<4;n++){
		if(s[string[n]-48]){
		  while(--n!=-1) s[string[n]-48]=0;
		  break;
		  }
		s[string[n]-48]=1;
		}
	      if(n==4){
		if(!stat[m]){
		  stat[m]=1;
		  sum+=m;
		  }
		while(--n!=-1) s[string[n]-48]=0;
		}
	      s[k]=0;
	      }
	    }
	  s[j]=0;
	  if(m>9876) break;
	  }
	}
      s[i]=0;
      if(m>9876) break;
      }
    }
  }

void four_digits(){
  int i,j,k,l,m=0,n,p;
  for(i=1,p=num%10;i<10;i++){
    if(!s[i]){
      s[i]=1;
      for(j=1;j<10;j++){
	if(!s[j]){
	  s[j]=1;
	  for(k=1;k<10;k++){
	    if(!s[k]){
	      s[k]=1;
	      for(l=2;l<10;l++){
		if(!s[l]&&!s[(p*l)%10]&&(p*l)%10!=l){
		  m=num*(i*1000+j*100+k*10+l);
		  if(m>9876) break;
		  s[l]=1;
		  sprintf(string,"%i",m);
		  for(n=0;n<4;n++){
		    if(s[string[n]-48]){
		      while(--n!=-1) s[string[n]-48]=0;
		      break;
		      }
		    s[string[n]-48]=1;
		    }
		  if(n==4){
		    if(!stat[m]){
		      stat[m]=1;
		      sum+=m;
		      }
		    while(--n!=-1) s[string[n]-48]=0;
		    }
		  s[l]=0;
		  }
		}
	      s[k]=0;
	      if(m>9876) break;
	      }
	    }
	  s[j]=0;
	  if(m>9876) break;
	  }
	}
      s[i]=0;
      if(m>9876) break;
      }
    }
  }

void main(){
  two_digits();
  one_digit();
  printf("%li\n",sum);
  }
