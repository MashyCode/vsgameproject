#pragma once
#include "3dObject.h"
#include <gl.h> //for RGB image
#include <glaux.h>
#include <vector>

struct vec3{
float x;
float y;
float z;
};

class CTerrain : public C3dObject
{
public:
	CTerrain(float x_, float y_,float z_, float w_, float h_,float d_, int textureID_);
	~CTerrain(void);

	void Render();
	float GetHeightAtPoint(float x_, float z_);
	

private:
	int m_iMapVerticesx;
	int m_iMapVerticesz;
	float m_fTerrainStepWidth;
	float m_fTerrainStepHeight;
	bool m_bClampToTerrain;
	
	AUX_RGBImageRec *m_pImage_RGB; //used to load image file for height data
	
	void LoadBitmapFile(char *filename);
	void UnloadBitmapFile();
	void CreateDisplayList();
	vec3 * ComputeCrossProduct(int x1,int z1,int x2,int z2,int x3,int z3);

	bool bDisplayListCreated;
	GLuint m_iDisplayList;

	void ComputeVertexHeights();
	void ComputeNormals();
	std::vector <float> m_vHeights;
	std::vector <vec3 *> m_vNormals;

	void NormalizeVector(vec3 *v);
	void AddVector(vec3 *a, vec3 *b) ;

	void DumpVertexData();
	

};
