#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

struct data{
	bool marked;
	bool connected;
	int  value;
};

int main()
{
	clock_t start, end;
	start = clock();
	ifstream in;
	in.open("network.txt");

	const int n = 40;
	int initial = 0, pruned = 0, i, j, min, k, l;
	data adj[n][n];
	bool done = false;
	char temp;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			temp = in.peek();
	
			if(temp == '-')
			{
				in >> temp;
				adj[i][j].value = -1;
			}
			else
			{
				in >> adj[i][j].value;
				initial += adj[i][j].value;
			}
			
			adj[i][j].connected = adj[i][j].marked = false;

			if(j != n-1)
				in >> temp; 
			else
				in.ignore(1, '\n');
		}
	}

	i = j = 0;

	bool first = true;
	
	while(!done)
	{
		if(first)
		{
			if(adj[i][j].value != -1)
			{
				min = adj[i][j].value;
				k = i; 
				l = j;
				i++;
				while(i < n)
				{
					if(adj[i][j].value < min &&  adj[i][j].value != -1)
					{
						min = adj[i][j].value; 
						k = i; 
						l = j;
					}
					i++;
				}

				adj[k][l].value = -1;

				for(i = 0; i <n; i++)
				{
					if(i == 0)
					{
						for(j = 0; j <n; j++)
							adj[i][j].marked = true;
					}
					adj[i][l].connected = true;
				}

				first = false;
			}
			else
				i++;
		}
		else
		{
			min = INT_MAX;
			for(i = 0; i < n; i++)
			{
				if(adj[i][0].marked)
				{
					for(j = 1; j <n; j++)
					{
						if(!adj[i][j].connected && adj[i][j].value != -1
							&& adj[i][j].value < min)
						{
							min = adj[i][j].value;
							k = i;
							l = j;
						}
					}
				}
			}

			pruned += min;
			adj[k][l].value = -1;

			for(i = 0; i <n; i++)
			{
				if(i == l)
				{
					for(j = 0; j <n; j++)
						adj[i][j].marked = true;
				}
				adj[i][l].connected = true;
			}

			done = true;
			for(i = 0; i < n; i++)
			{
				if(!adj[0][i].connected)
				{
					done = false;
					break;
				}
			}
		}
	}

	end = clock();

	cout << initial / 2 - pruned << endl;
	cout << "Computation Time: " << ((double) (end - start)) << "ms\n";

	return 0;
}