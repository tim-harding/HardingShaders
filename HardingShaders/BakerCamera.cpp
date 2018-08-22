#include "stdafx.h"
#include "BakerCamera.h"


AI_CAMERA_NODE_EXPORT_METHODS(BakerCameraMethods);


node_parameters
{
	AiParameterStr(ParameterNames::positionFilename, AtString());
	AiParameterStr(ParameterNames::normalFilename, AtString());
	AiParameterFlt(ParameterNames::normalOffset, 1.f);
}


node_initialize
{
	AiCameraInitialize(node);
	NodeData* data = new NodeData();
	AiNodeSetLocalData(node, data);

	data->sg = AiShaderGlobals();
	data->normalOffset = AiNodeGetInt(node, ParameterNames::normalOffset);
	AiTextureParamsSetDefaults(data->textureParams);
	getTextureHandles(node, data);

}


node_update
{
	AiCameraUpdate(node, false);
	NodeData* data = static_cast<NodeData*>(AiNodeGetLocalData(node));

	data->normalOffset = AiNodeGetFlt(node, ParameterNames::normalOffset);
	clearTextureHandles(data);
	getTextureHandles(node, data);
}


node_finish
{
	NodeData* data = static_cast<NodeData*>(AiNodeGetLocalData(node));
	AiTextureHandleDestroy(data->positionTexture);
	AiTextureHandleDestroy(data->normalTexture);
	AiShaderGlobalsDestroy(data->sg);
	delete data;
	AiNodeSetLocalData(node, nullptr);
}


camera_create_ray
{
	NodeData* data = static_cast<NodeData*>(AiNodeGetLocalData(node));
	data->sg->u = input.sx / 2.f + 1.f;
	data->sg->v = input.sy / 2.f + 1.f;
	bool success;

	AtRGBA position = AiTextureHandleAccess(data->sg, data->positionTexture, data->textureParams, &success);
	if (success) {
		output.origin = AtVector(position.r, position.g, position.b);
	}

	AtRGBA normal = AiTextureHandleAccess(data->sg, data->normalTexture, data->textureParams, &success);
	if (success) {
		output.dir = AtVector(normal.r, normal.g, normal.b);
	}
}


camera_reverse_ray
{
	return false;
} 


void getTextureHandle(const AtNode* node, AtTextureHandle* handle, const char* parameter) 
{
	AtString filename = AiNodeGetStr(node, parameter);
	handle = AiTextureHandleCreate(filename.c_str());
}


void getTextureHandles(const AtNode* node, NodeData* data)
{
	getTextureHandle(node, data->positionTexture, ParameterNames::positionFilename);
	getTextureHandle(node, data->normalTexture, ParameterNames::normalFilename);
}


void clearTextureHandles(NodeData* data)
{
	AiTextureHandleDestroy(data->positionTexture);
	AiTextureHandleDestroy(data->normalTexture);
}