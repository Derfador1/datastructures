
#include <stdio.h>

double sixpack(double x)
{
	return x > 0 ? x : -x;
}

double cube_root(double x)
{
	double low = 0;
	double high = x;

	double guess = (high - low)/3.0;

	while(sixpack(x - guess*guess*guess) > 0.001) {
		if(x > guess*guess*guess) {
			low = guess;
		} else {
			high = guess;
		}
		guess = low + (high - low)/3.0;
		printf("Guessing %lf\n", guess);
	}
	
	return guess;
}

int main(void)
{
	printf("cube root of %lf is %lf\n", 27.0, cube_root(27.0));
	printf("cube root of %lf is %lf\n", 54.0, cube_root(54.0));
}
