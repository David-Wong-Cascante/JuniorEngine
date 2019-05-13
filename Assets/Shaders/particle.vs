// Author: David Wong
// Email: david.wongcascante@digipen.edu
// Created: 10 May 2019
// Last Modified: 10 May 2019
// File name: particleVS.vs

#version 430 core

// In variables
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec4 particlePos;
layout (location = 3) in vec4 particleVel;
layout (location = 4) in vec4 particleColor;
layout (location = 5) in vec4 texCoordMods;
layout (location = 6) in float particleSize;
layout (location = 7) in float particleLifeTime;
layout (location = 8) in float particleAge;

// Uniforms
uniform mat4 camera;
uniform int textureAtlas;

// Out variables
out vec4 color;
out vec2 TexCoords;
out uint TexAtlas;

void main()
{
	// Set the in variables for the fragment shader
	TexCoords = texCoords;
	TexAtlas = textureAtlas;
	// Modify the texture coordinates
	TexCoords.x *= texCoordMods.z;
	TexCoords.y *= texCoordMods.w;
	TexCoords.xy += texCoordMods.xy;
	color = particleColor;
	//color = vec4(particleSize, 0, 0, 1);
	// Set the position of the particle's vertex
	vec3 particleVertexPos = vertexPos;
	particleVertexPos *= vec3(particleSize);
	particleVertexPos += particlePos.xyz;
	//gl_Position = vec4(vertexPos, 1.0);
	gl_Position = camera * vec4(particleVertexPos, 1.0f);
}