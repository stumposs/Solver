#include "LaxWendroffMethod.h"
#include "Problem.h"

LaxWendroffMethod::LaxWendroffMethod(void)
{
}


LaxWendroffMethod::~LaxWendroffMethod(void)
{
}
/*
* returns solution vector for every cell at a single timestep
* Since each solution is a 5 dimensional array, this is a vector
* of arrays, or (N-1)*(N-1)*(N-1) by 5, since there are (N-1)*(N-1)*(N-1) volumes
*/
std::vector<SPACETYPE> LaxWendroffMethod::Solve(std::vector<SPACETYPE> InitialValue,TIMETYPE _finalTime)
{
	vector<array<SPACETYPE,NSDIM> > prev;
	vector<array<SPACETYPE,NSDIM> > next;
	for(int t=0;t<_timeSteps;t++)
	{
		// solve for fluxes
		
	}
/*	SPACETYPE k = _temporalStepsize/(_spatialSolver->GetSpatialStepsize());
	array<SPACETYPE,NSDIM> prev_fluxfor,prev_fluxhere, next_fluxhere, next_fluxback;
	SPACETYPE predictor;
	/*
	for(int i=0;i<_timeSteps;i++)
	{
		for(int j=0;j<NSDIM;j++)
		{
			predictor = prev[i][j] - k*(prev_fluxfor[j] - prev_fluxhere[j]);

			next[i][j] = 0.5*(prev[i][j] + predictor - k*(next_fluxhere[j] - next_fluxback[j]);
		}
	}
	*/
	return InitialValue;
}
std::vector<array<SPACETYPE,5> > LaxWendroffMethod::Solve(std::vector<array<SPACETYPE,5> > prev)
{
	vector<array<SPACETYPE,NSDIM> > next;
	vector<array<SPACETYPE,NSDIM> > U;
	for(int t=0;t<_timeSteps;t++)
	{
		//solve for fluxes- next[i] is the solution matrix of the i-th cell of the 
		// RHS of dU/dt = -SUM(k=1...6)Integral(F . n[k])dS[k]
		
		next = _spatialSolver->GetSpatialSolution(prev);
		/* flux predictors:
		FluxMatrix flux_term;
		float h = _temporalStepsize/_spatialStepsize;
		for(int dim=0;dim<3;dim++)
		{
		 InviscidFluxVector<SPACETYPE> temp = 0.5*(fluxColumns[dim]->Compute(i+1,j,k) + fluxColumns[dim]->Compute(i,j,k) - dissipationFactor);
		 
		}
		predictor = prev[i] - h*(flux_pred[dim] - _volumes[i
		*/
	}
	return U;
}
