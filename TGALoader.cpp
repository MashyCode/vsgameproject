#include "stdafx.h"
#include "TGALoader.h"

void
CreateTextureWithAlphaFromTGA(char * fname, unsigned int textureID)
{
	glTexture mytexture;
	mytexture.TextureID=textureID;
	LoadTGAFromDisk(fname,&mytexture);
}

// Load a TGA file
// new part
int LoadTGAFromDisk(char *pszFileName, glTexture *pglTexture)
{
	FILE		*fTGA;													// File pointer to texture file
	_TGAHeader	header;
	GLubyte		*pImgData;
	GLint		glMaxTexDim;											// Holds Maximum Texture Size

	fTGA = fopen(pszFileName, "rb");									// Open file for reading

	if(fTGA == NULL)													// If it didn't open....
	{
		return FALSE;													// Exit function
	}

	if(fread(&header, sizeof(_TGAHeader), 1, fTGA) == 0)				// Attempt to read 12 byte header from file
	{
		if(fTGA != NULL)												// Check to seeiffile is still open
		{
			fclose(fTGA);												// If it is, close it
		}
		return FALSE;													// Exit function
	}

	// Precalc some values from the header
	const unsigned int imageType		= header.ImgType;
	const unsigned int imageWidth		= header.WidthLo  + header.WidthHi  * 256;
	const unsigned int imageHeight		= header.HeightLo + header.HeightHi * 256;
	const unsigned int imageBytesPerPel	= header.Bpp / 8;
	const unsigned int imageSize		= imageWidth * imageHeight * imageBytesPerPel;

	// load up our texture information
	pglTexture->Width  = imageWidth;
	pglTexture->Height = imageHeight;
	pglTexture->Bpp	   = header.Bpp;

	if(pglTexture->Bpp == 24)											// If the BPP of the image is 24...
	{
		pglTexture->Type = GL_RGB;										// Set Image type to GL_RGB
	}
	else																// Else if its 32 BPP
	{
		pglTexture->Type = GL_RGBA;										// Set image type to GL_RGBA
	}

	// Validate header info
	if( ( imageType != 2 && imageType != 10 ) ||
	    ( imageWidth == 0 ) || ( imageHeight == 0 ) ||
		( imageBytesPerPel != 3 && imageBytesPerPel != 4 ) )
	{
		// invalid header, bomb out
		fclose( fTGA );
		return (FALSE);
	}

	// Allocate the memory for the image size
	pImgData = (GLubyte *)malloc(imageSize);

	if(pImgData == NULL)												// If no space was allocated
	{
		fclose(fTGA);													// Close the file
		return FALSE;													// Return failed
	}

	// Skip image ident field
	if( header.ImgIdent > 0 )
	{
		fseek(fTGA, header.ImgIdent, SEEK_CUR);
	}

	// un-compresses image ?
	if (imageType == 2)
	{
		if(fread(pImgData, 1, imageSize, fTGA) != imageSize)			// Attempt to read image data
		{
			if(pImgData != NULL)										// If imagedata has data in it
			{
				free(pImgData);											// Delete data from memory
			}

			fclose(fTGA);												// Close file
			return FALSE;												// Return failed
		}

		// Byte Swapping Optimized By Steve Thomas
		for(GLuint cswap = 0; cswap < imageSize; cswap += imageBytesPerPel)
		{
			pImgData[cswap] ^= pImgData[cswap+2] ^=
			pImgData[cswap] ^= pImgData[cswap+2];
		}
	}
	else
	{
		// compressed image
		GLuint pixelcount	= imageHeight * imageWidth;					// Nuber of pixels in the image
		GLuint currentpixel	= 0;										// Current pixel being read
		GLuint currentbyte	= 0;										// Current byte
		GLubyte * colorbuffer = (GLubyte *)malloc(imageBytesPerPel);	// Storage for 1 pixel

		do
		{
			GLubyte chunkheader = 0;										// Storage for "chunk" header

			if(fread(&chunkheader, sizeof(GLubyte), 1, fTGA) == 0)			// Read in the 1 byte header
			{
				if(fTGA != NULL)											// If file is open
				{
					fclose(fTGA);											// Close file
				}
				if(pImgData != NULL)										// If there is stored image data
				{
					free(pImgData);											// Delete image data
				}
				return FALSE;												// Return failed
			}

			if(chunkheader < 128)											// If the ehader is < 128, it means the that is the number of RAW color packets minus 1
			{																// that follow the header
				chunkheader++;												// add 1 to get number of following color values
				for(short counter = 0; counter < chunkheader; counter++)	// Read RAW color values
				{
					if(fread(colorbuffer, 1, imageBytesPerPel, fTGA) != imageBytesPerPel) // Try to read 1 pixel
					{
						if(fTGA != NULL)									// See if file is open
						{
							fclose(fTGA);									// If so, close file
						}

						if(colorbuffer != NULL)							// See if colorbuffer has data in it
						{
							free(colorbuffer);							// If so, delete it
						}

						if(pImgData != NULL)							// See if there is stored Image data
						{
							free(pImgData);								// If so, delete it too
						}

						return FALSE;									// Return failed
					}
																		// write to memory
					pImgData[currentbyte		] = colorbuffer[2];		// Flip R and B vcolor values around in the process
					pImgData[currentbyte + 1	] = colorbuffer[1];
					pImgData[currentbyte + 2	] = colorbuffer[0];

					if (imageBytesPerPel == 4)							// if its a 32 bpp image
					{
						pImgData[currentbyte + 3] = colorbuffer[3];		// copy the 4th byte
					}

					currentbyte += imageBytesPerPel;					// Increase thecurrent byte by the number of bytes per pixel
					currentpixel++;										// Increase current pixel by 1

					if(currentpixel > pixelcount)						// Make sure we havent read too many pixels
					{
						if(fTGA != NULL)								// If there is a file open
						{
							fclose(fTGA);								// Close file
						}

						if(colorbuffer != NULL)							// If there is data in colorbuffer
						{
							free(colorbuffer);							// Delete it
						}

						if(pImgData != NULL)							// If there is Image data
						{
							free(pImgData);								// delete it
						}

						return FALSE;									// Return failed
					}
				}
			}
			else														// chunkheader > 128 RLE data, next color reapeated chunkheader - 127 times
			{
				chunkheader -= 127;										// Subtract 127 to get rid of the ID bit
				if(fread(colorbuffer, 1, imageBytesPerPel, fTGA) != imageBytesPerPel)	// Attempt to read following color values
				{
					if(fTGA != NULL)									// If thereis a file open
					{
						fclose(fTGA);									// Close it
					}

					if(colorbuffer != NULL)								// If there is data in the colorbuffer
					{
						free(colorbuffer);								// delete it
					}

					if(pImgData != NULL)								// If there is image data
					{
						free(pImgData);									// delete it
					}

					return FALSE;										// return failed
				}

				for(short counter = 0; counter < chunkheader; counter++)// copy the color into the image data as many times as dictated
				{														// by the header
					pImgData[currentbyte		] = colorbuffer[2];		// switch R and B bytes areound while copying
					pImgData[currentbyte + 1	] = colorbuffer[1];
					pImgData[currentbyte   + 2	] = colorbuffer[0];

					if(imageBytesPerPel == 4)							// If TGA images is 32 bpp
					{
						pImgData[currentbyte + 3] = colorbuffer[3];		// Copy 4th byte
					}

					currentbyte += imageBytesPerPel;					// Increase current byte by the number of bytes per pixel
					currentpixel++;										// Increase pixel count by 1

					if(currentpixel > pixelcount)						// Make sure we havent written too many pixels
					{
						if(fTGA != NULL)								// If there is a file open
						{
							fclose(fTGA);								// Close file
						}

						if(colorbuffer != NULL)							// If there is data in colorbuffer
						{
							free(colorbuffer);							// Delete it
						}

						if(pImgData != NULL)							// If there is Image data
						{
							free(pImgData);								// delete it
						}

						return FALSE;									// Return failed
					}
				} // for(counter)
			} // if(chunkheader)
		}
		while(currentpixel < pixelcount);								// Loop while there are still pixels left
	} // if (imageType == 2)

	fclose (fTGA);														// Close the TGA file

	/*
	** Scale Image to be a power of 2
	*/

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);					// Get Maximum Texture Size Supported

	//int lWidthPixels  = imageWidth;
	//int lHeightPixels = imageHeight;

	//// Resize Image To Closest Power Of Two
	//if (lWidthPixels <= glMaxTexDim) // Is Image Width Less Than Or Equal To Cards Limit
	//	lWidthPixels = 1 << (int)floor((log((double)lWidthPixels)/log(2.0f)) + 0.5f);
	//else  // Otherwise  Set Width To "Max Power Of Two" That The Card Can Handle
	//	lWidthPixels = glMaxTexDim;

	//if (lHeightPixels <= glMaxTexDim) // Is Image Height Greater Than Cards Limit
	//	lHeightPixels = 1 << (int)floor((log((double)lHeightPixels)/log(2.0f)) + 0.5f);
	//else  // Otherwise  Set Height To "Max Power Of Two" That The Card Can Handle
	//	lHeightPixels = glMaxTexDim;

	//// if low quality textures then make them halve the size which saved 4 times the texture space
	//if ((m_fHighQualityTextures == FALSE) && (lWidthPixels > 64))
	//{
	//	lWidthPixels /= 2;
	//	lHeightPixels /= 2;
	//}

	//// if the size needs to change, the rescale the raw image data
	//if ( (lWidthPixels  != (int)imageWidth)	&&
	//	 (lHeightPixels != (int)imageHeight) )
	//{
	//	// allocated the some memory for the new texture
	//	GLubyte	*pNewImgData = (GLubyte *)malloc(lWidthPixels * lHeightPixels * imageBytesPerPel);

	//	GLenum format;
	//	if (imageBytesPerPel == 4)
	//	{
	//		format = GL_RGBA;
	//	}
	//	else
	//	{
	//		format = GL_RGB;
	//	}

	//	gluScaleImage(format, imageWidth, imageHeight, GL_UNSIGNED_BYTE, pImgData,
	//						  lWidthPixels, lHeightPixels, GL_UNSIGNED_BYTE, pNewImgData);

	//	// free the original image data
	//	free(pImgData);

	//	// old becomes new..
	//	pImgData = pNewImgData;

	//	// update our texture structure
	//	pglTexture->Width  = lWidthPixels;
	//	pglTexture->Height = lHeightPixels;
	//}

	// Typical Texture Generation Using Data From The TGA loader
	glGenTextures(1, &pglTexture->TextureID);						// Create The Texture

	// generate the texture using the filtering model selected
	(void)GenerateTexture(pglTexture, (BYTE *)pImgData);

	// free the memory allocated
	free(pImgData);

	return TRUE;														// All went well, continue on
}

// Set the Texture parameters to match the type of filtering we want.
//
int GenerateTexture(glTexture *pglTexture, GLubyte *pImgData)
{
	int result = 0;

	int	components;
	// set the bytes per pixel
	if (pglTexture->Type == GL_RGBA)
	{
		components = 4;
	}
	else
	{
		components = 3;
	}

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, pglTexture->TextureID);				// Bind To The Texture ID

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

	BOOL	Mipping;


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1 );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	Mipping = FALSE;
							


	// crank out the texture

	glTexImage2D(GL_TEXTURE_2D,
					 0,
					 components,
					 pglTexture->Width,
					 pglTexture->Height,
					 0,
					 pglTexture->Type,
					 GL_UNSIGNED_BYTE,
					 pImgData);



	return 0;
}

//end TGA addition