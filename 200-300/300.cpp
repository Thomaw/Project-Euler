#include <stdio.h>              
#include <stdlib.h>             
#include <string.h>             
#include <math.h>               

#define ORIG 50

bool ish[30];
int grid[100][100];

int imax(int x, int y)
{                     
    return x>y?x:y;   
}                     

static int add(int x, int y, int pos, int max, int score, bool show)
{                                                                   
    if (pos>max)                                                    
        return score;                                               

    if (grid[x][y]!=0)
        return 0;     

    if (ish[pos])
    {            
        grid[x][y]=1;
        score+=(grid[x-1][y]==1);
        score+=(grid[x+1][y]==1);
        score+=(grid[x][y-1]==1);
        score+=(grid[x][y+1]==1);
    }                            
    else                         
    {                            
        grid[x][y]=2;            
    }                            
    int nscore=score;            
                                 
    if (pos<max-1)               
    {                            
        nscore=add(x-1,y,pos+1,max,score,show);
        if (pos)                               
        {                                      
            nscore=imax(nscore,add(x+1,y,pos+1,max,score,show));
            nscore=imax(nscore,add(x,y-1,pos+1,max,score,show));
            nscore=imax(nscore,add(x,y+1,pos+1,max,score,show));
        }                                                       
    }                                                           

    grid[x][y]=0;
    return nscore;
}                 

static long make_prots(int pos, int max)
{                                       
    if (pos==max)                       
    {                                   
        int a=0;                        
        int b=max-1;                    

        bool show=false;
        while (a<b)     
        {               
            if (ish[a]==ish[b])
            {                  
                a++;           
                b--;           
                continue;      
            }                  
            if (ish[a])        
                return 2*add(ORIG,ORIG,0,max,0,show);
            else
                return 0;
        }
        return add(ORIG,ORIG,0,max,0,show);
    }
    ish[pos]=false;
    long score=make_prots(pos+1,max);
    ish[pos]=true;


    score+=make_prots(pos+1,max);
    return score;
}


static long doit(long x)
{
    return make_prots(0,x);
}

int main(int argc, char** argv)
{
    long x=atol(argv[1]);
    long answer=doit(x);

    printf("answer is %ld\n",answer);
}