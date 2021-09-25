int a=0;            // number of intersections
int t[20000];
int sn[5000][2];    // each intersection on a line gets stored 
                    // max number of intersections on a line = 5000
                    // 2 values are needed to define an intersection
                    // numerator and denominator

// input of t[j]
ifstream inp ("165.txt");
for(int j=0;j<20000;j++)
    {
    inp >> t[j];
    }

// for every line n=2 to 5000
for(int n=2;n<=5000;n++)
   {
   int an=0;                    // number of intersections on the current line
   int x1=t[4*n-4];
   int y1=t[4*n-3];
   int x2=t[4*n-2];
   int y2=t[4*n-1];
   
   // for every line i=1 to n-1 we need to check if it crosses n somewhere.
   for(int i=1;i<=n-1;i++)
      {
      int x3=t[4*i-4];
      int y3=t[4*i-3];
      int x4=t[4*i-2];
      int y4=t[4*i-1];
      int un=(y4-y3)*(x2-x1)-(x4-x3)*(y2-y1);
      
      // if un isn't zero, the two lines cross somewhere.
      if(un!=0)
         {
         int ua=(x4-x3)*(y1-y3)-(y4-y3)*(x1-x3);
         int ub=(x2-x1)*(y1-y3)-(y2-y1)*(x1-x3);
         
         // if 0 < ua/un < 1 and 0 < ub/un < 1 we have a true intersection   
         if(sgn(ua)==sgn(un) && abs(ua)<abs(un) && sgn(ub)==sgn(un) && abs(ub)<abs(un))
                 {
                 a++; // increasing the number of intersections
                 
                 // check wether we've seen this intersection on this line before
                 for(int j=0;j<an;j++)
                    {
                    if(ua*sn[j][1]==sn[j][0]*un)
                        {a-=2;} // if that is the case, both intersections don't count
                    }
                 
                 // storing the new intersection
                 sn[an][0]=ua;
                 sn[an][1]=un;
                 
                 an++; // increasing the number of intersections on the current line
                 }
         }      
      }
   }

cout << a-5;
// a total of 19 lines intersect both 1264 and 2889.
// 12 lines smaller than 2889. 
// they got counted double the rest didn't got counted
// thus -12 + 7 = -5