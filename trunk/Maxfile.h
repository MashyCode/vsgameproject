#pragma once
#include <vector>
#include "3dObject.h"

using namespace std;



struct point3d{
	float x;
	float y;
	float z;
};

struct point2d{
	float x;
	float y;
};

struct vertexdata{
	int pointindex[3];
	int normalindex[3];
	int texcoordindex[3];
};

class CMaxFile : public C3dObject
{
public:
	CMaxFile(char * filepath_,float x_,float y_, float z_,float scale_, int textureID);
	~CMaxFile(void);
	void Render();
	void Update(double dt){;}

private:

	vector <point3d> vertlist; //point3d vertlist[485];//vertex list
	vector <point3d> normlist; //point3d normlist[507];//normals list
	vector <point2d> texcoordlist; //point2d texcoordlist[1608];//tex coord list
	vector <vertexdata> trilist; //int trilist[943];//triangle list  943/6

	int m_iNumVerts;
	int m_iNumNormals;
	int m_iNumTexcoords;
	int m_iNumTriangleData;

};
