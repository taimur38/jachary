#version 150

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform vec4 globalColor = vec4(1.0);
uniform sampler2D tex0;
uniform float timeValue=0.0;

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

	int widthCount = 1920 / ( 4 * init_radius);
	int heightCount = 1080 / ( 3 * init_radius);

	int id = (gl_InstanceID % count); 
	int instanceX = (id % widthCount) * 4 * init_radius - 1920/2 + init_radius;
	int instanceY = (int(id / widthCount) * 3 * init_radius) % 1080 - 1080/2;
	int instanceZ = int(float(id) / (widthCount * heightCount)) * 2*init_radius;

	vec4 newPos = position;
	newPos.x = position.x + instanceX;
	newPos.y = position.y + instanceY;
	newPos.z = position.z + instanceZ;

	colorVarying = vec4(float(id) / count, 1-float(id)/float(count), 1.0, 1.0);

	gl_Position = projectionMatrix * modelViewMatrix * newPos;

}