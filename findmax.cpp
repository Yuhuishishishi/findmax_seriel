#include "Findmax.h"
#include <cstdio>
#include <queue>
#include <vector>

Interval::Interval(double a, double b) {
	start = a;
	end = b;
}

double Interval::getStart() {
	return start;
}

double Interval::getEnd() {
	return end;
}

std::vector<Interval> Interval::split() {
	// return two sub interval
	std::vector<Interval> sub_intvls;
	double mid = (start + end) / 2.0;
	Interval intvl1(start, mid);
	Interval intvl2(mid, end);
	sub_intvls.push_back(intvl1);
	sub_intvls.push_back(intvl2);
	return sub_intvls;
}

bool Interval::exist_max(double(*func)(double), double eps, double s, double current_max_val) {
	double possible_max_val = (func(start) + func(end) + s*(end - start)) / 2.0;
	if (possible_max_val < current_max_val + eps)
		return false;
	else
		return true;
}

void max_func(double(*func)(double), double a, double b, double eps, double s, double *max_x, double *max_val) {
	// initial max value
	double current_max_val, x_attain_max;
	if (func(a) > func(b)) {
		current_max_val = func(a);
		x_attain_max = a;
	}
	else {
		current_max_val = func(b);
		x_attain_max = b;
	}
	
	std::queue<Interval> task_queue;
	Interval intvl(a, b);
	task_queue.push(intvl); // add the first task

	Interval* task;
	double a_val, b_val;
	std::vector<Interval> sub_intvls;
	while (task_queue.size() > 0) {
		// pull one task
		task = &task_queue.front();
		// update the current max value
		a_val = func(task->getStart());
		b_val = func(task->getEnd());
		if (current_max_val >= a_val
			&& current_max_val >= b_val) {
			// do nothing
		}
		else if (a_val >= current_max_val
			&& a_val >= b_val) {
			current_max_val = a_val;
			x_attain_max = task->getStart();
		}
		else if (b_val >= current_max_val
			&& b_val >= a_val) {
			current_max_val = b_val;
			x_attain_max = task->getEnd();
		}

		// evaluate if exists max
		if (task->exist_max(func, eps, s, current_max_val)) {
			// split into two intervals
			sub_intvls = task->split();
			// add task to the queue
			task_queue.push(sub_intvls.at(0));
			task_queue.push(sub_intvls.at(1));
		}
		else {
			// do nothing
		}
		// dump the current task from the queue
		task_queue.pop();
		printf("current max val = %.4f, queue size = %d\n", current_max_val, task_queue.size());
	}

	*max_val = current_max_val;
	*max_x = x_attain_max;

}

