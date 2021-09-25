int k,l,v,w,L[101],a,b;
long long int TOTAAL=0;
double start,kk,ll,vv,k1,l1,cc;


int ggd(int a,int b){
int a1,b1,r1;
if(a==1||b==1) return 1;
a1=a;b1=b;r1=a1%b1;
while(r1){
    a1=b1;b1=r1;r1=a1%b1;
}
return b1;
}

int main(){
start=clock();
for(k=2;k<=25;k++){
    for(l=1;l<=k-1;l++){
        if((k-l)%3){
            if(ggd(k,l)==1){
                v=(k-l)*(k-l)-3*l*l;vv=(double)v;
                w=abs(v);
                if(w<=100){
                    L[w]++;
                    if(w<=10){
                        if(L[w]==1){
                            a=100/w;
                            kk=(double)k;ll=(double)l;cc=pow(kk,2.0)+kk*ll+pow(ll,2.0);
                            while(cc<1e100){
                                if(cc<1e98)b=100;
                                else b=(int)(1e100/cc);
                                TOTAAL+=min(a,b);
                                k1=kk;l1=ll;
                                ll=k1+l1;
                                kk=(k1*ll-vv)/l1;
                                cc=pow(kk,2.0)+kk*ll+pow(ll,2.0);
                            }
                        }
                    }
                    else{
                        if(L[w]<=2){
                            a=100/w;
                            kk=(double)k;ll=(double)l;cc=pow(kk,2.0)+kk*ll+pow(ll,2.0);
                            while(cc<1e100){
                                if(cc<1e98)b=100;
                                else b=(int)(1e100/cc);
                                TOTAAL+=min(a,b);
                                k1=kk;l1=ll;
                                ll=k1+l1;
                                kk=(k1*ll-vv)/l1;
                                cc=pow(kk,2.0)+kk*ll+pow(ll,2.0);
                            }
                        }
                    }
                }
            }
        }
    }
}

cout<<"TOTAAL is "<<TOTAAL<<"\n";
cout<<clock()-start;