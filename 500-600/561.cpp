
const LL m=904961,n=1000000000000ll;
LL res=n/4+(n+1)/4*m;
for(LL p=8;p<=n;p*=2){
  res+=n/p;
}
for(LL p=8;p<=n+1;p*=2){
  res+=(n+1)/p*m;
}
cout<<res;