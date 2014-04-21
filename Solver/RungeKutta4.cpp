#include "RungeKutta4.h"


RungeKutta4::RungeKutta4(void)
{
}


RungeKutta4::~RungeKutta4(void)
{
}

vector<SPACETYPE> RungeKutta4::Solve(vector<SPACETYPE> initialValue, TIMETYPE finalTime)
{
	// N is the number of spatial gridpoints
	int N = initialValue.size();

	if (_spatialSolver==NULL)
		return initialValue;

	//mSolution.push_back(initialValue);

 // vector<vector<complex<double> > > mSolution(_timeSteps);
  double time=0;

  double h = finalTime/(_timeSteps-1);

  vector<SPACETYPE> K1(N), K2(N), K3(N), K4(N), Temp(N), Unew(N);

  for(int i=1; i<_timeSteps; i++)
  {
    time+=h;


//K1

    K1 = _spatialSolver->GetSpatialSolution(initialValue);
    for(int j=0;j<N;j++)
    {
       K1[j] = h*K1[j];
    }

//K2
    for(int j=0;j<N;j++)
    {
       Temp[j] = initialValue[j] + K1[j]/2.0;
    }
    Temp = _spatialSolver->GetSpatialSolution(Temp);
    for(int j=0;j<N;j++)
    {
      K2[j] = h*Temp[j];
    }

//K3
    for(int j=0;j<N;j++)
    {
       Temp[j] = initialValue[j] + K2[j]/2.0;
    }
    Temp = _spatialSolver->GetSpatialSolution(Temp);
    for(int j=0;j<N;j++)
    {
      K3[j] = h*Temp[j];
    }

//K4
    for(int j=0;j<N;j++)
    {
      Temp[j] = initialValue[j] + K3[j];
    }
    Temp = _spatialSolver->GetSpatialSolution(Temp);
    for(int j=0;j<N;j++)
    {
      K4[j] = h*Temp[j];
    }

//New
    for(int j=0;j<N;j++)
    {
      Unew[j] = initialValue[j]+(1/6.0)*(K1[j]+2.0*(K2[j]+K3[j])+K4[j]);
    }
    //mSolution.push_back(Unew);
    initialValue = Unew;
  }
  return initialValue;

}
