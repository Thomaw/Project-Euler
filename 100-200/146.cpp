  int64 lim = 150000000;
  int64 lim10 = lim / 10;
  primes ps(lim);

  int64 count = 0;
  int64 tot = 0;
  vector<bool> is_composite(lim10+1);

  vector<int64> r;
  r.push_back(1);
  r.push_back(3);
  r.push_back(7);
  r.push_back(9);
  r.push_back(13);
  r.push_back(27);

  for(int64 k = 1; k < lim10; k++)
  {
    int64 n = k * 10;
    if(k % 1000 == 0)
    {
     // cout << "processing: " << k << "/" << lim10 << endl;
    }
    if(is_composite[k]) continue;
    if(n % 3 == 0 || n % 7 == 0 || n % 13 == 0)
    {
      is_composite[k] = true;
      continue;
    }
    int64 p = ps.get_prime_divisor_a(100*k*k,r);
    if(p != 0)
    {
      // cout << "marking (" << k << "," << p << ")" << endl;
      for(int64 kp = k; kp < lim10; kp += p)
      {
        is_composite[kp] = true;
      }
    }
  }

  vector<int64> r19;
  r19.push_back(19);
  vector<int64> r21;
  r21.push_back(21);
  for(int64 k = 1; k < lim10; k++)
  {
    int64 n = 10*k;
    if(k % 10000 == 0)
    {
      cout << n << '\t' << count << endl;
    }
    if(! is_composite[k])
    {
      if((ps.get_prime_divisor_a(n*n,r19) != 0) && (ps.get_prime_divisor_a(n*n,r21) != 0))
      {
        count++;
        cout << "found " << n << endl;
        tot += n;
      }
    }
  }

  cout << count << endl;
  cout << tot << endl;