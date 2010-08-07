int main()
{
	int x = 1;
	int y = 1;
	int size = 50;
	int res = 0;
	int i;
	for (i = 0; i < size; ++i)
	{
		res = x + y;
		y = x;
		x = res;	
	}
}