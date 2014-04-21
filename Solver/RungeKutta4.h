#pragma once
#include "ODESolver.h"
#include<vector>
using namespace std;
class RungeKutta4:public ODESolver
{
public:
	RungeKutta4(void);
	~RungeKutta4(void);
	virtual vector<SPACETYPE> Solve(vector<SPACETYPE> InitialValue, TIMETYPE timefinal);

	virtual std::vector<array<SPACETYPE,5> > Solve(std::vector<array<SPACETYPE,5> > InitialValue){return InitialValue;}

};

