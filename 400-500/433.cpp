    typedef unsigned long long u64;
    u64 r = 0;
    for ( u64 i = 1; i <= N; ++i ) {
        static unsigned ss[1000];
        u64 c = 1, a = 2*i, b = i;
        do {
            if ( a <= N ) {
                do {
                    r += c;
                    ss[c++] = b;
                    u64 t = b;
                    b = a;
                    a += t;
                } while ( a <= N);
            }
            a = b;
            b = ss[--c];
            a += b;
        } while ( c );
    }
    ret = 2*r+N*(N+1)/2;