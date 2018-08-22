#include "stdafx.h"

AI_SHADER_NODE_EXPORT_METHODS(CameraTextureMethods);

enum CameraTextureParams {
	p_matrix,
	p_apertureHorizontal,
	p_apertureVertical,
	p_focalLength
};

node_parameters
{
	AiParameterMtx("matrix", AtMatrix());
	AiParameterFlt("apertureHorizontal", 36);
	AiParameterFlt("apertureVertical", 24);
	AiParameterFlt("focalLength", 60);
}

node_initialize{}

node_update{}

node_finish{}

shader_evaluate
{
	const float INCH_TO_MM = 25.4f;
	float apertureX = AiShaderEvalParamFlt(p_apertureHorizontal);
	float apertureY = AiShaderEvalParamFlt(p_apertureVertical);
	float focalLength = AiShaderEvalParamFlt(p_focalLength);
	AtMatrix matrix = *AiShaderEvalParamMtx(p_matrix);

	float uvScalarX = (apertureX * INCH_TO_MM) / (2.0f * focalLength);
	float uvScalarY = (apertureY * INCH_TO_MM) / (2.0f * focalLength);

	float x = uvScalarX * (sg->u * 2.0f - 1.0f);
	float y = uvScalarY * (sg->v * 2.0f - 1.0f);
	AtVector rayDirection = AtVector(x, y, -1.0f);
	rayDirection = AiM4VectorByMatrixMult(matrix, rayDirection);

	// row major indexing
	AtVector position = AtVector(matrix.data[3][0], matrix.data[3][1], matrix.data[3][2]);
	AtRay ray = AiMakeRay(AI_RAY_CAMERA, position, &rayDirection, AI_BIG, sg);
	AtScrSample sample = AtScrSample();
	AiTrace(ray, AtRGB(1.0f, 1.0f, 1.0f), sample);
	sg->out.RGB() = sample.color;
}