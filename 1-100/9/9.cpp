#include "cmath"

int main(void)
{
	unsigned int a, b, c, ca, cb, cc;
	a = b = c = ca = cb = cc = 1;
	
	for(;a<1000;a++)
	{
		b = 1;
		for(;;b++)
		{
			if(a + b > 1000)
				break;
			c = 1;
			for(;c<1000;c++)
			{
				if(a + b + c == 1000)
				{
					ca = std::min(a,b);
					cc = std::max(std::max(a,b),c);
					cb = (a+b+c)-ca-cc;
					if(pow((double)ca,2) + pow((double)cb,2) == pow((double)cc,2))
						std::cout << "a:" << ca << " b:" << cb << " c:" << cc << " rep:" << ca*cb*cc << std::endl;
				}
			}
		}
	}
	return 0;
}
