void main(void)
{
    long m, n, x, y, z, w, sub, total;
    
    start_time = clock();

    total = 0;
    for (m = 1; m <= 43; m++) {
	for (n = 1; n <= 47; n++) {
	    sub = 0;
	    for (x = 1; x <= m; x++) {
		for (y = 1; y <= n; y++) {
		    sub += (m-x+1) * (n-y+1);
		}
	    }
	    total += sub;
	    sub = 0;
	    for (x = 1; x <= 2*m; x++) {
		for (y = 1; y <= 2*n; y++) {
		    z = (x+y-1) / 2;
		    w = x+y-1 - z;
		    if (z>m) continue;
		    if (w>m) continue;
		    if (z>n) continue;
		    if (w>n) continue;
		    if (((x | y) & 1) == 0) {
			sub += ((m-z) * (n-z) + (m-w) * (n-w));
		    }
		    else {
			sub += ((m-z) * (n-w) + (m-w) * (n-z));
		    }
		}
	    }
	    total += sub;
	}
    }

    printf("total = %ld\n", total);
    end_time = clock();
    printf("Elapsed Time: %lu\n", (end_time - start_time));
}
