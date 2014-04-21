#pragma once
#include "SpatialSolver.h"
#include "ODESolver.h"
#include<fstream>
#include<string>

class Problem
{
public:
	Problem(SpatialSolver *solverS, ODESolver *solverT);
	~Problem(void);
	void SetInitialConditions();
	void GenerateSolution(string filename);
	void SetProblemParameters(SPACETYPE L,TIMETYPE T,int numSteps)
	{
		_domainLength=L;
		_finalTime = T;
		_odeSolver->SetTimeSteps(T/(TIMETYPE)numSteps);
	}
	std::vector<std::array<SPACETYPE,NSDIM> > Initialize();

private:
	SPACETYPE _domainLength; 
	TIMETYPE _finalTime; 

	SpatialSolver *_spaceSolver; // step through space
	ODESolver *_odeSolver; // step through time

};

