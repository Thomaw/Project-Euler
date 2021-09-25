double calcR(int a,int b,int c) {
  double p = (a+b+c)/2.;
  double s = sqrt(p*(p-a)*(p-b)*(p-c));
  double r = s/p;
  double gb = hypot(r, p-b);
  double ga = hypot(r, p-a);
  double ra = (ga-r)*r/(ga+r);
  double rb = (gb-r)*r/(gb+r);
  double raa = (ga-r-2*ra)*r/(ga+r);
  rb = max(rb,raa);
  return r*r+ra*ra+rb*rb;
}