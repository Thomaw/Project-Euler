void nolla(int* x,int MAX)
{
	for (int i=0;i<MAX;i++)
		x[i]=0;
}

int main()
{
	int MAX=1000;
	int rest,d,antal,tal,i,maxd,maxantal=0;
	int r[MAX];
	
	for (d=2;d<MAX;d++)
	{
		nolla(r,MAX);
		tal=10;
		while (tal<d)
			tal*=10;
		i=1;
		rest=tal%d;
		while (r[rest]==0){
			r[rest]=i;
			rest=(rest*10)%d;
			i++;
		}
		antal=i-r[rest];
		if (antal>maxantal)
		{
			maxd=d;
			maxantal=antal;
		}
	}
	cout<<"Max f?r "<<maxd<<" med "<<maxantal<<" decimaler"<<endl;
}
