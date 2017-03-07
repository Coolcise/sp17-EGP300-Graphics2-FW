/*
	Phong with Shadow Mapping
	By Dan Buckstein
	Fragment shader that performs Phong shading and shadow mapping.
	
	Modified by: ______________________________________________________________
*/

#version 410


// ****
// varyings: 
in vertexdata
{
	vec4 position_clip_alt;
	vec4 normal;
	vec4 texcoord;
	vec4 lightVec;
	vec4 eyeVec;
} pass;

// ****
// uniforms: 
uniform sampler2D tex_dm;
uniform sampler2D tex_sm;

uniform sampler2D tex_bool;
uniform sampler2D shadowmap;

uniform vec4 lightColor;

// target: 
layout (location = 0) out vec4 fragColor;


// ****
// constants/globals: 
const vec4 AMBIENT = vec4(0.02, 0.01, 0.0, 0.0);
vec2 booleanSample = vec2(0.0);

void main()
{

	vec4 projector_uv = pass.position_clip_alt / pass.position_clip_alt.w;
	float shadowSample = texture(shadowmap, projector_uv.xy).r;

	bool fragIsShadowed = (projector_uv.z > shadowSample + 0.025);
	
	vec4 diffuseColor = texture(tex_dm, pass.texcoord.xy);
	vec4 specularColor = texture(tex_sm, pass.texcoord.xy);

	vec4 N = normalize(pass.normal);
	vec4 L = normalize(pass.lightVec);
	float kd = dot(N, L);
	if(fragIsShadowed && pass.position_clip_alt.z > 0.0)
	{
		kd *= 0.2;
	}
	
// 2. specular
	vec4 V = normalize(pass.eyeVec);
	vec4 R = (kd+kd)*N - L;
	float ks = dot(V, R);

	// 3. clamp & exponent
	kd = max(0.0, kd);
	ks = max(0.0, ks);
	ks *= ks;
	ks *= ks;
	ks *= ks;
	ks *= ks;
	ks *= ks;
	ks *= ks;


	// ****
	// extra: apply textures as well
	fragColor = (kd*diffuseColor + ks*specularColor)*lightColor + AMBIENT;


//	fragColor = vec4(0.0, 0.5, 1.0, 1.0);
}