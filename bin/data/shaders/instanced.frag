#version 150

uniform sampler2DRect tex0;
uniform int colorMode;

in vec4 colorVarying;
in vec2 texCoordVarying;

out vec4 fragColor;

void main()
{
	if(colorMode == 0) {
		fragColor = texture(tex0, texCoordVarying * 1080);
	}
	else {
		fragColor = colorVarying;
	}
	//fragColor = vec4(1.0, 1.0, 1.0, 1.0); // white
}