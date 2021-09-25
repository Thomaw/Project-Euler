#include<cstdio>

#define MAXN 36
#define MAXP 3*MAXN*(MAXN+1)+1

int points[MAXP][3], pnts=0;
int ar[MAXP][MAXP];

void addpoint(int x, int y, int type) {
	points[pnts][0] = x;
	points[pnts][1] = y;
	points[pnts][2] = type;
	pnts++;
}

int ab(int a) {return a<0?-a:a;}
int gcd(int a,int b) {return b==0?a:gcd(b,a%b);}

void normalize(int & x, int & y) {
	int d = gcd(ab(x),ab(y));
	if(x<0) {x=-x;y=-y;}
	if(x==0&&y<0) y=-y;
	x/=d;
	y/=d;
}

int ok(int tline, int tpoint) {
	if(tpoint==0) return 1;
	if(tpoint==1&&tline>2) return 1;
	if(tpoint==2&&tline%3==0) return 1;
	if(tpoint==3&&tline%3==1) return 1;
	if(tpoint==4&&tline%3==2) return 1;
	return 0;
}

int main()
{
	int i,j,k,n=MAXN;
	k = n+1;
	for(i=0;k>0;i+=6) {
		for(j=0;j<k;j++) {
			addpoint(i+j*12,i,0);
		}
		k--;
	}
	k = n;
	for(i=0;k>0;i+=6) {
		for(j=0;j<k;j++) {
			addpoint(6+i+j*12,i+2,1);
		}
		k--;
	}
	k = n-1;
	for(i=0;k>0;i+=6) {
		for(j=0;j<k;j++) {
			addpoint(12+i+j*12,i+4,1);
		}
		k--;
	}
	k = n;
	for(i=0;k>0;i+=6) {
		for(j=0;j<k;j++) {
			addpoint(6+i+j*12,i,2);
		}
		k--;
	}
	k = n;
	for(i=0;k>0;i+=6) {
		for(j=0;j<k;j++) {
			addpoint(3+i+j*12,i+3,3);
		}
		k--;
	}
	k = n;
	for(i=0;k>0;i+=6) {
		for(j=0;j<k;j++) {
			addpoint(9+i+j*12,i+3,4);
		}
		k--;
	}
	int x,y,t;
	for(i=0;i<pnts;i++) {
	//	printf("%d %d %d\n",points[i][0],points[i][1],points[i][2]);
		for(j=i+1;j<pnts;j++) {
			x = points[i][0]-points[j][0];
			y = points[i][1]-points[j][1];
			normalize(x,y);
			t=-1;
			if(x==1&&y==0) t=0;
			if(x==1&&y==1) t=1;
			if(x==1&&y==-1) t=2;
			if(x==0&&y==1) t=3;
			if(x==3&&y==-1) t=4;
			if(x==3&&y==1) t=5;
			if(t<0) continue;
			if(ok(t,points[i][2]) && ok(t,points[j][2])) {
				ar[i][j]=t+1;
				ar[j][i]=t+1;
			}
		}
	}
	x=0;
	for(i=0;i<pnts;i++) {
		for(j=i+1;j<pnts;j++) {
			if(ar[i][j]==0) continue;
			for(k=j+1;k<pnts;k++) {
				if(ar[i][k]==0||ar[j][k]==0) continue;
				if(ar[i][j]==ar[j][k]) continue;
				x++;
			}
		}
	}
	printf("%d\n",x);
	return 0;
}