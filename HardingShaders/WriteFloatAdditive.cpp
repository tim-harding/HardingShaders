#include "stdafx.h"

AI_SHADER_NODE_EXPORT_METHODS(WriteFloatAdditiveMethods);


enum class NodeParameters {
	Beauty,
	Input,
	AovName,
};


node_parameters
{
	AiParameterRGB("beauty", 0.0f, 0.0f, 0.0f);
	AiParameterFlt("input", 0.0f);
	AiParameterStr("aov_name", "");
}


node_initialize{ }


node_update{ }


node_finish{ }


shader_evaluate
{
	AtRGB beauty = AiShaderEvalParamRGB(static_cast<int>(NodeParameters::Beauty));
	float input = AiShaderEvalParamFlt(static_cast<int>(NodeParameters::Input));
	AtString aov_name = AiShaderEvalParamStr(static_cast<int>(NodeParameters::AovName));

	// Pass through
	sg->out.RGB() = beauty;

	float current_aov_value = 0.0f;
	bool success = AiAOVGetFlt(sg, aov_name, current_aov_value);
	float write = input + current_aov_value;
	AiAOVSetFlt(sg, aov_name, current_aov_value + input);
} 