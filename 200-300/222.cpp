
#include <cstdio>
#include <cmath>
#include <vector>


double preCost = 1680*1000;

double R = 50*1000;

double cost(double r1, double r2)
{
    double r = r1 + r2;
    //return R*std::sqrt(2/R*r - 1) - r;
    return std::sqrt(r*r - (2*R - r)*(2*R - r)) - r;
}

double vecCost(std::vector<unsigned> const &v)
{
    double ret = preCost;
    for(unsigned i = 0; i < v.size()-1; ++i)
        ret += cost((v[i]+30)*1000, (v[i+1]+30)*1000);

    return ret;  //unsigned(ret + 0.5);
}

int main()
{
    std::vector<unsigned> v;
    //unsigned order[21] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    //unsigned order[21] = {0, 20, 1, 19, 2, 18, 3, 17, 4, 16, 5, 15, 6, 14, 7, 13, 8, 12, 9, 11, 10};
    unsigned order[21] = {20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    for(unsigned r = 0; r < 21; ++r)
        v.push_back(order[r]);
    std::printf("%lf\n", vecCost(v));
    //std::printf("%lf\n", cost(30000, 30000));
    /*unsigned sum = 0;
    for(unsigned r = 30; r <= 50; ++r)
        sum += r*2;
    std::printf("%u\n", sum);*/
}