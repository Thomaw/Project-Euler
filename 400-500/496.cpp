for (int u=3;u*u<=2*N;u++) {
		for (int v=u/2+1;v<u&&u*v<=N;v++) if (__gcd(u,v)==1) {
			ret+=1ll*u*v*(1ll*(N/u/v)*(N/u/v+1)/2);
		}
	}