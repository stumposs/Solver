#include "Mesh.h"

FVMMesh::FVMMesh(SPACETYPE L, int N)
{
	_spatialStepsize = L/(SPACETYPE)N;
	_numSteps = N;
	
}
FVMMesh::~FVMMesh()
{
	Clear();
}
void FVMMesh::Clear()
{
	map<string,Face*>::iterator it = _faces.end();
	it--;
	while(!_faces.empty())
	{
		// set all pointers to null
		it->second->UnSet();

		Face *temp = it->second;
		string key = it->first;
		it--;
		_faces.erase(key);
		delete temp;
	}
}
void FVMMesh::GenerateGrid()
{
	// CREATE GRIDPOINTS
	for(unsigned k=0;k<_numSteps;k++)
	{
		for(unsigned i=0;i<_numSteps;i++)
		{
			for(unsigned j=0;j<_numSteps;j++)
			{
				_gridPoints.push_back(CartPoint3(((SPACETYPE)j)*_spatialStepsize,((SPACETYPE)i)*_spatialStepsize,((SPACETYPE)k)*_spatialStepsize));
			}
		}
	}
}
void FVMMesh::ConstructVolumes(map<string,Volume*> &volumes)
{
	int N = _numSteps;
// CREATE FACES AND ASSIGN FACES TO VOLUMES - CELL CENTERED
	int k=0;
	int N2 = N*N;

	for(int l=0;l<N-1;l++) // y
	{
		for(int i=0;i<N-1;i++) // x
		{
			for(int j=0;j<N-1;j++) // z
			{

				int bbl = l*N2+i*N+j;
				int bbr = l*N2+(i+1)*N+j;

				int bfl = l*N2+i*N+(j+1);
				int bfr = l*N2+(i+1)*N+(j+1);

				int tbl = (l+1)*N2+i*N+j;
				int tbr = (l+1)*N2+(i+1)*N+j;

				int tfl = (l+1)*N2+i*N+(j+1);
				int tfr = (l+1)*N2+(i+1)*N+(j+1);

				CartPoint3 centroid;
				
				centroid.X(((_gridPoints[bbl]+_gridPoints[bbr])*0.5).X());
				centroid.Y(((_gridPoints[bbl]+_gridPoints[tbl])*0.5).Y());
				centroid.Z(((_gridPoints[bbl]+_gridPoints[bfl])*0.5).Y());

				vector<Face*> faces(NUMFACES);
				/* create faces -> TODO change this so it isn't O(N^4 logN)
				-> for details see comments above 'AddFace' funciton
				*/
				// ordering: back, right,front,left,bottom, top


				int backList[] = {bbr,bbl,tbl,tbr,(int)Face::Back};
				vector<int> backV(backList,backList + sizeof(backList) / sizeof(int));
				faces[0] = AddFace(backV);

				int frontList[] = {bfl, bfr, tfr, tfl,(int)Face::Front};
				vector<int> frontV(frontList,frontList + sizeof(frontList) / sizeof(int));
				faces[1] = AddFace(frontV);

				int rightList[] = {bfr, bbr, tbr,tfr,(int)Face::Right};
				vector<int> rightV(rightList,rightList + sizeof(rightList) / sizeof(int));
				faces[2] = AddFace(rightV);

				int leftList[] = {bbl,bfl,tfl, tbl,(int)Face::Left};
				vector<int> leftV(leftList,leftList + sizeof(leftList) / sizeof(int));
				faces[3] = AddFace(leftV);

				int bottomList[] = {bfr, bfl, bbl, bbr,(int)Face::Bottom};
				vector<int> bottomV(bottomList,bottomList + sizeof(bottomList) / sizeof(int));
				faces[4] = AddFace(bottomV);

				int topList[] = {tbr, tbl,tfl,tfr,(int)Face::Top};
				vector<int> topV(topList,topList + sizeof(topList) / sizeof(int));
				faces[5] = AddFace(topV);

				char key[20];
				// boundary volumes added first - there should be (N-1)*(N-1)*6
				if(i==0||j==0||l==0)
				{
					sprintf(key,"0%d%d%d.",i,l,j);
				}
				else
				{
					sprintf(key,"1%d%d%d.",i,l,j);
				}
				char *keystr = strtok(key,".");
				Volume *cv = new Volume(faces,keystr);
				cv->SetCentroid(centroid);
				volumes[keystr] = cv;

			}
		}
	}
	
}
/* TODO: change your algorithm. you are performing |Volume|*NUMFACES sort
operations (N log N each). If the number of points per dimension is 20, 
then N = 19^3*6 = 41154 and log2(41154) =~ 15.33 for a total of 630,839.17
operations! and thats just for the sorting!
*/
string FVMMesh::GetKeyFromList(vector<int> vertices)
{
	// declare empty string
	char key[100];
	// sort list
	_sorter.Sort(&vertices);
	
	// concatenate string versions of integers in list and add a terminating character
	for(int i=0;i<vertices.size();i++)
	{
		char k[10];
		sprintf(k,"%d.",vertices[i]);
		char *s = strtok(k,".");
		strncpy(key,s,strlen(s));
	}
	// delimit using terminating character to snip off extra zeros
	strncpy(key,".",1);
	char *str = strtok(key,".");
	

	return str;
}

Face* FVMMesh::AddFace(vector<int> vertices)
{
	
	string key = GetKeyFromList(vertices);
	map<string,Face*>::iterator faceIt = _faces.find(key);
	if(faceIt==_faces.end())
	{
		// TODO: GENERALIZE!!

		Face *f = new Face(vertices,key);
		_faces[key] = f;
		// TODO: This is a cheat. faces currently are all uniform squares
		// but if generalized to allow for other geometry or unstructured grids,
		// the way we set this must change
		SPACETYPE area = pow(_spatialStepsize,2);
		f->SetArea(area);
		return f;
	}
	else
	{
		return faceIt->second;
	}
}