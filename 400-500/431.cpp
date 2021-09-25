double Volume431(double r,double x,double alpha,int prec)
{
double t=tan((alpha/180.0)*M_PI);
double h1=(r-x)*t; // "right" top of the  grain
double h2=(r+x)*t; // "left" top of the grain
double increm=(h2-h1)/prec; // integration increments
double res=0.0;
// integral from h2 to h1
if(increm!=0.0) { // "lens" integration, "slice" integral, in prec steps
	for(int i=0;i<prec;i++) {
		double d=(h2-increm*(i+0.5))/t; // radius of the grain circle
		res+=d*d*acos((d*d-r*r+x*x)/(2.0*x*d)); // lens area
		res+=r*r*acos((r*r+x*x-d*d)/(2.0*x*r));
		res-=0.5*sqrt((d*d-(r-x)*(r-x))*((r+x)*(r+x)-d*d));
	}
        res*=increm;
}
res+=M_PI*h1*(r-x)*(r-x)/3.0; // top part : cone with base r-x and height h1
res=M_PI*r*r*h2-res; // empty volume
return res;
}