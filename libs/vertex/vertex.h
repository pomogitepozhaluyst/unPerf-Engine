#pragma once
class Vertex {
public:
	Vec3 pos;
	Vec2 tex;
	Vec3 norm;
	Vec3 tan;
	Vec3 bitan;

	Vertex() = default;

	Vertex(Vec3 pos1, Vec2 tex1, Vec3 norm1 = Vec3(1.0f, 1.0f, 1.0f)) {
		pos = pos1;
		tex = tex1;
		norm = norm1;
	}
	Vertex(glm::vec3 pos1, glm::vec2 tex1) {
		pos = Vec3(pos1.x, pos1.y, pos1.z);
		tex = Vec2(tex1.x, tex1.y);
	}
};