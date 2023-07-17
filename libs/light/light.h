#pragma once
class Light{
public:
	Vec3 direction;
	float intens;
	char type;
	bool debug = true;

	Transform transform = Transform();

	Light() {

		direction = Vec3(0.0f, 0.0f, -1.0f);
		type = 'p';
		intens = 1.0f;
	}
};









