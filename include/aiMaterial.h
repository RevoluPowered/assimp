/*
---------------------------------------------------------------------------
Open Asset Import Library (ASSIMP)
---------------------------------------------------------------------------

Copyright (c) 2006-2008, ASSIMP Development Team

All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the following 
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the ASSIMP team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the ASSIMP Development Team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

/** @file Defines the material system of the library
 *
 */

#ifndef AI_MATERIAL_H_INC
#define AI_MATERIAL_H_INC

#include "aiTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------
/** Defines type identifiers for use within the material system.
*
*/
// ---------------------------------------------------------------------------
enum aiPropertyTypeInfo
{
	/** Array of single-precision floats
	*/
	aiPTI_Float = 0x1,

	/** aiString data structure
	*/
	aiPTI_String = 0x3,

	/** Array of Integers
	*/
	aiPTI_Integer = 0x4,

	/** Simple binary buffer
	*/
	aiPTI_Buffer = 0x5,
};

// ---------------------------------------------------------------------------
/** Defines texture operations like add, mul ...
*
*/
// ---------------------------------------------------------------------------
enum aiTextureOp
{
	/** T = T1 * T2
	 */
	aiTextureOp_Multiply = 0x0,

	/** T = T1 + T2
	 */
	aiTextureOp_Add = 0x1,

	/** T = T1 - T2
	 */
	aiTextureOp_Subtract = 0x2,

	/** T = T1 / T2
	 */
	aiTextureOp_Divide = 0x3,

	/** T = (T1 + T2) - (T1 * T2)
	 */
	aiTextureOp_SmoothAdd = 0x4,

	/** T = T1 + (T2-0.5)
	 */
	aiTextureOp_SignedAdd = 0x5
};

// ---------------------------------------------------------------------------
/** Defines all shading models supported by the library
*
*  @note The list of shading modes has been taken from Blender3D.
*  See Blender3D documentation for more information. The API does
*  not distinguish between "specular" and "diffuse" shaders (thus the
*  specular term for diffuse shading models like Oren-Nayar remains
*  undefined)
*/
// ---------------------------------------------------------------------------
enum aiShadingMode
{
	/** Flat shading. Shading is done on per-face base, 
	*  diffuse only.
	*/
	aiShadingMode_Flat = 0x1,

	/** Diffuse gouraud shading. Shading on per-vertex base
	*/
	aiShadingMode_Gouraud =	0x2,

	/** Diffuse/Specular Phong-Shading
	*
	*  Shading is applied on per-pixel base. This is the
	*  slowest algorithm, but generates the best results.
	*/
	aiShadingMode_Phong = 0x3,

	/** Diffuse/Specular Phong-Blinn-Shading
	*
	*  Shading is applied on per-pixel base. This is a little
	*  bit faster than phong and in some cases even
	*  more realistic
	*/
	aiShadingMode_Blinn	= 0x4,

	/** Toon-Shading per pixel
	*
	*  Shading is applied on per-pixel base. The output looks
	*  like a comic. Often combined with edge detection.
	*/
	aiShadingMode_Toon = 0x5,

	/** OrenNayar-Shading per pixel
	*
	*  Extension to standard lambertian shading, taking the
	*  roughness of the material into account
	*	
	*/
	aiShadingMode_OrenNayar = 0x6,

	/** Minnaert-Shading per pixel
	*
	*  Extension to standard lambertian shading, taking the
	*  "darkness" of the material into account
	*/
	aiShadingMode_Minnaert = 0x7,

	/** CookTorrance-Shading per pixel
	*/
	aiShadingMode_CookTorrance = 0x8,

	/** No shading at all
	*/
	aiShadingMode_NoShading = 0x8
};


// ---------------------------------------------------------------------------
/** Data structure for a single property inside a material
*
*  @see aiMaterial
*/
// ---------------------------------------------------------------------------
struct aiMaterialProperty
{
	/** Specifies the name of the property (key)
	*
	*	Keys are case insensitive.
	*/
	C_STRUCT aiString* mKey;

	/**	Size of the buffer mData is pointing to, in bytes
	*/
	unsigned int mDataLength;

	/** Type information for the property.
	*
	*  Defines the data layout inside the
	*  data buffer. This is used by the library
	*  internally to perform debug checks.
	*/
	aiPropertyTypeInfo mType;

