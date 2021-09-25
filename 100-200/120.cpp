int Result = 0;
	for(int a = 3;a <= 1000;++a)
		Result += 2*a*((a*a - 1)/(2*a));

	std::cout << Result << std::endl;