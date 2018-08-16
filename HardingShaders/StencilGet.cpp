#include "stdafx.h"


AI_SHADER_NODE_EXPORT_METHODS(StencilGetMethods);


enum Parameters {
	p_stencil,
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
	int out = 0;
	int success = AiStateGetMsgInt(message, &out);
	sg->out.INT() = success && stencil == out;
}