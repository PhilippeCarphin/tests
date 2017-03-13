#include <iostream>
#include <cmath>
int round_int(double x)
{
	return (x > 0) ? (x + 0.5) : (x - 0.5);
}
int main(void)
{
	float N = 18;

	float angle;

	/*
	 * This test shows why rounding a float scares me a bit. If a float is
	 * 126 + epsilon for a small epsilon < 0, then I'm scared that if I
	 * cast it to an int, I will get 125.
	 */
	double eps = -0.000000000000001;
	double _n_ = 126;

	double test_float = _n_ + eps;
	printf("n + eps = (%f + %f ) = %f\n", _n_, eps, test_float);
	
	int n = (int)test_float;
	printf("Integer casted : %d\n", n);


	while(1){
		std::cin >> angle;
		float new_angle = round(angle/N) * N;
		std::cout << "Angle : " << angle << std::endl
				<< "Angle/N : " << angle/N << std::endl
				<< "Round(angle/N) : " << round(angle/N) << std::endl
				<< "closest : " << new_angle << std::endl <<std::endl;
		std::cout << "Integer : " << round_int(new_angle - 0.1) << std::endl << std::endl;
	}
	return 0;
}
