__int64 prob277(void)
{
char *seq="UDDDUdddDDUDDddDdDddDDUDDdUUDd";
__int64 p,q,n, ip, o, f;
int i, l=strlen(seq);

// define a(x) = (p*a0+q)/n
p=n=1;
q=0;
for(i=0;i<l;i++){
	switch(seq[i]){
		case 'D': n*=3; break;
		case 'U': p*=4; q=4*q+2*n; n*=3; break;
		case 'd': p*=2; q=2*q-n; n*=3; break;
		}
	}
ip=nt->modinverse(p,n);    // ip=inverse of p (mod n)
o=nt->modproduct(ip,-q,n); // offset = ip*(-q) (mod n)
f=(1000000000000000-o)/n + 1;  // factor = floor((10^15-offset)/n) + 1
return(o+f*n);  // result = offset + factor*n
}