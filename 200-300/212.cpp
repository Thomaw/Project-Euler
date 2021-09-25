#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int MAX(int x,int y)  {
    if(x<y)  return y;
    return x;
}
int MIN(int x,int y)  {
    if(x<y)  return x;
    return y;
}

int main()  {
    
    double dtime=clock();
    int *S,*x0,*y0,*z0,*dx,*dy,*dz,k,n,*ct,**perm;
    int a1,a2,a3,R,x,y,z,count,fx,fy,fz,lx,ly,lz;
    int *X1,*X2,*Y1,*Y2,*Z1,*Z2,*parity,w,r1,r2,r3,i,p,all,all2;
    int xx1,xx2,yy1,yy2,zz1,zz2,xxx1,xxx2,yyy1,yyy2,zzz1,zzz2;
    int x1[32],x2[32],y1[32],y2[32],z1[32],z2[32],F=50000;
    long long int K,res,vol;
    S=(int*)(malloc)(300001*sizeof(int));
    x0=(int*)(malloc)(50001*sizeof(int));
    y0=(int*)(malloc)(50001*sizeof(int));
    z0=(int*)(malloc)(50001*sizeof(int));
    dx=(int*)(malloc)(50001*sizeof(int));
    dy=(int*)(malloc)(50001*sizeof(int));
    dz=(int*)(malloc)(50001*sizeof(int));

    X1=(int*)(malloc)(100000*sizeof(int));
    X2=(int*)(malloc)(100000*sizeof(int));
    Y1=(int*)(malloc)(100000*sizeof(int));
    Y2=(int*)(malloc)(100000*sizeof(int));
    Z1=(int*)(malloc)(100000*sizeof(int));
    Z2=(int*)(malloc)(100000*sizeof(int));
    parity=(int*)(malloc)(100000*sizeof(int));

    ct=(int*)(malloc)(17576*sizeof(int));
    perm=(int**)(malloc)(17576*sizeof(int));

    for(k=1;k<=55;k++)  {
        K=k;
        res=100003-200003*K+300007*K*K*K;
        res%=1000000;
        S[k]=res;
    }
    for(k=56;k<=300000;k++)
        S[k]=(S[k-24]+S[k-55])%1000000;
    
    for(n=1;n<=50000;n++)  {
        x0[n]=S[6*n-5]%10000;
        y0[n]=S[6*n-4]%10000;
        z0[n]=S[6*n-3]%10000;
        dx[n]=1+(S[6*n-2]%399);
        dy[n]=1+(S[6*n-1]%399);
        dz[n]=1+(S[6*n]%399);
    }
    
    for(n=0;n<17576;n++)  ct[n]=0;
    for(n=1;n<=F;n++)  {
        R=(x0[n]/400)*676+(y0[n]/400)*26+(z0[n]/400);
        
        x=x0[n]/400;
        if(x0[n]+dx[n]>=400*(x+1))  a1=1;
        else  a1=0;
        y=y0[n]/400;
        if(y0[n]+dy[n]>=400*(y+1))  a2=1;
        else  a2=0;
        z=z0[n]/400;
        if(z0[n]+dz[n]>=400*(z+1))  a3=1;
        else  a3=0;
        
        ct[R]++;
        if(a1)  ct[R+676]++;
        if(a2)  ct[R+26]++;
        if(a3)  ct[R+1]++;
        if(a1+a2==2)  ct[R+676+26]++;
        if(a2+a3==2)  ct[R+26+1]++;
        if(a3+a1==2)  ct[R+1+676]++;
        if(a1+a2+a3==3) ct[R+676+26+1]++;
    }
    for(n=0;n<17576;n++)  perm[n]=(int*)(malloc)(ct[n]*sizeof(int*));
    for(n=0;n<17576;n++)  ct[n]=0;
    
    for(n=1;n<=F;n++)  {
        R=(x0[n]/400)*676+(y0[n]/400)*26+(z0[n]/400);
        
        x=x0[n]/400;
        if(x0[n]+dx[n]>=400*(x+1))  a1=1;
        else  a1=0;
        y=y0[n]/400;
        if(y0[n]+dy[n]>=400*(y+1))  a2=1;
        else  a2=0;
        z=z0[n]/400;
        if(z0[n]+dz[n]>=400*(z+1))  a3=1;
        else  a3=0;
        
        w=R,perm[w][ct[w]]=n,ct[w]++;
        if(a1)  w=R+676,perm[w][ct[w]]=n,ct[w]++;
        if(a2)  w=R+26,perm[w][ct[w]]=n,ct[w]++;
        if(a3)  w=R+1,perm[w][ct[w]]=n,ct[w]++;
        if(a1+a2==2)  w=R+676+26,perm[w][ct[w]]=n,ct[w]++;
        if(a2+a3==2)  w=R+26+1,perm[w][ct[w]]=n,ct[w]++;
        if(a3+a1==2)  w=R+1+676,perm[w][ct[w]]=n,ct[w]++;
        if(a1+a2+a3==3)  w=R+676+26+1,perm[w][ct[w]]=n,ct[w]++;
    }
    vol=0;
    for(n=0;n<17576;n++)  {
        r1=n/676;
        r2=(n/26)%26;
        r3=n%26;
        fx=r1*400;
        lx=fx+400;
        fy=r2*400;
        ly=fy+400;
        fz=r3*400;
        lz=fz+400;
        count=ct[n];
        for(i=0;i<count;i++)  {
             p=perm[n][i];
             x1[i]=MAX(fx,x0[p]);
             x2[i]=MIN(lx,x0[p]+dx[p]);
             y1[i]=MAX(fy,y0[p]);
             y2[i]=MIN(ly,y0[p]+dy[p]);
             z1[i]=MAX(fz,z0[p]);
             z2[i]=MIN(lz,z0[p]+dz[p]);
        }
        X1[0]=fx;
        X2[0]=lx;
        Y1[0]=fy;
        Y2[0]=ly;
        Z1[0]=fz;
        Z2[0]=lz;
        parity[0]=0;
        all=1;
        
        for(i=0;i<count;i++)  {
            all2=all;
            xxx1=x1[i],xxx2=x2[i];
            yyy1=y1[i],yyy2=y2[i];
            zzz1=z1[i],zzz2=z2[i];
            for(k=0;k<all;k++)  {
                xx1=MAX(X1[k],xxx1);
                xx2=MIN(X2[k],xxx2);
                yy1=MAX(Y1[k],yyy1);
                yy2=MIN(Y2[k],yyy2);
                zz1=MAX(Z1[k],zzz1);
                zz2=MIN(Z2[k],zzz2);
               if((xx1<xx2)&&(yy1<yy2)&&(zz1<zz2))  {
                  X1[all2]=xx1;
                  X2[all2]=xx2;
                  Y1[all2]=yy1;
                  Y2[all2]=yy2;
                  Z1[all2]=zz1;
                  Z2[all2]=zz2;
                  parity[all2]=1-parity[k];
                  if(parity[all2])  vol+=(xx2-xx1)*(yy2-yy1)*(zz2-zz1);
                  else              vol-=(xx2-xx1)*(yy2-yy1)*(zz2-zz1);
                  all2++;
               }
           }
           all=all2;
       }
    }
    printf("volume=%I64d, time=%.3lf sec.\n",vol,(double) (clock()-dtime)/CLOCKS_PER_SEC);   
    
    return 0;
}