for (ll p=1;p*p*p*p*4<=N;p++) for (ll q=p;q*q*(p+q)*(p+q)<=N;q++) if (__gcd(p,q)==1) {
		ll d=N/q/q/(p+q)/(p+q);
		ans+=d*(d+1)/2*((p*p+q*q)*(p+q)*(p+q)+p*p*q*q);
	}