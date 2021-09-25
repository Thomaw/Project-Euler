{
  G=10^6;L=10^12;N=10^18;m=101^4; s=0;

  t=vector(100); for(p=1,100, t[p]=Mod(p+1,m)^N-2*Mod(p,m)^N+Mod(p-1,m)^N);

  for(l=1,L\G,  
    p=factor(l)[,2]~;lp=length(p);
    tt=(L\l-G+1);for(i=1,lp,tt*=t[p[i]]);
    s+=tt;
  );

  print(s);
}