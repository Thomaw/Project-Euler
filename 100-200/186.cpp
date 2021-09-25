#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 
int main()  {
    
    double dtime=clock();
    
    long long int L;
 
    int i,k,c,*color,*numcolor,**element,*last,nextpos,call;
    int x,y,c1,c2,p,usedcolor,S[1025];
    color=(int*) (malloc) (1000000*sizeof(int));
    element=(int**) (malloc) (2000000*sizeof(int));
    for(i=0;i<2000000;i++)  element[i]=(int*) (malloc) (2*sizeof(int));
    last=(int*) (malloc) (1000000*sizeof(int));
    numcolor=(int*) (malloc) (1000000*sizeof(int));
    for(i=0;i<1000000;i++)  color[i]=0;
  
    for(k=1;k<=55;k++)  {
        L=k;
        L=(100003-200003*L+300007*L*L*L)%1000000;
        S[k]=L;
    }
    for(i=56;i<1025;i++)  S[i]=(S[i-24]+S[i-55])%1000000;
    
    c=1;
    call=0;
    usedcolor=0;
    nextpos=1000000;
    while(1)  {
          x=S[c];
          y=S[c+1];
          if(x!=y)  {
          c1=color[x];
          c2=color[y];
          if((c1==0)&&(c2==0))  {
              usedcolor++;
              color[x]=usedcolor;
              color[y]=usedcolor;
              element[usedcolor][0]=x;
              element[usedcolor][1]=nextpos;
              element[nextpos][0]=y;
              last[usedcolor]=nextpos;
              nextpos++;
              numcolor[usedcolor]=2;
          }
          else if(c1==0)  {
             color[x]=c2;
             element[last[c2]][1]=nextpos;
             element[nextpos][0]=x;
             last[c2]=nextpos;
             nextpos++;
             numcolor[c2]++;
          }
          else if(c2==0)  {
             color[y]=c1;
             element[last[c1]][1]=nextpos;
             element[nextpos][0]=y;
             last[c1]=nextpos;
             nextpos++;
             numcolor[c1]++;
          }
          else if(c1!=c2)  {
             if(numcolor[c1]<numcolor[c2])  {
                p=c1;
                for(i=0;i<numcolor[c1];i++)  {
                    color[element[p][0]]=c2;
                    p=element[p][1];
                }
                numcolor[c2]+=numcolor[c1];
                element[last[c2]][1]=c1;
                last[c2]=last[c1];
             }
             else {
                p=c2;
                for(i=0;i<numcolor[c2];i++)  {
                   color[element[p][0]]=c1;
                   p=element[p][1];
                }
                numcolor[c1]+=numcolor[c2];
                element[last[c1]][1]=c2;
                last[c1]=last[c2];
             }
          }
          call++;
          }
          c+=2;
          if(c==1025)  {
             for(i=1;i<=56;i++)    S[i]=S[1024-56+i];
             for(i=57;i<1025;i++)  S[i]=(S[i-24]+S[i-55])%1000000;
             c=57;
          }
          if((color[524287]!=0)&&(numcolor[color[524287]]+1>990000)) break;
    }
    printf("calls=%d,time=%.3lf sec.\n",call,(double) (clock()-dtime)/CLOCKS_PER_SEC);
    
    return 0;
}