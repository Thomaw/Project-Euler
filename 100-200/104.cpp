typedef unsigned __int64 nrt;

bool IsPandigit(nrt nNr)
{
	char vec[10];
	for(int i=0; i<sizeof(vec)/sizeof(*vec); i++)
		vec[i]=0;
	    
	while (nNr!=0)
	{
		vec[nNr%10]++;
		nNr/=10;
	}

	for(int i=1; i<=9; i++)
		if(vec[i]>1 || vec[i]==0)
			return false;

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	nrt top[2] = {1,1};
	nrt bot[2] = {1,1};

	const nrt nrtMax = ~((nrt)0);
	time_t start = clock();

	for(int k=3; true; k++)
	{
		nrt newTop = top[0] + top[1];
		nrt newBot = bot[0] + bot[1];
		if(newBot>=1000000000)
		{
			newBot%=1000000000;
			bot[1]%=1000000000;
		}
		bot[0] = bot[1];
		bot[1] = newBot;
		if(newTop>=nrtMax/10)
		{
			newTop/=10;
            top[1]/=10;
		}
		top[0]=top[1];
		top[1]=newTop;

		while (newTop>1000000000)
			newTop/=10;
		if(IsPandigit(newTop) && IsPandigit(newBot))
		{
			time_t end = clock();
			std::cout <<"k=" << k << ", took " << end-start << "ms";
			break;
		}
	}
	return 0;
}