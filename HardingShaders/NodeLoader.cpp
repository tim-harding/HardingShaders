#include "stdafx.h"

extern const AtNodeMethods* DirectionalAoMethods;
extern const AtNodeMethods* CameraTextureMethods;

enum Shaders {
	DirectionalAo,
	CameraTexture
};

node_loader{
	switch (i) {
	case DirectionalAo:
		node->methods = DirectionalAoMethods;
		node->name = "directional_ao";
		break;

	case CameraTexture:
		node->methods = CameraTextureMethods;
		node->name = "camera_texture";
		break;

	default:
		return false;
	}

	node->node_type = AI_NODE_SHADER;
	node->output_type = AI_TYPE_RGB;
	strcpy_s(node->version, AI_VERSION);
	return true;
}  