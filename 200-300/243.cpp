void prob243(void)
{
double d,t;
int i;

i=0;
t=15499.0/94744.0;
d=2.0;
while(d>=t){
	i+=210;
	d=(double)nt->EulerPhi(i)/(double)(i-1);
	}
printf("%d\n",i);
}
