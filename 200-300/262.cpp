#include <stdio.h>
#include <math.h>

#define PI  3.1415926535897932385
#define L   0.001
#define opt 10396.46219328410410974086630800431688947354

#define stx 48.30584298702600650754722292
#define sty 624.5037006839436175945351992
#define enx 873.03724286382425682
#define eny 1536.0428163758743303

double dabs(double x)  {
    if(x>0.0)  return x;
    return -x;
}

double h(double x,double y)  {
    return (5000.-0.005*(x*x+y*y+x*y)+12.5*(x+y))*exp(-dabs(0.000001*(x*x+y*y)-0.0015*(x+y)+0.7) );
}

double finddeg(double x,double y,double deg)  {
    
    double pow2=PI,deg2,x0,y0;
    int i;
    for(i=0;i<32;i++)  {
        pow2/=2.0;
        deg2=deg-pow2;
        x0=x+cos(deg2)*L;
        y0=y+sin(deg2)*L;
        if((h(x0,y0)<=opt)&&(x0>=0.0)&&(x0<=1600.0)&&(y0>=0.0)&&(y0<=1600.0))  deg=deg2;
    }
    if(deg<0.0)  deg+=2.0*PI;
    if(deg>2.0*PI) deg-=2.0*PI;
    return deg;
}



int main()  {
    
    int i;
    double x,y,dx,dy,deg=PI,len=0.0;
    
    x=stx;
    y=sty;
    for(i=0;;i++)  {
        len+=L;
        deg=finddeg(x,y,deg);
        x+=cos(deg)*L;
        y+=sin(deg)*L;
        if(i%1000==0)  printf("iter=%d,x=%lf,y=%lf,dist=%lf\n",i,x,y,dabs(h(x,y)-opt));
        if(x>enx)  break;
    }
    dx=200.0-stx;
    dy=200.0-sty;
    len+=sqrt(dx*dx+dy*dy);
    dx=1400.0-enx;
    dy=1400.0-eny;
    len+=sqrt(dx*dx+dy*dy);
    printf("total length=%.3lf\n",len);
    
    return 0;
}