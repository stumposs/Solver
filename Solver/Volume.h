#pragma once
#include"DataTypes.h"
#include<string>
#include<cmath>
#include<map>
using namespace std;
/*! A volume is the region of space where  the conservative 
 * variables are solved. It is defined by its enclosing faces
 *
 * this class is responsible for handling all direct flux calls
 *
 * Note that this should be generalized to allow for volumes 
 * of any geometry. currently they must be cubes.
*/
class FiniteVolumeMethod;
class Face;

class Volume
{
public:
	Volume(vector<Face*> faces,string id);
	~Volume(void);
	void Update(array<SPACETYPE,NSDIM> average);

	void SetPressure(SPACETYPE p){_pressure = p;}

	void ComputeNetFlux();

	void SetCentroid(CartPoint3 c){_centroid = c;}
	string GetID(){return _id;}
	void UnSet()
	{
		map<string,Face*>::iterator it=_faces.begin();
		while(it!=_faces.end())
		{
			it->second = NULL;
			it++;
		}
	}
private:
	// the key to the face ranges from -n to n for a volume with 2n faces
	//the key indicates the placement of the face with respect to the cube
	map<string,Face*> _faces;

	array<SPACETYPE,NSDIM> _average;

	FluxMatrix<SPACETYPE> _netFlux;
	SPACETYPE _pressure;
	SPACETYPE _volume;
	CartPoint3 _centroid;
	string _id;
};

