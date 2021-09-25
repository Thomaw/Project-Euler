#include<stdio.h>
#include<math.h>
#include<queue>
#define LIM 5000000
struct qdata
{
	double r;
	double sx, sy;
	int l, b;
	friend bool operator < (qdata d1, qdata d2)
	{
		return d1.r<d2.r;
	}
};
using namespace std;
priority_queue<qdata> q;
int ans;
double f_get(double sx, double sy)
{
	return (sqrt((sx+sy)*(sx+sy)-4.0*(sx*sy-1.0))-(sx+sy))/2.0;
}
int main()
{
	int i;
	int cnt=0;
	qdata cur, nxt;
	nxt.sx=1.0; nxt.sy=0.0; nxt.l=0; nxt.b=0; nxt.r=f_get(nxt.sx, nxt.sy);
	if(nxt.b<=3 && nxt.l<=3) cnt++;
	q.push(nxt);
	for(i=1;cnt && q.size()<LIM;i++)
	{
		cur=q.top(); q.pop();
		if(cur.b<=3 && cur.l<=3) cnt--;
		if(cur.b==3 && cur.l==3) ans=i;
		nxt.sx=cur.sx+cur.r; nxt.sy=cur.sy; nxt.l=cur.l+1; nxt.b=cur.b; nxt.r=f_get(nxt.sx, nxt.sy);
		if(nxt.b<=3 && nxt.l<=3) cnt++;
		q.push(nxt);
		nxt.sx=cur.sx; nxt.sy=cur.sy+cur.r; nxt.l=cur.l; nxt.b=cur.b+1; nxt.r=f_get(nxt.sx, nxt.sy);
		if(nxt.b<=3 && nxt.l<=3) cnt++;
		q.push(nxt);
	}
	if(cnt) printf("OVERFLOW!\n");
	else printf("%d\n", ans);
	return 0;
}