#pragma once
#include<array>
#include"ODESolver.h"
#include"DataTypes.h"
class Problem;
using namespace std;

class LaxWendroffMethod:public ODESolver
{
public:
	LaxWendroffMethod(void);
	virtual ~LaxWendroffMethod(void);
	virtual std::vector<SPACETYPE> Solve(std::vector<SPACETYPE> InitialValue,TIMETYPE _finalTime);

	virtual std::vector<array<SPACETYPE,5> > Solve(std::vector<array<SPACETYPE,5> > InitialValue);

};

