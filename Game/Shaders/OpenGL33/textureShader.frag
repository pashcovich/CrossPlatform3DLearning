#version 330

smooth in float cosAngIncidence;
in vec2 textureCoords;

uniform sampler2D textureImage;

out vec4 outputColour;

void main()
{

//outputColour =  cosAngIncidence * 0.8 * vec4(1.0, 1.0, 1.0, 1.0);
vec4 texCol =  texture(textureImage, textureCoords);
outputColour = cosAngIncidence * 0.8 * vec4(texCol.x, texCol.y, texCol.z, 1.0);
}