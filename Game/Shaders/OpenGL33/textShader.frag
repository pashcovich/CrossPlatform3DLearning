#version 330

in vec2 textureCoords;
uniform sampler2D textureImage;
out vec4 outputColour;

void main()
{

    outputColour = texture(textureImage, textureCoords);
    //outputColour = vec4(1.0, 1.0, 1.0, 1.0);
}
