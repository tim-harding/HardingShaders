#include "stdafx.h"

extern const AtNodeMethods* DirectionalAoMethods;
extern const AtNodeMethods* CameraTextureMethods;
extern const AtNodeMethods* CellularMethods;
extern const AtNodeMethods* StencilSetMethods;
extern const AtNodeMethods* StencilGetMethods;
extern const AtNodeMethods* BakerCameraMethods;

enum Shaders {
	DirectionalAo,
	CameraTexture,
	Cellular,
	StencilSet,
	StencilGet,
	BakerCamera
};

node_loader{
	switch (i) {
	case DirectionalAo:
		node->methods = DirectionalAoMethods;
		node->name = "directional_ao";
		node->node_type = AI_NODE_SHADER;
		node->output_type = AI_TYPE_RGB;
		break;

	case CameraTexture:
		node->methods = CameraTextureMethods;
		node->name = "camera_texture";
		node->node_type = AI_NODE_SHADER;
		node->output_type = AI_TYPE_RGB;
		break;

	case Cellular:
		node->methods = CellularMethods;
		node->name = "cellular";
		node->node_type = AI_NODE_SHADER;
		node->output_type = AI_TYPE_RGB;
		break;

	case StencilSet:
		node->methods = StencilSetMethods;
		node->name = "stencil_set";
		node->node_type = AI_NODE_SHADER;
		node->output_type = AI_TYPE_CLOSURE;
		break;

	case StencilGet:
		node->methods = StencilGetMethods;
		node->name = "stencil_get";
		node->node_type = AI_NODE_SHADER;
		node->output_type = AI_TYPE_INT;
		break;

	case BakerCamera:
		node->methods = BakerCameraMethods;
		node->name = "baker_camera";
		node->node_type = AI_NODE_CAMERA;
		node->output_type = AI_TYPE_NONE;
		break;

	default:
		return false;
	}


	strcpy_s(node->version, AI_VERSION);
	return true;
}