	/**	Binary buffer to hold the property's value
	*
	*  The buffer has no terminal character. However,
	*  if a string is stored inside it may use 0 as terminal,
	*  but it would be contained in mDataLength.
	*/
	char* mData;
};


// ---------------------------------------------------------------------------
/** Data structure for a material
*
*  Material data is stored using a key-value structure, called property
*  (to guarant that the system is maximally flexible).
*  The library defines a set of standard keys, which should be enough
*  for nearly all purposes. 
*/
// ---------------------------------------------------------------------------
struct aiMaterial
{
#ifdef __cplusplus
protected:
	aiMaterial() {}
public:
#endif // __cplusplus

	/** List of all material properties loaded.
	*/
	C_STRUCT aiMaterialProperty** mProperties;

	/** Number of properties loaded
	*/
	unsigned int mNumProperties;
	unsigned int mNumAllocated;
};


// ---------------------------------------------------------------------------
/** @def AI_MATKEY_NAME
*  Defines the name of the material (aiString)
*/
#define AI_MATKEY_NAME "$mat.name"

/** @def AI_MATKEY_SHADING_MODE
*  Defines the shading model to use (aiShadingMode)
*/
#define AI_MATKEY_SHADING_MODEL "$mat.shadingm"

/** @def AI_MATKEY_ENABLE_WIREFRAM
*  Integer property. 1 to enable wireframe for rendering
*/
#define AI_MATKEY_ENABLE_WIREFRAME "$mat.wireframe"

/** @def AI_MATKEY_OPACITY
*  Defines the base opacity of the material
*/
#define AI_MATKEY_OPACITY "$mat.opacity"

/** @def AI_MATKEY_BUMPSCALING
*  Defines the height scaling of a bump map (for stuff like Parallax
*  Occlusion Mapping)
*/
#define AI_MATKEY_BUMPSCALING "$mat.bumpscaling"

/** @def AI_MATKEY_SHININESS
*  Defines the base shininess of the material
*  This is the exponent of the phong shading equation.
*/
#define AI_MATKEY_SHININESS "$mat.shininess"

/** @def AI_MATKEY_SHININESS_STRENGTH
*  Defines the strength of the specular highlight.
*/
#define AI_MATKEY_SHININESS_STRENGTH "$mat.shinpercent"

/** @def AI_MATKEY_COLOR_DIFFUSE
*  Defines the diffuse base color of the material
*/
#define AI_MATKEY_COLOR_DIFFUSE "$clr.diffuse"

/** @def AI_MATKEY_COLOR_AMBIENT
*  Defines the ambient base color of the material
*/
#define AI_MATKEY_COLOR_AMBIENT "$clr.ambient"

/** @def AI_MATKEY_COLOR_SPECULAR
*  Defines the specular base color of the material
*/
#define AI_MATKEY_COLOR_SPECULAR "$clr.specular"

/** @def AI_MATKEY_COLOR_EMISSIVE
*  Defines the emissive base color of the material
*/
#define AI_MATKEY_COLOR_EMISSIVE "$clr.emissive"

/** @def AI_MATKEY_TEXTURE_DIFFUSE
*  Defines a specified diffuse texture channel of the material
*/
#define AI_MATKEY_TEXTURE_DIFFUSE(N) "$tex.file.diffuse["#N"]"
#define AI_MATKEY_TEXTURE_DIFFUSE_  "$tex.file.diffuse"

/** @def AI_MATKEY_TEXTURE_AMBIENT
*  Defines a specified ambient texture channel of the material
*/
#define AI_MATKEY_TEXTURE_AMBIENT(N) "$tex.file.ambient["#N"]"
#define AI_MATKEY_TEXTURE_AMBIENT_   "$tex.file.ambient"

/** @def AI_MATKEY_TEXTURE_SPECULAR
*  Defines a specified specular texture channel of the material
*/
#define AI_MATKEY_TEXTURE_SPECULAR(N) "$tex.file.specular["#N"]"
#define AI_MATKEY_TEXTURE_SPECULAR_   "$tex.file.specular"

/** @def AI_MATKEY_TEXTURE_EMISSIVE
*  Defines a specified emissive texture channel of the material
*/
#define AI_MATKEY_TEXTURE_EMISSIVE(N) "$tex.file.emissive["#N"]"
#define AI_MATKEY_TEXTURE_EMISSIVE_   "$tex.file.emissive"

