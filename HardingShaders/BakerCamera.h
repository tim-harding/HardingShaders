#pragma once

struct NodeData 
{
	AtShaderGlobals* sg;
	AtTextureParams textureParams;
	AtTextureHandle* positionTexture;
	AtTextureHandle* normalTexture;
	float normalOffset;
};


struct ParameterNames
{
	static const char* positionFilename;
	static const char* normalFilename;
	static const char* normalOffset;
};


const char* ParameterNames::positionFilename = "position_filename";
const char* ParameterNames::normalFilename = "normal_filename";
const char* ParameterNames::normalOffset = "normal_offset";


void getTextureHandle(const AtNode*, AtTextureHandle*, const char*);
void getTextureHandles(const AtNode*, NodeData*);
void clearTextureHandles(NodeData*);