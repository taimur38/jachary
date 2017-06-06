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

uniform int boomTick;
uniform int boomDuration;
uniform int boomStrength;

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

	int maxX = (count % widthCount) * xSpacing * init_radius - 1920/2 + init_radius + int(offset * sin(ticks));
	int maxY = (int(count / widthCount) * ySpacing * init_radius) % 1080 - 1080/2;
	int maxZ = int(float(count) / (widthCount * heightCount)) * 2*init_radius;

	vec4 cornerPt = vec4(maxX, maxY, maxZ, 0.0);
	vec4 center = vec4(0, 0, maxZ/2.0, 0.0);

	vec4 newPos = position;
	newPos.x = position.x + instanceX;
	newPos.y = position.y + instanceY;
	newPos.z = position.z + instanceZ;

	float boomPropagation = 100;


	float boomTravel = boomPropagation * (ticks - boomTick);

	if(boomTravel > .8 * length(newPos - center) && boomTravel < 1.5 * length(newPos - center)) {
			newPos.x += sign(newPos.x) * boomStrength;
			newPos.y += sign(newPos.y) * boomStrength;
			newPos.z += sign(newPos.z) * boomStrength;
	}
	// assume boomLocation is (0,0,maxZ/2)
	if(ticks < boomTick + boomDuration && ticks > boomTick) {
		
		/*
		float boomSpan = float(boomDuration)/float(ticks - boomTick);

		float boomDistance = length(newPos - center);
		float maxDistance = length(cornerPt - center);

		float normD = boomDistance / maxDistance;

		if( .8 * boomSpan > normD && 1.4 * boomSpan < normD) {
			newPos.x += sign(newPos.x) * boomStrength;
			newPos.y += sign(newPos.y) * boomStrength;
			newPos.z += sign(newPos.z) * boomStrength;
		}
		*/

	}


	//colorVarying = vec4(float(id) / count, 1-float(id)/float(count), 1.0, 1.0);

	colorVarying = vec4(mix(color1, color2, float(id)/float(count)));
	texCoordVarying = vec2(position.x, position.y);

	gl_Position = projectionMatrix * modelViewMatrix * newPos;

}