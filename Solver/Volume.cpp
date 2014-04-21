#include "Face.h"
#include "Volume.h"
#include "FiniteVolumeMethod.h"

//TODO change to std::array type
Volume::Volume(vector<Face*> faces,string id):_id(id)
{
	for(int i=0;i<faces.size();i++)
	{
	  _faces[faces[i]->GetID()] = faces[i];
	}
	_pressure = 1;
}


Volume::~Volume(void)
{
}
/*
The volume knows its faces so it is responsible 
for calculating the flux at the face using the 
average over the cell

NUMERICAL INTEGRATION OF FLUXES HANDLED HERE

current method is midpoint rule
*/
void Volume::Update(array<SPACETYPE,NSDIM> average)
{
	_average = average;
	ComputeNetFlux();
}

void Volume::ComputeNetFlux()
{
	map<string,Face*>::iterator it = _faces.begin();
	for(;it!=_faces.end();it++)
		it->second->ComputeFlux(_average);
}