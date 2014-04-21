#pragma once
#include "SpatialSolver.h"
#include "Integrator.h"
#include "DataTypes.h"
#include<cmath>
#include "Volume.h"
#include<map>
#include<string>
#include<set>
#include<cstdio>
using namespace std;


class FiniteVolumeMethod:public SpatialSolver
{
public:
	FiniteVolumeMethod(SPACETYPE L, int N);
	~FiniteVolumeMethod(void);
	virtual std::vector<array<SPACETYPE,NSDIM> > FiniteVolumeMethod::GetSpatialSolution(std::vector<array<SPACETYPE,NSDIM> > Averages);

	void Clear();
	void SolveForFluxes(vector<array<SPACETYPE,NSDIM> > averages);
	virtual std::vector<SPACETYPE> GetSpatialSolution(std::vector<SPACETYPE> p){return p;}
private:
	FiniteVolumeMethod(){}

	map<string,Volume*> _volumes;
	std::vector<array<SPACETYPE,NSDIM> > _solution;
	FVMMesh* _mesh;

};

