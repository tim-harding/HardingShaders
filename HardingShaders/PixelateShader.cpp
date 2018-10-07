#include "stdafx.h"

AI_SHADER_NODE_EXPORT_METHODS(PixelateMethods);

enum PixelateParams {
	p_input,
	p_resolution,
};

node_parameters{
	AiParameterRGB("input", 1.f, 1.f, 1.f);
	AiParameterVec2("resolution", 64.f, 64.f)
}


node_initialize{ }


node_update{ }


node_finish{ }


shader_evaluate{
	AtVector2 resolution = AiShaderEvalParamVec2(p_resolution);
	float u = sg->u;
	float v = sg->v;
	sg->u = u - fmod(u, 1.f / resolution.x);
	sg->v = v - fmod(v, 1.f / resolution.y);
	sg->out.RGB() = AiShaderEvalParamRGB(p_input);
} 