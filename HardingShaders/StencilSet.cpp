#include "stdafx.h"


AI_SHADER_NODE_EXPORT_METHODS(StencilSetMethods);

enum Parameters {
	p_stencil
};

node_parameters
{
	AiParameterInt("stencil", 0);
}


node_initialize{}


node_update{}


node_finish{}


shader_evaluate
{
	int stencil = AiShaderEvalParamInt(p_stencil);
	static const AtString message{ "stencil" };
	AiStateSetMsgInt(message, stencil);
	sg->out.RGBA() = AtRGBA(0.f, 0.f, 0.f, 0.f);
	sg->out.CLOSURE() = AiClosureTransparent(sg, AI_RGB_WHITE, nullptr);
} 