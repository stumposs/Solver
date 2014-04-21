#pragma once
#include <vector>
#include "DataTypes.h"
#include "Mesh.h"
class SpatialSolver
{
public:
	SpatialSolver(void){}
	SpatialSolver(SPACETYPE L, int N);
	virtual ~SpatialSolver(void);

	virtual std::vector<array<SPACETYPE,NSDIM> > GetSpatialSolution(std::vector<array<SPACETYPE,NSDIM> > p) = 0;
	virtual std::vector<SPACETYPE> GetSpatialSolution(std::vector<SPACETYPE> p) = 0;

protected:
	//Mesh *_mesh;
	SPACETYPE _spatialStepsize;
};

