#include "lab_1.h"
double f_hanshu(double a)
{
	//n^10
	double Anum = 1;
	for (int i = 0; i < 10; i++)
	{
		Anum = Anum * a;
	}
	return Anum;
}

double g_hanshu(double b)
{
	//2^n
	return pow(2, b);

}

int main()
{
	int n = 1;
	double N;//-1<N<1
	double up = 1, low = -1, mid = (up+low)/2;

	while (up - low > 1e-6)
	{
		if (g_hanshu(mid) > f_hanshu(mid))
			up = mid;
		else if (g_hanshu(mid) < f_hanshu(mid))
			low = mid;
		else break;
		mid = (up + low) / 2;

	}
	
	N = mid;
	printf("N= %f\n", N);
	return 0;  

}