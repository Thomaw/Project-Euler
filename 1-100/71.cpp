#include <Core/Core.h>
using namespace Upp;

CONSOLE_APP_MAIN
{
	int xmax = 0, xmaxd = 2;
	for ( int d = 2; d <= 1000000; ++d ) {
		int x = 3*d/7;
		if ( (d%7) == 0 ) --x;
		if ( x*xmaxd > xmax*d ) {
			xmax = x, xmaxd = d;
		}
	}
	Cout().Put( AsString(xmax) + "/" + AsString(xmaxd) + "\r\n" );
}
