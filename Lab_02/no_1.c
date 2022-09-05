#include "lab_1.h"
double f_hanshu(double a) 
{
	return a;
}

double g_hanshu(double b) 
{
	//log只能后接正数
	return b * log(b);
}

double t_hanshu(double c)
{
	//c*log(c)/c = log(c)
	return log(c);
}

int main() 
{
	int n = 1;
	double N;//0 < N < 1

	//要使 n>N, log(N) >= 1
	printf("在N的有效范围内，g函数恒小于f函数！\n");
	return 0;

}