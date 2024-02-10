//#version 330 core
//
//layout (location = 0) in vec3 aPosition;
//layout (location = 1) in vec2 aTexturePostion;
//
//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
//
//
//out vec2 TextureCoordinates;
//
//void main()
//{
//	gl_Position = projection * view * model * vec4(aPosition, 1.0);
//	TextureCoordinates = vec2(texturePostion.x, 1 - texturePostion.y);
//}

#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexturePostion;


out vec2 TextureCoordinates;
uniform mat4 camMatrix;


void main()
{
	gl_Position = camMatrix * vec4(aPosition, 1.0);
	TextureCoordinates = aTexturePostion;
}