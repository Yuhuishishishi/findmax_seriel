#include <vector>

class Interval {
	double start, end;
public:
	Interval(double, double);
	std::vector<Interval> split(); // return a ptr to 2 intervals
	bool exist_max(double(*func)(double), double eps, double s, double current_max_val);
	double getStart();
	double getEnd();
};

void max_func(double(*func)(double), double a, double b, double eps, double s, double* max_x, double* max_val);
