// Biggest numbers that matter are 21 digits, so digitsum cannot be more than 189
#define MAXDS 200
#define MAXCARRY (137)

struct state
{
    unsigned long pop[2*MAXDS+1][MAXCARRY];
};

long digitsum(long x)
{
    long ds=0;

    while (x)
    {
        ds+=(x%10);
        x/=10;
    }
    return ds;
}

long count_hits(const state& c)
{
    long sum=0;
    
    for (int carry=0;carry<MAXCARRY;carry++)
    {
        long cds=digitsum(carry);
        long needed_ds=MAXDS+cds;
        
        sum+=c.pop[needed_ds][carry];
    }
    return sum;
}
            

int main(int argc, char** argv)
{
    state cur;

    memset(&cur,0,sizeof(cur));
    // Set the '0 digit' number
    cur.pop[0+MAXDS][0]=1;

    long x=atol(argv[1]);
    
    for (long pass=0;pass<x;pass++)
    {
        state next;
        memset(&next,0,sizeof(next));
        for (int prepend=0;prepend<10;prepend++)
        {
            long prep137=137*prepend;
            for (int ds=0;ds<2*MAXDS+1;ds++)
            {
                for (int carry=0;carry<MAXCARRY;carry++)
                {
                    long p=cur.pop[ds][carry];
                    if (!p)
                        continue;
                    
                    long new137=carry+prep137;
                    long d137=new137%10;
                    long c137=new137/10;

                    next.pop[ds+prepend-d137][c137]+=p;
                }
            }
        }
        cur=next;
    }

    long answer=count_hits(cur);
    printf("Answer is %ld\n",answer);
}