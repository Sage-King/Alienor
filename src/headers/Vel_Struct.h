#ifndef VEL_STRUCT_H_GUARD
#define VEL_STRUCT_H_GUARD
struct Vel
{
	Vel(double x, double y)
		:
		x(x),
		y(y)
	{}
	double x, y;
};
#endif