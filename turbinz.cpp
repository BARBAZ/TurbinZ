#include <maya/MIOStream.h>
#include <maya/MFnMesh.h>
#include <maya/MFStream.h>
#include <maya/MObject.h>
#include <maya/MSimple.h>
#include <maya/MStatus.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MIntArray.h>
#include <iostream>

DeclareSimpleCommand(spin, PLUGIN_COMPANY, "4.5");

void Log(const char* message)
{
	std::cout << message << std::endl;
}

MStatus spin::doIt(const MArgList&)
{
	std::ios::streampos file_size;
	char* File;
	std::fstream elu; // ifstream object instanced
	elu.open("C:/Users/Human/Documents/Projects/RBZ/Workspaces/Crt_am_Body.elu", std::ios::in | std::ios::binary | std::ios::ate);
	if (elu.is_open())
	{
		std::cout << "file opened" << std::endl;
		file_size = elu.tellg();
		File = new char[file_size];
		elu.seekg(0, std::ios::beg);
		elu.read(File, file_size);
		std::cout << "file stored in ram at address:" << std::endl;
		std::cout << *File << std::endl;

		std::cin.get();
	}
	else
	{
		std::cout << "Error opening file ! - killing process" << std::endl;
	}
	std::cin.get();

	std::cout << "Init Mesh construct" << std::endl;
	MStatus stat;
	stat.kSuccess;
	const double PA[8][4] = {	{-0.5, -0.5, 0.5,0},
								{ 0.5, -0.5, 0.5, 0},
								{ 0.5,  0.5, 0.5 ,0},
								{-0.5,  0.5, 0.5,0},
								{-0.5,  0.5, -0.5,0},
								{ 0.5,  0.5, -0.5,0},
								{ 0.5, -0.5, -0.5,0},
								{-0.5, -0.5, -0.5,0}};
	const MPointArray mpoints(PA, 8);
	int PF[] = {4,4,4,4,4,4};
	const MIntArray PolygonFaces(PF,6);
	int PC[] = {0,1,2,3,1,6,5,2,7,6,5,4,3,2,5,4,3,0,7,4,0,1,6,7}; 
	const MIntArray polygonConnects(PC,24);
	
	
	MFnMesh mesh;
	mesh.create(24, 6, mpoints, PolygonFaces, polygonConnects);
	Log("Mesh Construct");

	
	// Mesh Status definition

	return MS::kSuccess;
}