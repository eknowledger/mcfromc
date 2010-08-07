int main()
{
	int x = 3;
	int y = -5;
	int temp = 0;

	if (x < 10)
	{
		x = 2*y + 3*(x-2);
		x++;
	}
	else
	{
		y %= 2*x + 3*(y-2);
		y++;		
	}
	for (temp = 1; x < y; ++x)
		temp += temp;
}