#pragma once

#include "Body.h"

class Connection {
public:
	Connection(Body& p1, Body& p2); 

	void calc_force();
	void do_collision();

private:
	Body &p1, &p2;
};
