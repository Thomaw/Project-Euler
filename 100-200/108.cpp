uint64_t max=0;
for (uint64_t n=4;;n++)
{
    uint64_t s=1;
    for (uint64_t b=n+1;b<n*2;b++)
        if ((b-n)/gcd(b-n,b*n)==1) s++;
    if (s>max)
    {
        max=s;
        std::cout<<n<<":"<<s<<std::endl;
    }
}