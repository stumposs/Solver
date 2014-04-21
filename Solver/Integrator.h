#pragma once
#include "DataTypes.h"
#include<vector>
#include<map>


class Integrator
{
public:
	Integrator(void);
	virtual ~Integrator(void);
    virtual SPACETYPE ApproximateIntegral(std::vector<CartPoint3> in) = 0;
	void SetInterval(short i,float j){_intervals[i] = j;}
	void SetIntegrand(FunctionPtr f){_integrand = f;}
	short GetMinNumDataPoints(){return _minNumDataPoints;}
protected:
	short _minNumDataPoints;
	// the length of the interval of integration of dimension i
	std::map<short,float> _intervals;
	// the integrand
	FunctionPtr _integrand;
};

class SimpsonRule:public Integrator
{
public:
	SimpsonRule(){_minNumDataPoints = 3;}
	virtual ~SimpsonRule(){}
	virtual SPACETYPE ApproximateIntegral(std::vector<CartPoint3> in);
};
class TrapezoidalRule:public Integrator
{
public:
	TrapezoidalRule(){_minNumDataPoints = 2;}
	virtual ~TrapezoidalRule(){}
	virtual SPACETYPE ApproximateIntegral(std::vector<CartPoint3> in);
	
};
