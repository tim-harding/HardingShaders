#include "stdafx.h"

extern const AtNodeMethods* DirectionalAoMethods;
extern const AtNodeMethods* CameraTextureMethods;
extern const AtNodeMethods* CellularMethods;
extern const AtNodeMethods* StencilSetMethods;
extern const AtNodeMethods* StencilGetMethods;
extern const AtNodeMethods* BakerCameraMethods;
extern const AtNodeMethods* PixelateMethods;
extern const AtNodeMethods* WriteFloatAdditiveMethods;

enum Shaders {
	DirectionalAo,
	CameraTexture,
	Cellular,
	StencilSet,
	StencilGet,
	Pixelate,
	WriteFloatAdditive,
};

node_loader{
	switch (i) {
	case DirectionalAo:
		node->methods = DirectionalAoMethods;
		node->name = "directional_ao";
		node->output_type = AI_TYPE_RGB;
		break;

	case CameraTexture:
		node->methods = CameraTextureMethods;
		node->name = "camera_texture";
		node->output_type = AI_TYPE_RGB;
		break; 

	case Cellular:
		node->methods = CellularMethods;
		node->name = "cellular";
		node->output_type = AI_TYPE_RGB;
		break;

	case StencilSet:
		node->methods = StencilSetMethods;
		node->name = "stencil_set";
		node->output_type = AI_TYPE_CLOSURE;
		break;

	case StencilGet:
		node->methods = StencilGetMethods;
		node->name = "stencil_get";
		node->output_type = AI_TYPE_INT;
		break;

	case Pixelate:
		node->methods = PixelateMethods;
		node->name = "pixelate";
		node->output_type = AI_TYPE_RGB;
		break;

	case WriteFloatAdditive:
		node->methods = WriteFloatAdditiveMethods;
		node->name = "write_float_additive";
		node->output_type = AI_TYPE_RGB;
		break;

	default:
		return false;
	}

	node->node_type = AI_NODE_SHADER;
	strcpy_s(node->version, AI_VERSION);
	return true;
}