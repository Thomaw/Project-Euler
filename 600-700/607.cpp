#define rep(i,l,r)for(int i=l;i<r;i++)

main(){
	double m[6],L[6];
	double l=0,r=2*atan(1);
	rep(n,0,50){//binary search
		m[0]=(l+r)/2;
		L[0]=(50*sqrt(2)-50)*tan(m[0]);
		rep(i,1,6){
			m[i]=asin((1-0.1*i)*sin(m[0]));
			L[i]=10*tan(m[i]);
		}
		double LL=L[0]+L[1]+L[2]+L[3]+L[4]+L[5];
		if(LL>50*sqrt(2))r=m[0];
		else l=m[0];
	}
	double ans=0;
	rep(i,0,6)ans+=L[i]/sin(m[i])/(10-i);
	printf("%.8f",ans);
}