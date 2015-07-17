#ifndef _MYWORLD_
#define _MYWORLD_

#include <vector>
#include <Eigen/Dense>

#define IX(i, j) ((i)+(getNumCells()+2)*(j))
#define SWAP(x0,x) {double *tmp=x0;x0=x;x=tmp;}

class MyWorld {
 public:
    MyWorld(int _numCells, double _timeStep, double _diffCoef, double _viscCoef);

    virtual ~MyWorld();

    int getNumCells() { return mNumCells;}
    double getDensity(int _index, int channel)
    {
        if (channel == 1)
            return mDensity1[_index];
        else if (channel == 2)
            return mDensity2[_index];
        return mDensity3[_index];
    }

    double getVelocityU(int _index) { return mU[_index]; }
    double getVelocityV(int _index) { return mV[_index]; }
    void setDensity(int _i, int _j, double _source, int channel)
    {
        if (channel == 1)
            mDensity1[IX(_i, _j)] += mTimeStep * _source;
        else if (channel == 2)
            mDensity2[IX(_i, _j)] += mTimeStep * _source;
        else if (channel == 3)
            mDensity3[IX(_i, _j)] += mTimeStep * _source;
    }
    void setU(int _i, int _j, double _force) { mU[IX(_i, _j)] += mTimeStep * _force; }
    void setV(int _i, int _j, double _force) { mV[IX(_i, _j)] += mTimeStep * _force; }
    
    void simulate();
    
 protected:
    void densityStep(double *_x, double *_x0);
    void velocityStep(double *_u, double *_v, double *_u0, double *_v0);
    void diffuseDensity(double *_x, double *_x0);
    void diffuseVelocity(double *_u, double *_v, double *_u0, double *_v0);
    void advectDensity(double *_d, double *_d0, double *_u, double *_v);
    void advectVelocity(double *_u, double *_v, double *_u0, double *_v0);
	void project(double *_u, double *_v, double *_u0, double *_v0);
    void externalForces();
	void linearSolve(double *_x, double *_x0, double _a, double _c);
	void linearSolve1(double *_x, double *_x0, double _a, double _c);
    void setBoundary(double *_x);
    void setVelocityBoundary(double *_u, double *_v);

    int mNumCells;
    double mTimeStep;
    double mDiffusionCoef;
    double mViscosityCoef;
    double *mU;
    double *mV;
    double *mPreU;
    double *mPreV;
    double *mDensity1;
    double *mDensity2;
    double *mDensity3;
    double *mPreDensity1;
    double *mPreDensity2;
    double *mPreDensity3;
	double p; // pressure
	double ro; // fluid density
};

#endif
