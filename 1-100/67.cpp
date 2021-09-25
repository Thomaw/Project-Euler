#define numlines 100

int main()
{
  	
  	int** lines = new int*[numlines];
  	int linelen[numlines];
  	
  	for(int i=0; i<numlines; i++) linelen[i] = i+1;
  	
   	ifstream in_triangle("triangle.txt");
   	
   	// read in the textfile
   	for (int i=0;i<numlines;i++)
   	{
   		lines[i] = new int[i+1];
   		linelen[i] = i+1;
   		for (int j=0; j<i+1; j++)
   		{
       		in_triangle>>lines[i][j];
       	}
       	in_triangle.ignore(1,'\n');
   	}
  	
   	int routes1[numlines];
   	int routes2[numlines];
   	
   	for (int i=0;i<numlines;i++) routes1[i] = lines[numlines-1][i];

   	//find the best way
   	for (int i=numlines-2;i>=0;i--)
   	{	
     	for(int j=0;j<i+1;j++)
   		{
   			if(routes1[j] > routes1[j+1])
   			{
      			routes2[j] = routes1[j] + lines[i][j];
            } else
            {
            	routes2[j] = routes1[j+1] + lines[i][j];
            }
     	}
     	for (int i=0;i<numlines;i++) routes1[i] = routes2[i];
   	}
   	cout<<"the sum is: "<<routes1[0]<<endl;
}
