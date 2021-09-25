long long N=1e10;
double N2=(double)N*N;
double M=4000;

double tot=0;
for (double k=1; k<=1e8; k++) tot+= pow(1- (  4*k*(N+1-k)-2)/(N2), M);
	
cout<<(long long) ((tot+N/2)*1e3)<<endl;