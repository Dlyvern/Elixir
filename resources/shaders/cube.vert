#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 texturePostion;

out vec2 TextureCoordinates;

uniform mat4 rotationMatrix;

void main()
{
	gl_Position = rotationMatrix * vec4(aPosition, 1.0);
	TextureCoordinates = vec2(texturePostion.x, 1 - texturePostion.y);
}