/** @def AI_MATKEY_TEXTURE_NORMALS
*  Defines a specified normal texture channel of the material
*/
#define AI_MATKEY_TEXTURE_NORMALS(N) "$tex.file.normals["#N"]"
#define AI_MATKEY_TEXTURE_NORMALS_   "$tex.file.normals"

/** @def AI_MATKEY_TEXTURE_HEIGHT
* Defines a specified bumpmap texture (=heightmap) channel of the material
* This is very similar to #AI_MATKEY_TEXTURE_NORMALS. It is provided
* to allow applications to determine whether the input data for
* normal mapping is already a normal map or needs to be converted from
* a heightmap to a normal map.
*/
#define AI_MATKEY_TEXTURE_HEIGHT(N) "$tex.file.bump["#N"]"
#define AI_MATKEY_TEXTURE_HEIGHT_   "$tex.file.bump"

/** @def AI_MATKEY_TEXTURE_SHININESS
*  Defines a specified shininess texture channel of the material
*/
#define AI_MATKEY_TEXTURE_SHININESS(N) "$tex.file.shininess["#N"]"
#define AI_MATKEY_TEXTURE_SHININESS_   "$tex.file.shininess"

/** @def AI_MATKEY_TEXTURE_OPACITY
*  Defines a specified opacity texture channel of the material
*/
#define AI_MATKEY_TEXTURE_OPACITY(N) "$tex.file.opacity["#N"]"
#define AI_MATKEY_TEXTURE_OPACITY_   "$tex.file.opacity"


#define AI_MATKEY_TEXOP_DIFFUSE(N)		"$tex.op.diffuse["#N"]"
#define AI_MATKEY_TEXOP_AMBIENT(N)		"$tex.op.ambient["#N"]"
#define AI_MATKEY_TEXOP_SPECULAR(N)		"$tex.op.specular["#N"]"
#define AI_MATKEY_TEXOP_EMISSIVE(N)		"$tex.op.emissive["#N"]"
#define AI_MATKEY_TEXOP_NORMALS(N)		"$tex.op.normals["#N"]"
#define AI_MATKEY_TEXOP_HEIGHT(N)			"$tex.op.bump["#N"]"
#define AI_MATKEY_TEXOP_SHININESS(N)	"$tex.op.shininess["#N"]"
#define AI_MATKEY_TEXOP_OPACITY(N)		"$tex.op.opacity["#N"]"

#define AI_MATKEY_TEXOP_DIFFUSE_		"$tex.op.diffuse"
#define AI_MATKEY_TEXOP_AMBIENT_		"$tex.op.ambient"
#define AI_MATKEY_TEXOP_SPECULAR_		"$tex.op.specular"
#define AI_MATKEY_TEXOP_EMISSIVE_		"$tex.op.emissive"
#define AI_MATKEY_TEXOP_NORMALS_		"$tex.op.normals"
#define AI_MATKEY_TEXOP_HEIGHT_			"$tex.op.bump"
#define AI_MATKEY_TEXOP_SHININESS_		"$tex.op.shininess"
#define AI_MATKEY_TEXOP_OPACITY_		"$tex.op.opacity"

#define AI_MATKEY_UVWSRC_DIFFUSE(N)		"$tex.uvw.diffuse["#N"]"
#define AI_MATKEY_UVWSRC_AMBIENT(N)		"$tex.uvw.ambient["#N"]"
#define AI_MATKEY_UVWSRC_SPECULAR(N)	"$tex.uvw.specular["#N"]"
#define AI_MATKEY_UVWSRC_EMISSIVE(N)	"$tex.uvw.emissive["#N"]"
#define AI_MATKEY_UVWSRC_NORMALS(N)		"$tex.uvw.normals["#N"]"
#define AI_MATKEY_UVWSRC_HEIGHT(N)		"$tex.uvw.bump["#N"]"
#define AI_MATKEY_UVWSRC_SHININESS(N)	"$tex.uvw.shininess["#N"]"
#define AI_MATKEY_UVWSRC_OPACITY(N)		"$tex.uvw.opacity["#N"]"

