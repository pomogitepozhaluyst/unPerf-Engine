#pragma once

#include<model.h>



class Object {
public:

	int layout;
	int id;
	int globalId;
	string name;
	char type;
	float heightScale = 0.0f;
	map<int, Component*> component;
	Transform transform;

	Object() = default;

	Object(string name1, int layout1, Transform transform1) {
		name = name1;
		layout = layout1;
		transform = transform1;
	}

};


class Cube {
public:
	Mesh mesh;

	Cube() {

		vector<Vertex> verts = {
			Vertex(Vec3(-0.05f, -0.05f, -0.05f), Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(0.05f, -0.05f, -0.05f),  Vec2(1.0f,  0.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(0.05f,  0.05f, -0.05f),  Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(0.05f,  0.05f, -0.05f),  Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(-0.05f,  0.05f, -0.05f),  Vec2(0.0f,  1.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(-0.05f, -0.05f, -0.05f),  Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f, -1.0f)),

			//bottom
			Vertex(Vec3(-0.05f, -0.05f,  0.05f), Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(0.05f, -0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(0.05f,  0.05f,  0.05f), Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(0.05f,  0.05f,  0.05f), Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(-0.05f,  0.05f,  0.05f), Vec2(0.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(-0.05f, -0.05f,  0.05f), Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f,  1.0f)),

			//left
			Vertex(Vec3(-0.05f,  0.05f,  0.05f), Vec2(1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.05f,  0.05f, -0.05f), Vec2(1.0f,  1.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.05f, -0.05f, -0.05f), Vec2(0.0f,  1.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.05f, -0.05f, -0.05f), Vec2(0.0f,  1.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.05f, -0.05f,  0.05f), Vec2(0.0f,  0.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.05f,  0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(-1.0f, 0.0f, 0.0f)),

			//right

			Vertex(Vec3(0.05f,  0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.05f,  0.05f, -0.05f), Vec2(1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.05f, -0.05f, -0.05f), Vec2(0.0f,  1.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.05f, -0.05f, -0.05f), Vec2(0.0f,1.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.05f, -0.05f,  0.05f), Vec2(0.0f,  0.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.05f,  0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(1.0f, 0.0f, 0.0f)),

			//front
			Vertex(Vec3(-0.05f, -0.05f, -0.05f), Vec2(0.0f,  1.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(0.05f, -0.05f, -0.05f), Vec2(1.0f,  1.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(0.05f, -0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(0.05f, -0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(-0.05f, -0.05f,  0.05f), Vec2(0.0f,  0.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(-0.05f, -0.05f, -0.05f), Vec2(0.0f,1.0f), Vec3(0.0f, -1.0f,  0.0f)),

			//back
			Vertex(Vec3(-0.05f,  0.05f, -0.05f), Vec2(0.0f,  1.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(0.05f,  0.05f, -0.05f), Vec2(1.0f, 1.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(0.05f,  0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(0.05f,  0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(-0.05f,  0.05f,  0.05f), Vec2(0.0f,0.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(-0.05f,  0.05f, -0.05f), Vec2(0.0f,1.0f), Vec3(0.0f,  1.0f,  0.0f)),
		};
		vector<unsigned> indes;
		for (int i = 0; i < 36; i++) {
			indes.push_back(i);
		}
		mesh = Mesh(verts, indes);
	}

	Cube(const char* texture) {

		vector<Vertex> verts = {
			Vertex(Vec3(-0.05f, -0.05f, -0.05f), Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(0.05f, -0.05f, -0.05f),  Vec2(1.0f,  0.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(0.05f,  0.05f, -0.05f),  Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(0.05f,  0.05f, -0.05f),  Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(-0.05f,  0.05f, -0.05f),  Vec2(0.0f,  1.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(-0.05f, -0.05f, -0.05f),  Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f, -1.0f)),

			//bottom
			Vertex(Vec3(-0.05f, -0.05f,  0.05f), Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(0.05f, -0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(0.05f,  0.05f,  0.05f), Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(0.05f,  0.05f,  0.05f), Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(-0.05f,  0.05f,  0.05f), Vec2(0.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(-0.05f, -0.05f,  0.05f), Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f,  1.0f)),

			//left
			Vertex(Vec3(-0.05f,  0.05f,  0.05f), Vec2(1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.05f,  0.05f, -0.05f), Vec2(1.0f,  1.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.05f, -0.05f, -0.05f), Vec2(0.0f,  1.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.05f, -0.05f, -0.05f), Vec2(0.0f,  1.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.05f, -0.05f,  0.05f), Vec2(0.0f,  0.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.05f,  0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(-1.0f, 0.0f, 0.0f)),

			//right

			Vertex(Vec3(0.05f,  0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.05f,  0.05f, -0.05f), Vec2(1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.05f, -0.05f, -0.05f), Vec2(0.0f,  1.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.05f, -0.05f, -0.05f), Vec2(0.0f,1.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.05f, -0.05f,  0.05f), Vec2(0.0f,  0.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.05f,  0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(1.0f, 0.0f, 0.0f)),

			//front
			Vertex(Vec3(-0.05f, -0.05f, -0.05f), Vec2(0.0f,  1.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(0.05f, -0.05f, -0.05f), Vec2(1.0f,  1.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(0.05f, -0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(0.05f, -0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(-0.05f, -0.05f,  0.05f), Vec2(0.0f,  0.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(-0.05f, -0.05f, -0.05f), Vec2(0.0f,1.0f), Vec3(0.0f, -1.0f,  0.0f)),

			//back
			Vertex(Vec3(-0.05f,  0.05f, -0.05f), Vec2(0.0f,  1.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(0.05f,  0.05f, -0.05f), Vec2(1.0f, 1.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(0.05f,  0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(0.05f,  0.05f,  0.05f), Vec2(1.0f,  0.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(-0.05f,  0.05f,  0.05f), Vec2(0.0f,0.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(-0.05f,  0.05f, -0.05f), Vec2(0.0f,1.0f), Vec3(0.0f,  1.0f,  0.0f)),
		};
		vector<unsigned> indes;
		for (int i = 0; i < 36; i++) {
			indes.push_back(i);
		}
		Mesh mesh1 = Mesh(verts, indes);
		mesh = mesh1;
	}
};
