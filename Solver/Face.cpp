#include "Face.h"

Face::Face(vector<int> vertices,string key)
{
	// a face must be at least three vertices
	if(vertices.size()<3)
		return;

	_vertices = vertices;
	_name = vertices[vertices.size()-1];
	_id = key;
	for(int i=0;i<_volumes.size();i++)
		_volumes[i]._volume = NULL;
		// TODO: the normal of the face should not be hard-coded
		// construct the normal using the coordinates of the face
	switch(_name)
	{
	case -1:
		_normal = CartPoint3(-1,0,0);
		break;
	case 1:
		_normal = CartPoint3(1,0,0);
		break;
	case -2:
		_normal = CartPoint3(0,-1,0);
		break;
	case 2:
		_normal = CartPoint3(0,1,0);
		break;
	case -3:
		_normal = CartPoint3(0,0,-1);
		break;
	case 3:
		_normal = CartPoint3(0,0,1);
		break;
	default:
		_normal = CartPoint3(0,0,0);
		break;
	}
	_vCounter = 0;
	_negNormal = _normal;
	-_negNormal;
}
Face::~Face()
{
	
}
void Face::UnSet()
{
	for(int i=0;i<_volumes.size();i++)
	{
		_volumes[i]._volume->UnSet();
		_volumes[i]._volume = NULL;
	}
}
void Face::AddVolume(Volume *v,int faceName)
{
	VolumeIO vio;
	vio._volume = v;
	for(int i=0;i<_volumes.size();i++)
	{
		if(_volumes[i]._volume==NULL&&i==0)
		{
			vio._direction = (eName)_name;
			vio._flux.Zeros();
			return;
		}
		else if(_volumes[i]._volume==NULL&&i!=0)
		{
			vio._direction = (eName)(-(int)_name);
			vio._flux.Zeros();
			return;
		}

	}
}
/*
calculate the flux at the average. if the flux has already been computed at the 
average for the neighbor cv, compute the average
*/
void Face::ComputeFlux(array<SPACETYPE,NSDIM> average)
{
	_volumes[_vCounter]._flux.ComputeFluxes(average);
	if(_volumes[_vCounter]._direction<0)
	{
		_volumes[_vCounter]._flux.DotWithCartPoint3(_negNormal);
	}
	else
		_volumes[_vCounter]._flux.DotWithCartPoint3(_normal);
	_volumes[_vCounter]._flux*=_area;

	_vCounter++;

	if(_vCounter>=_volumes.size())
	{
		// get average
		_flux = _volumes[0]._flux;
		_flux +=_volumes[1]._flux;
		// take the average
		_flux*0.5;
		//set back to zero
		_vCounter = 0;
	}

}