#define AI_MATKEY_UVWSRC_DIFFUSE_		"$tex.uvw.diffuse"
#define AI_MATKEY_UVWSRC_AMBIENT_		"$tex.uvw.ambient"
#define AI_MATKEY_UVWSRC_SPECULAR_		"$tex.uvw.specular"
#define AI_MATKEY_UVWSRC_EMISSIVE_		"$tex.uvw.emissive"
#define AI_MATKEY_UVWSRC_NORMALS_		"$tex.uvw.normals"
#define AI_MATKEY_UVWSRC_HEIGHT_			"$tex.uvw.bump"
#define AI_MATKEY_UVWSRC_SHININESS_		"$tex.uvw.shininess"
#define AI_MATKEY_UVWSRC_OPACITY_		"$tex.uvw.opacity"

#define AI_MATKEY_TEXBLEND_DIFFUSE(N)	"$tex.blend.diffuse["#N"]"
#define AI_MATKEY_TEXBLEND_AMBIENT(N)	"$tex.blend.ambient["#N"]"
#define AI_MATKEY_TEXBLEND_SPECULAR(N)	"$tex.blend.specular["#N"]"
#define AI_MATKEY_TEXBLEND_EMISSIVE(N)	"$tex.blend.emissive["#N"]"
#define AI_MATKEY_TEXBLEND_NORMALS(N)	"$tex.blend.normals["#N"]"
#define AI_MATKEY_TEXBLEND_HEIGHT(N)		"$tex.blend.bump["#N"]"
#define AI_MATKEY_TEXBLEND_SHININESS(N)	"$tex.blend.shininess["#N"]"
#define AI_MATKEY_TEXBLEND_OPACITY(N)	"$tex.blend.opacity["#N"]"

#define AI_MATKEY_TEXBLEND_DIFFUSE_		"$tex.blend.diffuse"
#define AI_MATKEY_TEXBLEND_AMBIENT_		"$tex.blend.ambient"
#define AI_MATKEY_TEXBLEND_SPECULAR_	"$tex.blend.specular"
#define AI_MATKEY_TEXBLEND_EMISSIVE_	"$tex.blend.emissive"
#define AI_MATKEY_TEXBLEND_NORMALS_		"$tex.blend.normals"
#define AI_MATKEY_TEXBLEND_HEIGHT_		"$tex.blend.bump"
#define AI_MATKEY_TEXBLEND_SHININESS_	"$tex.blend.shininess"
#define AI_MATKEY_TEXBLEND_OPACITY_		"$tex.blend.opacity"


#define AI_MATKEY_ORENNAYAR_ROUGHNESS	 "$shading.orennayar.roughness"
#define AI_MATKEY_MINNAERT_DARKNESS		 "$shading.minnaert.darkness"
#define AI_MATKEY_COOK_TORRANCE_REFRACTI "$shading.cookt.refracti"
#define AI_MATKEY_COOK_TORRANCE_PARAM	 "$shading.cookt.param"


/** @def AI_MATKEY_GLOBAL_BACKGROUND_IMAGE
*  Global property defined by some loaders. Contains the path to 
*  the image file to be used as background image.
*/
#define AI_MATKEY_GLOBAL_BACKGROUND_IMAGE "$global.bg.image2d"


// ---------------------------------------------------------------------------
/** Retrieve a material property with a specific key from the material
*
*  @param pMat Pointer to the input material. May not be NULL
*  @param pKey Key to search for. One of the AI_MATKEY_XXX constants.
*  @param pPropOut Pointer to receive a pointer to a valid aiMaterialProperty
*         structure or NULL if the key has not been found. 
*/
// ---------------------------------------------------------------------------
aiReturn aiGetMaterialProperty(const C_STRUCT aiMaterial* pMat, 
	const char* pKey,
	const C_STRUCT aiMaterialProperty** pPropOut);


// ---------------------------------------------------------------------------
/** Retrieve an array of float values with a specific key 
*  from the material
*
* @param pMat Pointer to the input material. May not be NULL
* @param pKey Key to search for. One of the AI_MATKEY_XXX constants.
* @param pOut Pointer to a buffer to receive the result. 
* @param pMax Specifies the size of the given buffer, in float's.
*        Receives the number of values (not bytes!) read. 
*/
// ---------------------------------------------------------------------------
aiReturn aiGetMaterialFloatArray(const C_STRUCT aiMaterial* pMat, 
	const char* pKey,
	float* pOut,
	unsigned int* pMax);

