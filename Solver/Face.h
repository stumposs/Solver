
#pragma once
#include<set>
#include<string>
#include<array>
#include "DataTypes.h"
#include "Volume.h"
using namespace std;


// for now, we constrain the face polygon to be a square
// Thus it will always consist of 4 indices into the array of 
// gridpoints.
// note that this class should be generalized to allow for faces 
// of any geometry


class Face{
public:
	// back and front are orthogonal to z axis (3)
	// right and left are orthogonal to x axis (1)
	// top and bottom are orthogonal to y axis (2)
	enum eName{Back = -3,Front = 3,Right = 1,Left = -1,Bottom = -2,Top = 2};

	Face(vector<int> vertices, string key);
	Face(){_id="";}
	~Face();
	void UnSet();
	string GetID(){return _id;}
	int GetName(){return _name;}
	void SetArea(SPACETYPE a){_area = a;}
	SPACETYPE GetArea(){return _area;}
	bool operator<(const Face &f)const
	{
		if(_id<f._id)
			return true;
		else
			return false;
	}
	CartPoint3 GetNormal(){return _normal;}

	void ComputeFlux(array<SPACETYPE,NSDIM> average);
	void AddVolume(Volume *v,int faceName);

	struct VolumeIO{
		Volume* _volume;
		eName _direction;
		FluxMatrix<SPACETYPE> _flux;
	};

private:
	// TODO: change this to a vector of indices instead of hardcoding a static number of 4 vertices
	vector<int> _vertices;

	string _id;
	int _name;

	SPACETYPE _area;
	CartPoint3 _normal;
	CartPoint3 _negNormal;
	FluxMatrix<SPACETYPE> _flux;

	array<VolumeIO,2> _volumes;
	int _vCounter;

};
