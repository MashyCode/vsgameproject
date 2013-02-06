#if !defined(TGALOADER__INCLUDED_)
#define TGALOADER__INCLUDED_

#include <stdio.h>

//new stuff TGA loading
typedef struct {
	unsigned char ImgIdent;
	unsigned char ignored[ 1 ];
	unsigned char ImgType;
	unsigned char ignored2[ 9 ];
	unsigned char WidthLo;
	unsigned char WidthHi;
	unsigned char HeightLo;
	unsigned char HeightHi;
	unsigned char Bpp;
	unsigned char ignored3[ 1 ];
} _TGAHeader;

// Define Interface Data Types / Structures
//
typedef enum {
	txUnknown	= 0,	// images
	txBmp		= 1,
	txJpg		= 2,
	txPng		= 3,
	txTga		= 4,
	txGif		= 5,
	txIco		= 6,
	txEmf		= 7,
	txWmf		= 8,
	// add new ones at the end
} eglTexType;

typedef	struct
{
	GLuint		TextureID;									// Texture ID Used To Select A Texture
	eglTexType	TexType;									// Texture Format
	GLuint		Width;										// Image Width
	GLuint		Height;										// Image Height
	GLuint		Type;										// Image Type (GL_RGB, GL_RGBA)
	GLuint		Bpp;										// Image Color Depth In Bits Per Pixel
} glTexture;


int LoadTGAFromDisk(char *pszFileName, glTexture *pglTexture);
int GenerateTexture(glTexture *pglTexture, GLubyte *pImgData);
void CreateTextureWithAlphaFromTGA(char * fname, unsigned int textureID);
//end new stuff TGA loading

#endif