#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;  
int start[]={-1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};
int endvec[]={-1,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0};
//int endvec[]={0,0,1,1,0,1,1,1,0,-1,0,1,0,0,1,1};
bool isok(vector <int> x,string moves);
long long int convert(vector <int> x);

int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
bool matchvec(vector <int> x);

map <long long int , string> memorize;


int main()
{



  vector <string> currmovesleft;
  vector <vector <int> > currconfigleft;
  currconfigleft.resize(1);
  currmovesleft.resize(0);
  vector <string> nextmovesleft;
  vector <vector <int> > nextconfigleft;
  for(int i=0;i<16;i++)
    currconfigleft[0].push_back(start[i]);



  


  currmovesleft.push_back("");
  int nummoves=0;
  bool done=0;
  while(currconfigleft.size()>0)
    {
      nummoves++;
      printf("%d\n",currmovesleft[0].size());
     
      for(int i=0;i<currconfigleft.size();i++)
	if(matchvec(currconfigleft[i]))
	  {
	    done=1;
	  }
      if(done)
	break;
      nextconfigleft.resize(0);
      nextmovesleft.resize(0);
      for(int i=0;i<currconfigleft.size();i++)
	{
	  /* for(int j=0;j<16;j++)
	    printf("%d,",currconfig[i][j]);
	    printf("\n");*/
	    
	  int pose=-1;
	  for(int j=0;j<16;j++)
	    {
	      if(currconfigleft[i][j]==-1)
		{
		pose=j;
		break;
		}
	    }
	  int posx=pose/4;
	  int posy=pose%4;
	  for(int m=0;m<4;m++)
	    {
	  string movestring=currmovesleft[i];

	      int nextposx=posx+dx[m];
	      int  nextposy=posy+dy[m];
	      
	      if( nextposx>=0 && nextposx<4 && nextposy>=0 && nextposy<4 )
		{
		  vector <int> nextconfigvec;
		  nextconfigvec=currconfigleft[i];
		  nextconfigvec[pose]=currconfigleft[i][nextposx*4+nextposy];
		  nextconfigvec[nextposx*4+nextposy]=-1;

		      if(dx[m]==1)
			movestring.push_back('U');
		      if(dx[m]==-1)
			movestring.push_back('D');
		      if(dy[m]==1)
			movestring.push_back('L');
		      if(dy[m]==-1)
			movestring.push_back('R');
		  if(isok(nextconfigvec,movestring))
		    {
		      
		      // cout << movestring << endl;

		      // cout << movestring << endl;
		      // cout << endl;
		      nextmovesleft.push_back(movestring);
		      nextconfigleft.push_back(nextconfigvec);
		      memorize[convert(nextconfigvec)]=movestring;
		    }

		}
		 
	    }
	}
	  currconfigleft=nextconfigleft;
	  currmovesleft=nextmovesleft;
    }


  // printf("%d\n",nummoves);
  long long int answer=0;
      for(int i=0;i<currmovesleft.size();i++)
	{
	  long long int checksum=0;
	if(matchvec(currconfigleft[i]))
	  {
	    for(int j=0;j<currmovesleft[i].size();j++)
	      {
	      printf("%c",currmovesleft[i][j]);
	      checksum=(checksum*243+currmovesleft[i][j])%100000007;
	      }
	    printf("->%d\n",currmovesleft[i].size());
	  }
	answer+=checksum;
	}
      cout << answer << endl;

}


  bool matchvec(vector <int> x)
  {
    for(int i=0;i<16;i++)
      if(x[i]!=endvec[i])
	return 0;
    return 1;
  }



  bool isok(vector <int> x,string moves)
  {
    long long int codex=convert(x);
    if(memorize.find(codex)==memorize.end())
      return 1;
    if(memorize[codex].size()<moves.size())
      return 0;
    else
      return 1;
    
  }



long long int convert(vector <int> x)
{
  long long retval=0;
  for(int i=0;i<16;i++)
    retval=retval*3+x[i];
  return retval;
}