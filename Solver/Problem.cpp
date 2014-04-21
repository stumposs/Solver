#include "Problem.h"


Problem::Problem(SpatialSolver *solverS, ODESolver *solverT):_spaceSolver(solverS),_odeSolver(solverT)
{

}


Problem::~Problem(void)
{
}

void Problem::SetInitialConditions()
{

}
std::vector<std::array<SPACETYPE,NSDIM> > Problem::Initialize()
{
	std::vector<std::array<SPACETYPE,NSDIM> > ic;

	// apply initial conditions

	return ic;
}
void Problem::GenerateSolution(string filename)
{
	ofstream results(filename);
	_odeSolver->SetSpatialSolver(_spaceSolver);
	// utilize initial conditions to start process
	std::vector<std::array<SPACETYPE,NSDIM> > ic = Initialize();
	_odeSolver->Solve(ic);
	results.close();
}