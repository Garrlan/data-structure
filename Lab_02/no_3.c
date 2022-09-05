#include "lab_1.h"
int f_hanshu(int a)
{
	//2^n
	return pow(2, a);
}

int g_hanshu(int b)
{
	//n!
	int Num_1=1;
	if (b==0)
	{
		Num_1=1;
	}
	else
	{
		for (int i = b; i > 0; i--)
			Num_1 = Num_1 * i;
	}
	return Num_1;
}

int main()
{
	int n = 2;
	int N; //0=< N <2
	//printf("g_hanshu = %d", g_hanshu(4));
	for (int i = 1; i >= 0; i--)
	{
		if (g_hanshu(i) >= f_hanshu(i))
			N = i;
	}
	printf("N = %d\n", N);
	return 0;
}