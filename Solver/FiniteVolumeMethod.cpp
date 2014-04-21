#include "FiniteVolumeMethod.h"



FiniteVolumeMethod::FiniteVolumeMethod(SPACETYPE L, int N):SpatialSolver(L,N)
{
	_mesh = new FVMMesh(L,N);
	_mesh->GenerateGrid();
	_mesh->ConstructVolumes(_volumes);
}

FiniteVolumeMethod::~FiniteVolumeMethod(void)
{
	Clear();
	delete _mesh;
}
void FiniteVolumeMethod::Clear()
{
	_mesh->Clear();
	map<string,Volume*>::iterator it = _volumes.begin();

	// set all pointers to null
	while(!_volumes.empty())
	{

		Volume *temp = it->second;
		string key = it->first;
		it--;
		_volumes.erase(key);
		delete temp;
	}
	

}
/*



INPUT: average of solution vector U[i] at every cell
there will be _volumes.size() 5-tuples
*/
std::vector<array<SPACETYPE,NSDIM> > FiniteVolumeMethod::GetSpatialSolution(std::vector<array<SPACETYPE,NSDIM> > averages)
{

	SolveForFluxes(averages);
	return _solution;
}
/*
The input into the function is the average U for each gridpoint. Therefore, it is a vector of 
M 5-tuples, where M = the number of gridpoints
*/
void FiniteVolumeMethod::SolveForFluxes(vector<array<SPACETYPE,NSDIM> > averages)
{
	map<string,Volume*>::iterator it = _volumes.begin();
	// boundary
	int j = 0;
	while(it!=_volumes.end()&&strncmp("1",it->first.c_str(),1)!=0)
	{
	
		it++;
	}
	// interior
	while(it!=_volumes.end())
	{
		// update the conservative variables at the center of each cv
		it->second->Update(averages[j]);
		it++;
	}
	
}
