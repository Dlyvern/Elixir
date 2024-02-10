#version 330 core

out vec4 FragColor;
in vec2 TextureCoordinates;
uniform sampler2D texture1;

void main()
{
//    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    FragColor = texture(texture1,  TextureCoordinates);
}