#ifdef __cplusplus
// inline it
inline aiReturn aiGetMaterialFloat(const C_STRUCT aiMaterial* pMat, 
	 const char* pKey,
	 float* pOut)
	{return aiGetMaterialFloatArray(pMat,pKey,pOut,(unsigned int*)0x0);}
#else 
// use our friend, the C preprocessor
#define aiGetMaterialFloat (pMat, pKey, pOut) \
	aiGetMaterialFloatArray(pMat, pKey, pOut, NULL)
#endif //!__cplusplus


// ---------------------------------------------------------------------------
/** Retrieve an array of integer values with a specific key 
*  from the material
*
* @param pMat Pointer to the input material. May not be NULL
* @param pKey Key to search for. One of the AI_MATKEY_XXX constants.
* @param pOut Pointer to a buffer to receive the result. 
* @param pMax Specifies the size of the given buffer, in int's.
*        Receives the number of values (not bytes!) read. 
*/
// ---------------------------------------------------------------------------
aiReturn aiGetMaterialIntegerArray(const C_STRUCT aiMaterial* pMat, 
	const char* pKey,
	int* pOut,
	unsigned int* pMax);

#ifdef __cplusplus
// inline it
inline aiReturn aiGetMaterialInteger(const C_STRUCT aiMaterial* pMat, 
	const char* pKey,
	int* pOut)
	{return aiGetMaterialIntegerArray(pMat,pKey,pOut,(unsigned int*)0x0);}
#else 
// use our friend, the C preprocessor
#define aiGetMaterialInteger (pMat, pKey, pOut) \
	aiGetMaterialIntegerArray(pMat, pKey, pOut, NULL)
#endif //!__cplusplus



// ---------------------------------------------------------------------------
/** Retrieve a color value from the material property table
*
*	@param pMat Pointer to the input material. May not be NULL
*	@param pKey Key to search for. One of the AI_MATKEY_XXX constants.
*	@param pOut Pointer to a buffer to receive the result. 
*/
// ---------------------------------------------------------------------------
aiReturn aiGetMaterialColor(const C_STRUCT aiMaterial* pMat, 
	const char* pKey,
	aiColor4D* pOut);


// ---------------------------------------------------------------------------
/** Retrieve a string from the material property table
*
*	@param pMat Pointer to the input material. May not be NULL
*	@param pKey Key to search for. One of the AI_MATKEY_XXX constants.
*	@param pOut Pointer to a buffer to receive the result. 
*/
// ---------------------------------------------------------------------------
aiReturn aiGetMaterialString(const C_STRUCT aiMaterial* pMat, 
	const char* pKey,
	aiString* pOut);


#define AI_TEXTYPE_OPACITY		0x0
#define AI_TEXTYPE_SPECULAR		0x1
#define AI_TEXTYPE_AMBIENT		0x2
#define AI_TEXTYPE_EMISSIVE		0x3
#define AI_TEXTYPE_HEIGHT		0x4
#define AI_TEXTYPE_NORMALS		0x5
#define AI_TEXTYPE_SHININESS	0x6
#define AI_TEXTYPE_DIFFUSE		0x7

// ---------------------------------------------------------------------------
/** Helper function to get a texture from a material
 *
 *  This function is provided just for convinience. 
 *  @param pMat Pointer to the input material. May not be NULL
 *  @param iIndex Index of the texture to retrieve. If the index is too 
 *     large the function fails.
 *  @param iTexType One of the AI_TEXTYPE constants. Specifies the type of
 *     the texture to retrieve (e.g. diffuse, specular, height map ...)
 *  @param szPath Receives the output path
 *     NULL is no allowed as value
 *  @param piUVIndex Receives the UV index of the texture. 
 *     NULL is allowed as value.
 *  @param pfBlendFactor Receives the blend factor for the texture
 *     NULL is allowed as value.
 *  @param peTextureOp Receives the texture operation to perform between
 *     this texture and the previous texture.
 *     NULL is allowed as value.
 */
// ---------------------------------------------------------------------------
aiReturn aiGetMaterialTexture(const C_STRUCT aiMaterial* pMat,
	unsigned int iIndex,
	unsigned int iTexType,
	C_STRUCT aiString* szPath,
	unsigned int* piUVIndex,
	float* pfBlendFactor,
	aiTextureOp* peTextureOp); 


#ifdef __cplusplus
}
#endif //!__cplusplus

#endif //!!AI_MATERIAL_H_INC
