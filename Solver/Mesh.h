#include<map>
#include<vector>
#include"DataTypes.h"
#include "Volume.h"
#include "Face.h"
#include "QuickSort.h"
using namespace std;

class Mesh
{
public:
	Mesh(){}
	virtual ~Mesh(){}

	CartPoint3 GetVertex(int i){return _gridPoints[i];}

protected:
	vector<CartPoint3> _gridPoints;
};

class FVMMesh: public Mesh
{
public:
	FVMMesh(SPACETYPE L, int N);
	virtual ~FVMMesh();
	void Clear();
	void GenerateGrid();
	void ConstructVolumes(map<string,Volume*> &volumes);
	string GetKeyFromList(vector<int> vertices);
	Face* AddFace(vector<int> vertices);

private:
	map<string,Face*> _faces;
	SPACETYPE _spatialStepsize;
	CQuickSort<int> _sorter;
	int _numSteps;
};