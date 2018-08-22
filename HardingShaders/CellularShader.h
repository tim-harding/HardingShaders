#pragma once


enum class Space 
{ 
	UV, 
	World, 
	Object 
};


static const char* SpaceNames[] = 
{
	"UV",
	"World",
	"Object",
	nullptr
};


enum class Feature 
{ 
	First, 
	Second 
};


static const char* FeatureNames[] = 
{
	"First",
	"Second",
	nullptr
};


enum class NodeParameters 
{ 
	Octaves, 
	Feature, 
	Space, 
	Scale, 
	Offset, 
	Position 
};


struct Params 
{
	int octaves;
	Feature feature;
	Space space;
	AtVector scale;
	AtVector offset;
	AtVector position;
};


inline AtRGB Evaluate(const AtShaderGlobals*, const Params&) noexcept;
inline AtVector GetPosition(const AtShaderGlobals*, const Params&) noexcept;
inline bool IsZero(const AtVector&) noexcept;
inline AtVector SpaceToPosition(Space, const AtShaderGlobals*) noexcept;
inline void TransformPosition(AtVector&, const Params&) noexcept;
inline float Noise(const AtVector&, const Params&) noexcept;