#include "stdafx.h"
#include "BloomShader.h"


AI_SHADER_NODE_EXPORT_METHODS(BloomMethods);


enum class Params {
	Locator
};


node_parameters
{
	AiParameterMtx("locator", AiM4Identity());
}


node_initialize{ }


node_update{ }


node_finish{ }


shader_evaluate
{
	AtMatrix locator = *AiShaderEvalParamMtx(static_cast<int>(Params::Locator));
	AtMatrix inverseLocator = AiM4Invert(locator);
	AtVector position = AiM4PointByMatrixMult(inverseLocator, sg->P);
	float starNoise = AiNoise4(AiV3Normalize(position), 0.f, 5, 1.5f, 1.92f) * 0.5f + 0.5f;
	float len = AiV3Length(position);
	sg->out.RGB() = starNoise;
}
