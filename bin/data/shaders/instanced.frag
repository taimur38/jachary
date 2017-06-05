#version 150

in vec4 colorVarying;
in vec2 texCoordVarying;

out vec4 fragColor;

void main()
{
	fragColor = colorVarying;
	//fragColor = vec4(1.0, 1.0, 1.0, 1.0); // white
}