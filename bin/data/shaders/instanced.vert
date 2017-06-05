#version 150

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform vec4 globalColor = vec4(1.0);
uniform sampler2D tex0;
uniform float timeValue=0.0;

uniform vec4 color1;
uniform vec4 color2;
uniform int ticks;
uniform int perturbation;

uniform int xSpacing;
uniform int ySpacing;

uniform int count;

in vec4 position;
in vec2 texcoord;
in vec4 color_coord;
in vec3 normal;

out vec4 colorVarying;
out vec2 texCoordVarying;

void main()
{

	int init_radius = 20;

	int widthCount = 1920 / ( xSpacing * init_radius);
	int heightCount = 1080 / ( ySpacing * init_radius);

	int id = (gl_InstanceID % count); 

	int offset = id % perturbation;

	int instanceX = (id % widthCount) * xSpacing * init_radius - 1920/2 + init_radius + int(offset * sin(ticks));
	int instanceY = (int(id / widthCount) * ySpacing * init_radius) % 1080 - 1080/2;
	int instanceZ = int(float(id) / (widthCount * heightCount)) * 2*init_radius;

	vec4 newPos = position;
	newPos.x = position.x + instanceX;
	newPos.y = position.y + instanceY;
	newPos.z = position.z + instanceZ;

	//colorVarying = vec4(float(id) / count, 1-float(id)/float(count), 1.0, 1.0);

	colorVarying = vec4(mix(color1, color2, float(id)/float(count)));
	texCoordVarying = vec2(position.x, position.y);

	gl_Position = projectionMatrix * modelViewMatrix * newPos;

}