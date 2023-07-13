#pragma once
class Light {
public:
	Vec3 colorDif;
	Vec3 direction;
	float intens;
	Vec3 pos;
	char type;
	bool isOn = true;
	bool debug = true;

	Light(char type1 = 'p', Vec3 pos1 = Vec3(1.0f, 1.0f, 1.0f), Vec3 color1 = Vec3(1.0f, 1.0f, 1.0f), Vec3 direction1 = Vec3(1.0f, 1.0f, 1.0f), float intens1 = 1.0f) {
		pos = pos1;
		colorDif = color1;
		intens = intens1;
		direction = direction1;
		type = type1;
	}
};


