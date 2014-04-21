#pragma once
#include "SpatialSolver.h"
typedef float TIMETYPE;


class ODESolver
{
public:
	ODESolver(void){_timeSteps = 128;_spatialSolver = NULL;}
	virtual ~ODESolver(void){}

	virtual std::vector<SPACETYPE> Solve(std::vector<SPACETYPE> InitialValue,TIMETYPE _finalTime)=0;

	virtual std::vector<array<SPACETYPE,5> > Solve(std::vector<array<SPACETYPE,5> > InitialValue)=0;
	int GetTimeSteps(){return _timeSteps;}
	TIMETYPE GetTemporalStepsize(){return _temporalStepsize;}

	void SetSpatialSolver(SpatialSolver *ss){_spatialSolver = ss;}
	void SetTimeSteps(int ts){_timeSteps = ts;}
protected:
	int _timeSteps;
	TIMETYPE _temporalStepsize;
	SpatialSolver *_spatialSolver;
	
};

