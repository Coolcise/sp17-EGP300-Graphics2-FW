/*
* Authors: David Horntvedt
* Course: EGP 300
*
* We certify that this work is
* entirely our own. The assessor of this project may reproduce this project
* and provide copies to other academic staff, and/or communicate a copy of
* this project to a plagiarism-checking service, which may retain a copy of the
* project on its database.
*/

/*Sources:
Blinn-Phong:
http://sunandblackcat.com/tipFullView.php?l=eng&topicid=30&topic=Phong-Lighting
https://www.google.ca/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0ahUKEwjuj-nclb7TAhVjw4MKHa6FAW4QFggkMAA&url=https%3A%2F%2Fen.wikipedia.org%2Fwiki%2FBlinn%25E2%2580%2593Phong_shading_model&usg=AFQjCNE5BWRGRdd14rrZJweghI1mDzcsRA
https://tomaka.github.io/glium/book/tuto-13-phong.html

Rim lighting:
http://www.roxlu.com/2014/037/opengl-rim-shader

*/
// version
#version 410


// ****
// varyings
in vertex
{
	vec4 normal;
	vec4 lightVec;
	vec4 eyeVec;
	vec2 texcoord;
} data;


// ****
// uniforms
uniform sampler2D tex_dm;
uniform sampler2D tex_sm;

// ****
// target
layout(location = 0) out vec4 fragColor;

//Lighting reflection and intensity		 						   
const vec4 ambientIntensity    = vec4(0.1f, 0.1f, 0.1f, 1.0f);
const vec4 ambientReflection   = vec4(1.0f, 1.0f, 1.0f, 1.0f);

const vec4 diffuseIntensity   = vec4(0.7f, 0.7f, 0.7f, 1.0f);
const vec4 diffuseReflection  = vec4(1.0f, 1.0f, 1.0f, 1.0f);

const vec4 specularIntensity  = vec4(0.8f, 0.8f, 0.8f, 1.0f);
const vec4 specularReflection = vec4(1.0f, 1.0f, 1.0f, 1.0f);

//Shiny coefficient
const float shiny = 100.0f;

//Rim lighting vars
const float rimLightingMod = 0.8f;
const float rimLightingStep = 0.4f;

// shader function
void main()
{
	//Normalize vectors
	vec4 L = normalize(data.lightVec);
	vec4 V = normalize(data.eyeVec);
	vec4 N = normalize(data.normal);

	//N dot L
	float NdL = dot(N, L);

	//Ambient lighting
	vec4 ambient = ambientReflection * ambientIntensity;
	
	//Diffuse lighting
	float diffuseTerm = clamp(NdL,0,1);
	vec4 diffuse = diffuseReflection * diffuseIntensity * diffuseTerm;
	
	//Specular lighting
	float specularTerm = 0;
	if(NdL > 0)
	{
		vec4 H = normalize(L+V);
		specularTerm = pow(dot(N,H), shiny);
	}
	vec4 specular = specularReflection * specularIntensity * specularTerm;

	//Get color samples
	vec4 diffuseColor = texture(tex_dm, data.texcoord.xy);
	vec4 specularColor = texture(tex_dm, data.texcoord.xy);

	//Rimlighting
	float vdn = (1.0 - max(dot(V,N), 0.0f)) * rimLightingMod;

	vec4 color = diffuseColor * diffuse + specularColor * specular + ambient;
	color += vec4(smoothstep(rimLightingStep, 1.0f, vdn));

	fragColor = color;
	fragColor.a = 1;
}