/*
 * ccd.h
 *
 *  Created on: Sep 10, 2010
 *      Author: msuchard
 */

#ifndef CCD_H_
#define CCD_H_

#include <time.h>

#ifdef _WIN32
#include <stddef.h>
#include <io.h>
#include <stdlib.h>
#include <winsock.h>
#include <stdio.h>
#else
#include <sys/time.h>
#endif

#include "Types.h"

namespace bsccs {

    class CyclicCoordinateDescent; // forward declaration
    class ModelData;
    class AbstractModelSpecifics;

struct CCDArguments {

	// Needed for fitting
	std::string inFileName;
	std::string outFileName;
	std::string fileFormat;
	std::string outDirectoryName;
	std::vector<std::string> outputFormat;
	bool useGPU;
	bool useBetterGPU;
	int deviceNumber;
	double tolerance;
	double hyperprior;
	bool computeMLE;
	bool fitMLEAtMode;
	bool reportASE;
	bool useNormalPrior;
	bool hyperPriorSet;
	int maxIterations;
	std::string convergenceTypeString;
	int convergenceType;
	long seed;

	// Needed for cross-validation
	bool doCrossValidation;
	bool useAutoSearchCV;
	double lowerLimit;
	double upperLimit;
	int fold;
	int foldToCompute;
	int gridSteps;
	std::string cvFileName;
	bool doFitAtOptimal;

	//Needed for Hierarchy
	bool useHierarchy;
	std::string hierarchyFileName; //tshaddox
	double classHierarchyVariance; //tshaddox

	// Needed for boot-strapping
	bool doBootstrap;
	bool reportRawEstimates;
	int replicates;
	std::string bsFileName;
	bool doPartial;

	// Needed for model specification
	int modelType;
	std::string modelName;

	NoiseLevels noiseLevel;

	ProfileVector profileCI;
	ProfileVector flatPrior;
};


class CcdInterface {

public:

    CcdInterface();
    virtual ~CcdInterface();

void parseCommandLine(
		int argc,
		char* argv[],
		CCDArguments &arguments);

void parseCommandLine(
		std::vector<std::string>& argcpp,
		CCDArguments& arguments);

double initializeModel(
		ModelData** modelData,
		CyclicCoordinateDescent** ccd,
		AbstractModelSpecifics** model,
		CCDArguments &arguments);

double fitModel(
		CyclicCoordinateDescent *ccd,
		CCDArguments &arguments);
		
double runFitMLEAtMode(
        CyclicCoordinateDescent* ccd, 
        CCDArguments &arguments);

double predictModel(
		CyclicCoordinateDescent *ccd,
		ModelData *modelData,
		CCDArguments &arguments);

double profileModel(
		CyclicCoordinateDescent *ccd,
		ModelData *modelData,
		CCDArguments &arguments,
		ProfileInformationMap &profileMap);

double runCrossValidation(
		CyclicCoordinateDescent *ccd,
		ModelData *modelData,
		CCDArguments &arguments);

// double runBoostrap(
// 		CyclicCoordinateDescent *ccd,
// 		ModelData *modelData,
// 		CCDArguments &arguments);
		
double runBoostrap(
		CyclicCoordinateDescent *ccd,
		ModelData *modelData,
		CCDArguments &arguments,
		std::vector<double>& savedBeta);		

double calculateSeconds(
		const struct timeval &time1,
		const struct timeval &time2);

void setDefaultArguments(
		CCDArguments &arguments);

void setZeroBetaAsFixed(
		CyclicCoordinateDescent *ccd);
		
double logModel(CyclicCoordinateDescent *ccd, ModelData *modelData,
		CCDArguments& arguments,
		ProfileInformationMap &profileMap,
		bool withProfileBounds);
		
double diagnoseModel(
        CyclicCoordinateDescent *ccd, 
        ModelData *modelData,
		CCDArguments& arguments,
		double loadTime,
		double updateTime);
		
protected:
    std::string getPathAndFileName(CCDArguments& arguments, std::string stem);
    bool includesOption(const std::string& line, const std::string& option);
		

}; // class CcdInterface

class CmdLineCcdInterface : public CcdInterface {


}; // class CmdLineCcdInterface

class RCcdInterface: public CcdInterface {


}; // class RCcdInterface

} // namespace

#endif /* CCD_H_ */
