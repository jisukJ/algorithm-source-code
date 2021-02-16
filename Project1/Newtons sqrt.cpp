//x= x-f(x)/f'(x)
double mysqrt(int n)
{
	double ret = n;
	for (int i = 0; i < 16; ++i)
	{
		if (ret < 1.0)
			break;
		ret = ret - (ret*ret - n) / (2 * ret);
	}
	return ret;
}