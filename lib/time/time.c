#include "time/time.h"

static double _time = 0;

double get_time() {
	return _time;
}

void update_time(double delta) {
	_time += delta;
}

void reset_time() {
	_time = 0;
}