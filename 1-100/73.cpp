int main() {
    int n, i, j, s=0, a[10001], d[50];
        
    for (n=2; n<=10000; n++) {
        a[n]=ceil(n/2.)-(n/3)-1;
        for (i=0; i<50; i++) d[i]=0;
        i=2;
        j=0;
        while (n > i*i) {
              if (!(n%i)) {
                 d[j]=i;
                 j++;
              }
              i++;
        }
        if (!(n%i)) a[n]-=a[i];
        for (i=0; i < j; i++) a[n]-=(a[d[i]]+a[n/d[i]]);
        s+=a[n];
    }
    
    printf("%d", s);
    return 0;
}
