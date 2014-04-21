#pragma once
#include<vector>
#include<array>
#include<cmath>
using namespace std;

typedef float SPACETYPE;
#define NSDIM 5
#define NUMFACES 6
class CartPoint3;
typedef SPACETYPE (* FunctionPtr)(SPACETYPE);
//
// COORDINATE SYSTEMS
//
class Coordinate
{
public:
	Coordinate(){}
	~Coordinate(){}
	
};

class CartPoint:public Coordinate{
public:
	CartPoint(SPACETYPE x):_x(x){}
	CartPoint(){}
	~CartPoint(){}
	SPACETYPE X(){return _x;}
	void X(SPACETYPE x){_x = x;}
protected:
	SPACETYPE _x;
};

class CartPoint2:public CartPoint{
public:
	CartPoint2(SPACETYPE x, SPACETYPE y):CartPoint(x),_y(y){}
	~CartPoint2(){}
	SPACETYPE Y(){return _y;}
	void Y(SPACETYPE y){_y = y;}
	
protected:
	SPACETYPE _y;
};

class CartPoint3:public CartPoint2{
public:
	CartPoint3(SPACETYPE x, SPACETYPE y, SPACETYPE z):CartPoint2(x,y),_z(z){}
	CartPoint3():CartPoint2(0,0),_z(0){}
	~CartPoint3(){}
	SPACETYPE Z(){return _z;}
	void Z(SPACETYPE z){_z = z;}
	static SPACETYPE Dot(CartPoint3 a, CartPoint3 b)
	{
		return a.X()*b.X()+a.Y()*b.Y()+a.Z()*b.Z();
	}
	CartPoint3 operator*(const SPACETYPE a)
	{
		return CartPoint3(_x*a,_y*a,_z*a);
	}
	CartPoint3 operator+(CartPoint3 b)
	{
		return CartPoint3(_x+b.X(),_y+b.Y(),_z+b.Z());
	}
	void operator+=(CartPoint3 b)
	{
		_x+=b.X();
		_y+=b.Y();
		_z+=b.Z();
	}
	CartPoint3 operator- (const CartPoint3 &p)
	{
    return CartPoint3(_x-p._x, _y-p._y, _z-p._z);
	}
	CartPoint3& operator-()
	{
		_x = -_x;
		_y = -_y;
		_z = -_z;
		return *this;
	}	
	void Normalize()
	{
		SPACETYPE norm = sqrt(_x*_x+_y*_y+_z*_z);
		_x = _x/norm;
		_y = _y/norm;
		_z = _z/norm;
	}
private:
	SPACETYPE _z;
};

//
// FLUXES
//

/*
a fluxvector is an array of multivariate functions
or a vector function
*/
template<class T>
class FluxVector
{
public:
	FluxVector()
	{

	}
	
	virtual ~FluxVector(){}
	void SetFluxVector(array<T,NSDIM> f){_fluxVector = f;}

	T& operator[](size_t position)
	{
		return _fluxVector[position];
	}
	virtual void Compute(array<SPACETYPE,NSDIM> U) = 0;

protected:
	array<T,NSDIM> _fluxVector;
	unsigned _dimension;
	
};

template<class T>
class InviscidFluxVector:public FluxVector<T>
{
public:
	InviscidFluxVector(unsigned dimension){_dimension = dimension;}
	virtual ~InviscidFluxVector(){}
	virtual void Compute(array<SPACETYPE,NSDIM> U)
	{
		T rho = U[0];
		_fluxVector[0] = U[_dimension];
		for(int i=1;i<NSDIM-1;i++)
		{
			if(i==_dimension)
				_fluxVector[i] = U[i]*U[_dimension]/rho + _pressure;
			else
				_fluxVector[i] = U[i]*U[_dimension]/rho;
		}
		_fluxVector[4] = U[4]+_pressure*U[_dimension];
	}
private:
	T _pressure;
};

/*
FluxMatrix manages the momentum fluxes in each of the three 
dimensions.
TODO: generalize so that we don't limit ourselves to just inviscous flux
*/
template<class T>
class FluxMatrix
{
public:
	FluxMatrix()
	{
		for(unsigned i=0;i<3;i++)
			_fluxColumns[i] = new InviscidFluxVector<T>(i);
	}

	~FluxMatrix()
	{
		for(unsigned i=0;i<3;i++)
		{
			delete _fluxColumns[i];
			_fluxColumns[i] = NULL;
		}
	}
	array<T,NSDIM> DotWithCartPoint3(CartPoint3 vec)
	{
		array<T, NSDIM> result;
	
		for(int i=0;i<NSDIM;i++)
			result[i] = (*_fluxColumns[0])[i]*vec.X()+(*_fluxColumns[1])[i]*vec.Y()+(*_fluxColumns[2])[i]*vec.Z();
		
		return result;
	}
	void ComputeFluxes(array<SPACETYPE,NSDIM> average)
	{
		for(int i=0;i<3;i++)
			_fluxColumns[i]->Compute(average);
	}
	const InviscidFluxVector<T>& operator[](size_t position)
	{
		if(position>=NSDIM)
			return NULL;
		else
			return &_fluxColumns[position];
	}
	FluxMatrix& operator+=(FluxMatrix m)
	{
		for(int i=0;i<NSDIM;i++)
			for(int j=0;j<3;j++)
			{
				(*_fluxColumns[j])[i] += (*m._fluxColumns[j])[i];	
			}
		return *this;
	}
	FluxMatrix& operator*=(T scalar)
	{
		for(int i=0;i<NSDIM;i++)
			for(int j=0;j<3;j++)
			{
				(*_fluxColumns[j])[i] *= scalar;	
			}
		return *this;
	}
	FluxMatrix& operator*(const T scalar)
	{
		for(int i=0;i<NSDIM;i++)
			for(int j=0;j<3;j++)
				(*_fluxColumns[j])[i]*=scalar;
		return *this;
	}
	FluxMatrix& operator=(const FluxMatrix m)
	{
		for(int i=0;i<NSDIM;i++)
			for(int j=0;j<3;j++)
				(*_fluxColumns[j])[i]=(*m._fluxColumns[j])[i];
		return *this;
	}

	void Zeros()
	{
		for(int i=0;i<NSDIM;i++)
			for(int j=0;j<3;j++)
				(*_fluxColumns[j])[i]=0;
	}
protected:

	array<InviscidFluxVector<T>*,3> _fluxColumns;

};






