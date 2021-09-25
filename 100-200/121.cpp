#include<iostream>
using namespace std;

long long calcdenom(int rounds);
long long getmasknumerator(int* mask, int rounds);
long long calcnumerator(int rounds);

int main()
{ 
  long long numerator,denominator;
  double a,b;
  
  denominator = calcdenom(15);
  numerator = calcnumerator(15);
 
  cout << "numerator " << numerator 
      << " denominator " << denominator << endl; 
  
  a=(double)numerator/denominator;
  b=(double)denominator/numerator;
  
  cout << a << endl;
  cout << b << endl;
  return 0;
}

//Function to calculate the denominator for any number
//of rounds asuming we start with 2 balls and add a ball
//at each round
long long calcdenom(int rounds)
{
  int i_work;
  long long i_tot;
  for(i_work=2,i_tot=1;i_work<rounds+2;i_work++){
    i_tot = i_tot*i_work;
  }
  return i_tot;
}

//This routine needs to visit every winning combination and find 
//the numerator resulting from each possibility
//in order to be a winning combination a maximum of seven
//red balls can be drawn in 15 rounds.  We generate a mask of ones and zeros
//representing each round a one indicating that a red ball was drawn.
//This is done with a series of nested for loops.  There has to be a better / more flexible way of doing this - so we pass rounds as a //parameter for when we work out how we should do this!
long long calcnumerator(int rnds){
  int mask[rnds];
  int a,b,c,d,e,f,g;  //Control the for loops 7 vars one for each 
                      //possible red ball before we lose
  long long runningtot=0;
   
  //Default to all balls being blue
  for(a=0;a<rnds;a++) mask[a]=0; 
  runningtot = runningtot+getmasknumerator(mask,rnds);
  
  //incrementally set positions red exploring all possibilitiies
  //that still result in a winning position
  for(a=0;a<rnds;a++){
    mask[a]=1;
    runningtot = runningtot+getmasknumerator(mask,rnds); 
    
    for(b=a+1;b<rnds;b++){
      mask[b]=1;
      runningtot = runningtot+getmasknumerator(mask,rnds);
      
      for(c=b+1;c<rnds;c++){
        mask[c]=1;
        runningtot = runningtot+getmasknumerator(mask,rnds);
        
        for(d=c+1;d<rnds;d++){
          mask[d]=1;
          runningtot = runningtot+getmasknumerator(mask,rnds);
          
          for(e=d+1;e<rnds;e++){
            mask[e]=1;
            runningtot = runningtot+getmasknumerator(mask,rnds);
            
            for(f=e+1;f<rnds;f++){
              mask[f]=1;
              runningtot = runningtot+getmasknumerator(mask,rnds);
              
              for(g=f+1;g<rnds;g++){
                mask[g]=1;
                runningtot = runningtot+getmasknumerator(mask,rnds);
                
                mask[g]=0;
              }
              mask[f]=0;
            }
            mask[e]=0;
          }
          mask[d]=0;
        }
        mask[c]=0;
      }
      mask[b]=0;
    }
    mask[a]=0;
  }
  return runningtot;   
}    

//routine to visit all elements of a mask and multiply
//together - this assumes that the mask is that of a winning 
//solution and that the ones indicate rounds in which a red ball was 
//drawn - so the numerator is the product of all the red balls, which //starts with one in the 1st round and increases by 1 each round
//special case if all balls are blue therefore mask is all 0's
//make the numerator 1 (1*1*1*1. . . .)
long long getmasknumerator(int* mask, int rounds)
{
  int pos;
  int balls;
  unsigned long wrkprod=1;
  for(pos=0,balls=1;pos<rounds;pos++,balls++)
  {
    if(mask[pos]) wrkprod=wrkprod *balls;
  }
  return wrkprod;
}