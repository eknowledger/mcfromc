int collatz3()
{
	int curr = 3;
	int currMod;
	while (curr > 1)
	{
		currMod = curr%2;
		if (currMod > 0)
			curr = 3*curr + 1;
		else
			curr /= 2;
	}

}