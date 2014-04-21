#include "SpatialSolver.h"


SpatialSolver::SpatialSolver(SPACETYPE L, int N)
{
	SPACETYPE h = (SPACETYPE)(L/(float)N);
	_spatialStepsize = h;
}


SpatialSolver::~SpatialSolver(void)
{
}
