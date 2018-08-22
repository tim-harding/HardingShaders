#include "stdafx.h"
#include "CellularShader.h"


///////////////////////////////////////////////
// Deprecated with the release of Arnold 3.1 //
///////////////////////////////////////////////


AI_SHADER_NODE_EXPORT_METHODS(CellularMethods);


node_parameters
{
	AiParameterInt("octaves", 1);
	AiParameterEnum("feature", 0, FeatureNames);
	AiParameterEnum("space", 0, SpaceNames);
	AiParameterVec("scale", 1.0f, 1.0f, 1.0f);
	AiParameterVec("offset", 0.0f, 0.0f, 0.0f);
	AiParameterVec("position", 0.0f, 0.0f, 0.0f);
}


node_initialize{ }


node_update{ }


node_finish{ }


shader_evaluate
{
	Params params {
		AiShaderEvalParamInt(static_cast<int>(NodeParameters::Octaves)),
		static_cast<Feature>(AiShaderEvalParamEnum(static_cast<int>(NodeParameters::Feature))),
		static_cast<Space>(AiShaderEvalParamEnum(static_cast<int>(NodeParameters::Space))),
		AiShaderEvalParamVec(static_cast<int>(NodeParameters::Scale)),
		AiShaderEvalParamVec(static_cast<int>(NodeParameters::Offset)),
		AiShaderEvalParamVec(static_cast<int>(NodeParameters::Position))
	};

	sg->out.RGB() = Evaluate(sg, params);
}


inline AtRGB Evaluate(const AtShaderGlobals* sg, const Params& params) noexcept
{
	AtVector position = GetPosition(sg, params);
	float noise = Noise(position, params);
	return AtRGB(noise, noise, noise);
}


inline float Noise(const AtVector& position, const Params& params) noexcept
{
	const int closestPointCount = 2;
	const float lacunarity = 1.92f;
	const float randomness = 1.0f;
	float distances[closestPointCount];
	AiCellular(position, closestPointCount, params.octaves, lacunarity, randomness, distances, nullptr, nullptr);
	return distances[static_cast<int>(params.feature)];
}


inline AtVector GetPosition(const AtShaderGlobals* sg, const Params& params) noexcept {
	AtVector position = params.position;
	if (IsZero(position))
	{
		position = SpaceToPosition(params.space, sg);
		TransformPosition(position, params);
	}
	return position;
}


inline bool IsZero(const AtVector& vector) noexcept {
	return vector == AtVector(0.0f, 0.0f, 0.0f);
}


inline AtVector SpaceToPosition(Space space, const AtShaderGlobals* sg) noexcept {
	switch (space)
	{
	case Space::UV:
		return AtVector(sg->u, sg->v, 0.0f);
	case Space::World:
		return sg->P;
	case Space::Object:
		return sg->Po;
	default:
		return AtVector(0.0f, 0.0f, 0.0f);
	}
}


inline void TransformPosition(AtVector& position, const Params& params) noexcept {
	position = position * params.scale + params.offset;
}
