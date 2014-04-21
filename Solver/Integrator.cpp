#include "Integrator.h"


Integrator::Integrator(void)
{
}


Integrator::~Integrator(void)
{
}
//
// Simpson
//
SPACETYPE SimpsonRule::ApproximateIntegral(std::vector<CartPoint3> in)
{
	if(in.size()<_minNumDataPoints)
		return 0;
	else
	{

	}
}
//
// Trapezoidal
//
SPACETYPE TrapezoidalRule::ApproximateIntegral(std::vector<CartPoint3> in)
{
	/*
	float n = in.size();


	if(n<_minNumDataPoints)
		return 0;

	// this is a cheat!
	float h = _intervals[0]/n;
	float inv = 1/h;
	double total=0;
	for(int i=0;i<2;i++)
		total+=(0.5*inv*_integrand(in[i]));
	for(int j=n-2;j<n;j++)
		total+=(0.5*inv*_integrand(in[j]));

	for(int i=2;i<n-2;i++)
	{
		total+=(inv*_integrand(in[i]));
	}
	*/
	return 0;
}