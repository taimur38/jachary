#version 150

uniform sampler2DRect tex0;
in vec4 colorVarying;
in vec2 texCoordVarying;

out vec4 fragColor;

void main()
{
	vec4 texcol = texture(tex0, texCoordVarying * 1080);
    //fragColor = colorVarying;
	fragColor = texcol;
	//fragColor = vec4(1.0, 1.0, 1.0, 1.0); // white
}