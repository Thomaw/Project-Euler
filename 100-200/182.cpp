typedef unsigned long long Integer;

static const Integer p = 1009;
static const Integer q = 3643;

static const Integer n = p * q;
static const Integer phi = (p - 1) * (q - 1);

//	get divisors of phi
vector<Integer> divisors;
vector<Integer> orders;
for( Integer d = 1; d <= phi; d++ ){
	if( phi % d == 0 ){
		divisors.push_back(d);
		orders.push_back(0);
	};
};

//	get orders
for( Integer a = 0; a < n; a++ ){
	for( unsigned int i = 0; i < divisors.size(); i++ ){
		if( powmod<Integer>(a, divisors[i], n) == 1 ){
			orders[i]++;
			break;
		};
	};
};

//	get minimal number of unconcealed messages and sum of associated e numbers
Integer minc = n;
Integer sum = 0;
for( Integer e = 2; e < phi; e++ ){
	if( gcd(e, phi) != 1 ){
		continue;
	};
	Integer c = 0;
	for( unsigned int i = 0; i < divisors.size(); i++ ){
		if( e % divisors[i] == 1 ){
			c += orders[i];
		};
	};
	if( minc == c ){
		sum += e;
	};
	if( minc > c ){
		minc = c;
		sum = e;
	};
};

//	print sum
cout << sum << endl;