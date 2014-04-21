#include "RungeKutta4.h"
#include "FiniteVolumeMethod.h"
#include "LaxWendroffMethod.h"
#include "Integrator.h"
#include "Problem.h"


int main(int argc, char *argv[])
{

	FiniteVolumeMethod *fvm = new FiniteVolumeMethod(1,10);
	LaxWendroffMethod *lwm = new LaxWendroffMethod();
	// then solve ode (temporal solver)
	// for a fvm,
	Problem navierStokes(fvm,lwm);
	navierStokes.GenerateSolution("flow.txt");
	
	delete fvm;
	delete lwm;
}