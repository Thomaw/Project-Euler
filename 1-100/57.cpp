#include <conio.h>
#include &lt;iostream&gt;
#include &lt;vector&gt;
using namespace std

vector&lt;char&gt; add(vector&lt;char&gt; a, vector&lt;char&gt; b)
{
	vector&lt;char&gt; c;
	vector&lt;char&gt;::iterator ia,ib,i,ie;
	ia = a.begin();
	ib = b.begin();
	char o = 0,s;
	while(ia!=a.end() && ib!=b.end())
	{
		s = (*ia)+(*ib)+o;
		o = s/10;
		s %= 10;
		ia++;
		ib++;
		c.push_back(s);
	};
	if(o && ia==a.end() && ib==b.end())
	{
		c.push_back(o);
	} else {
		if(ia==a.end()) {
			i=ib;
			ie=b.end();
		}
		else 
		{
			i=ia;
			ie=a.end();
		};
		while(i!=ie)
		{
			s = o + (*i);
			o = s/10;
			s %= 10;
			i++;
			c.push_back(s);
		};
		if(o) c.push_back(o);
	};
	return c;
}

void printv(vector&lt;char&gt; c)
{
	for(int i=c.size()-1; i&gt;=0; --i)
		cout &lt;&lt; int(c[i]);
}


int _tmain(int argc, _TCHAR* argv[])
{

	vector&lt;char&gt; n,d,c;
	unsigned i=0,tot=0;
	n.push_back(3);
	d.push_back(2);
	do{
		c = add(d,d);
		c = add(c,n);
		d = add(d,n);
		n = c;
		if(n.size()!=d.size()) tot++;
		i++;
	}while(i&lt;1000);
	cout &lt;&lt; tot;
	getch();
	return 0;
}
