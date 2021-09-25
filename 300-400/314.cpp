
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using std::vector;

int main (int argc, char * const argv[])
{
    const int maxR = 250;

    /*
     Assume that the best shape has 8-way symmetry.

     smallestPerimeter[r][A] is the smallest length of a sequence of line
     segments from (r, 0) to (0, r) where the shape formed by the path and the
     X- and Y-axes has area A/2.
     */
    vector< vector<double> > smallestPerimeter(maxR + 1);
    smallestPerimeter[0].assign(1, 0.0);
    
    for(int r = 1; r <= maxR; ++r)
    {
        smallestPerimeter[r].resize(2 * r * r + 1, std::numeric_limits<double>::infinity() );
        smallestPerimeter[r][r * r] = hypot(r, r);
        for(int x = 1; x <= r; ++x)
        {
            for(int y = 1; y <= x; ++y)
            {
                int smaller_r = x - y;
                int max_smallerTwiceArea = 2 * smaller_r * smaller_r;
                int remainingTwiceArea = 2 * y * (r + x - y);
                double remainingPerimeter = 2 * hypot(r - x, y);
                for(int smallerTwiceArea = 0;
                    smallerTwiceArea <= max_smallerTwiceArea;
                    ++smallerTwiceArea)
                {
                    int twiceArea = remainingTwiceArea + smallerTwiceArea;
                    double perimeter = remainingPerimeter
                        + smallestPerimeter[smaller_r][smallerTwiceArea];
                    if(smallestPerimeter[r][twiceArea] > perimeter)
                        smallestPerimeter[r][twiceArea] = perimeter;
                }
            }
        }
        
        double bestRatio = 0.0;
        for(int twiceArea = 1; twiceArea <= 2 * r * r; ++twiceArea)
        {
            double ratio = 0.5 * twiceArea / smallestPerimeter[r][twiceArea];
            if(bestRatio < ratio)
                bestRatio = ratio;
        }
        
        std::printf("%3d: %.8f\n", r, bestRatio);
    }
    
    return 0;
}