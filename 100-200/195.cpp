int euler195()
{
    const double nn = 1053779.0;

    int cnt = 0;

    double C = (1.0/2.0)*sqrt((double)3);
    for (int n = 1; ; n++)
    {
        bool br = false;
        for (int m = n+1; ; m++)
        {
            if (gcd(m,n) != 1) continue;
            if ((m-n) % 3 == 0) continue;
            double r = C*m*n;
            if (r <= nn)
            {
                cnt += int(nn/r);
                br = true;
            }
            else
                break;
        }
        if (br == false)
            break;
    }

    C = (1/6.0)*sqrt((double)3);
    for (int n = 1; ; n++)
    {
        bool br = false;
        for (int m = n+1; ; m++)
        {
            if (gcd(m,n) != 1) continue;
            if ((m-n) % 3 == 0) continue;
            double r = C*(m+2*n)*(m-n);
            if (r <= nn)
            {
                cnt += int(nn/r);
                br = true;
            }
            else
                break;
        }
        if (br == false)
            break;
    }

    cout << cnt << endl;
    return cnt;
}