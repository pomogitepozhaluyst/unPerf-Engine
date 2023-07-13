#pragma once



class Object {
public:
	vector<Mesh> mesh;
	Vec4 color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//Vec4 light = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vector<Light*> light;
	Mat3 matRotation = Mat3().E();
	int layout;
	int id;
	int globalId;
	Vec3 scale;
	Vec3 translate = Vec3(0,0,0);
	Vec3 rotation;
	string name;
	char type;
	float heightScale = 0.0f;

	Object() = default;

	virtual void draw(Shader shaderProgram, Camera& camera) {
		for (int i = 0; i < mesh.size(); i++) {
			matRotation = QRotationMat(Vec3(1.0f, 0.0f, 0.0f), rotation.x+ mesh[i].localRot.x) * QRotationMat(Vec3(0.0f, 1.0f, 0.0f), rotation.y + mesh[i].localRot.y);
			matRotation = matRotation*QRotationMat(Vec3(0.0f, 0.0f, 1.0f), rotation.z + mesh[i].localRot.z);
			mesh[i].draw(shaderProgram, camera, translate, matRotation, scale, color);
		}
	}

	void addLight(char type1, Vec3 pos1, Vec3 col1, Vec3 dir1, float inten1) {
		light.push_back(new Light(type1, pos1, col1, dir1, inten1));
	}

	void updateTexture(const char* path) {
		for (int i = 0; i < mesh.size(); i++) {
			mesh[i].updateTex(path);
		}
	}

	void deleteDMap() {
		for (int i = 0; i < mesh.size(); i++) {
			mesh[i].deleteDifMap();
		}
	}

	void enDisDMap() {
		for (int i = 0; i < mesh.size(); i++) {
			mesh[i].isDTex ^= 1;
		}
	}

	void updateNormalTexture(const char* path) {
		for (int i = 0; i < mesh.size(); i++) {
			mesh[i].updateNormal(path);
		}
	}

	void deleteNMap() {
		for (int i = 0; i < mesh.size(); i++) {
			mesh[i].deleteNormMap();
		}
	}
	void enDisNMap() {
		for (int i = 0; i < mesh.size(); i++) {
			mesh[i].isNTex ^= 1;
		}
	}

	void updateParallaxTexture(const char* path) {
		for (int i = 0; i < mesh.size(); i++) {
			mesh[i].updateParallax(path);
		}
	}

	void deletePMap() {
		for (int i = 0; i < mesh.size(); i++) {
			mesh[i].deleteParallaxMap();
		}
	}

	void enDisPMap() {
		for (int i = 0; i < mesh.size(); i++) {
			mesh[i].isPTex ^= 1;
		}
	}
};

#include<model.h>

class Cube : public Object {
public:
	Cube(string name2, int globalId1, int layout1, int id1, Vec3 s, Vec3 t, Vec3 r, const char* texture = "C:/textuesOGL/brick2/bricks2.jpg", const char* normal = "") {
		name = name2;
		layout = layout1;
		globalId = globalId1;
		id = id1;
		translate = t;
		rotation = r;
		scale = s;
		type = 'c';

		vector<Vertex> verts = {
			Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(0.5f, -0.5f, -0.5f),  Vec2(1.0f,  0.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(0.5f,  0.5f, -0.5f),  Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(0.5f,  0.5f, -0.5f),  Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(-0.5f,  0.5f, -0.5f),  Vec2(0.0f,  1.0f), Vec3(0.0f,  0.0f, -1.0f)),
			Vertex(Vec3(-0.5f, -0.5f, -0.5f),  Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f, -1.0f)),

			//bottom
			Vertex(Vec3(-0.5f, -0.5f,  0.5f), Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(0.5f, -0.5f,  0.5f), Vec2(1.0f,  0.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(0.5f,  0.5f,  0.5f), Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(0.5f,  0.5f,  0.5f), Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(-0.5f,  0.5f,  0.5f), Vec2(0.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f)),
			Vertex(Vec3(-0.5f, -0.5f,  0.5f), Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f,  1.0f)),

			//left
			Vertex(Vec3(-0.5f,  0.5f,  0.5f), Vec2(1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.5f,  0.5f, -0.5f), Vec2(1.0f,  1.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2(0.0f,  1.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2(0.0f,  1.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.5f, -0.5f,  0.5f), Vec2(0.0f,  0.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-0.5f,  0.5f,  0.5f), Vec2(1.0f,  0.0f), Vec3(-1.0f, 0.0f, 0.0f)),

			//right

			Vertex(Vec3(0.5f,  0.5f,  0.5f), Vec2(1.0f,  0.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.5f,  0.5f, -0.5f), Vec2(1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.5f, -0.5f, -0.5f), Vec2(0.0f,  1.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.5f, -0.5f, -0.5f), Vec2(0.0f,1.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.5f, -0.5f,  0.5f), Vec2(0.0f,  0.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(0.5f,  0.5f,  0.5f), Vec2(1.0f,  0.0f), Vec3(1.0f, 0.0f, 0.0f)),

			//front
			Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2(0.0f,  1.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(0.5f, -0.5f, -0.5f), Vec2(1.0f,  1.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(0.5f, -0.5f,  0.5f), Vec2(1.0f,  0.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(0.5f, -0.5f,  0.5f), Vec2(1.0f,  0.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(-0.5f, -0.5f,  0.5f), Vec2(0.0f,  0.0f), Vec3(0.0f, -1.0f,  0.0f)),
			Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2(0.0f,1.0f), Vec3(0.0f, -1.0f,  0.0f)),

			//back
			Vertex(Vec3(-0.5f,  0.5f, -0.5f), Vec2(0.0f,  1.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(0.5f,  0.5f, -0.5f), Vec2(1.0f, 1.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(0.5f,  0.5f,  0.5f), Vec2(1.0f,  0.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(0.5f,  0.5f,  0.5f), Vec2(1.0f,  0.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(-0.5f,  0.5f,  0.5f), Vec2(0.0f,0.0f), Vec3(0.0f,  1.0f,  0.0f)),
			Vertex(Vec3(-0.5f,  0.5f, -0.5f), Vec2(0.0f,1.0f), Vec3(0.0f,  1.0f,  0.0f)),
		

		};
		vector<unsigned> indes;
		for (int i = 0; i < 36; i++) {
			indes.push_back(i);
		}

		if (texture == "") {
			texture = "C:/textuesOGL/brick2/bricks2.jpg";
		}
		mesh.push_back(Mesh(verts, indes, texture, normal));
	}

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
		mesh.push_back(Mesh(verts, indes));
		type = 'c';
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
		mesh1.difMap = new Texture("C:/textuesOGL/skybox");
		mesh.push_back(mesh1);
		type = 'c';
	}
};

class Plane : public Object {
public:
	Plane(string name2, int globalId1, int layout1, int id1, Vec2 s, Vec3 t, Vec3 r, const char* texture = "C:/textuesOGL/brick2/bricks2.jpg", const char* normal = "") {
		//objMat = Mat4().E() * matTranslate(t) * ( QRotationMat(r.v, r.a) * Mat4(s.x,1.0f, s.y,1.0f ));
		name = name2;

		id = id1;
		layout = layout1;
		name = name2;

		translate = t;
		rotation = r;
		scale = Vec3(s.x,1.0f,s.y);
		globalId = globalId1;
		type = 'p';
		vector<Vertex> verts = {

			Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f, 1.0f)),
			Vertex(Vec3(0.5f, -0.5f, -0.5f),  Vec2(1.0f,  0.0f), Vec3(0.0f,  0.0f, 1.0f)),
			Vertex(Vec3(0.5f,  0.5f, -0.5f),  Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f, 1.0f)),
			Vertex(Vec3(0.5f,  0.5f, -0.5f),  Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f, 1.0f)),
			Vertex(Vec3(-0.5f,  0.5f, -0.5f),  Vec2(0.0f,  1.0f), Vec3(0.0f,  0.0f, 1.0f)),
			Vertex(Vec3(-0.5f, -0.5f, -0.5f),  Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f, 1.0f)),

		};

		vector<unsigned> indes = {
			//Top
			0,1,2,
			3, 4, 5
		};
		if (texture == "") {
			texture = "C:/textuesOGL/brick2/bricks2.jpg";
		}

		mesh.push_back( Mesh(verts, indes, texture, normal));
	}


};

class Sphere : public Object {
public:
	Sphere(string name2, int globalId1, int layout1, int id1, Vec3 s, Vec3 t, Vec3 r, const char* texture = "C:/textuesOGL/brick2/bricks2.jpg") {
		name = name2;

		layout = layout1;
		globalId = globalId1;
		type = 's';
		id = id1;
		translate = t;
		rotation = r;
		scale = s;
		Model model = Model("C:/glModels/sphere/untitled.gltf", "C:/textuesOGL/brick2/bricks2.jpg");

		mesh = model.mesh;
	}

};

class ModelObj : public Object {
public:

	ModelObj(string path, string name2, int globalId1, int layout1, Vec3 s, Vec3 t, Vec3 r) {
		name = name2;

		layout = layout1;
		globalId = globalId1;
		type = 'm';
		translate = t;
		rotation = r;
		scale = s;
		Model model = Model(path.c_str());

		mesh = model.mesh;
	}
};

class LightObj: public Object {
public:
	LightObj(string name2, int globalId1, int layout1, int id1, Vec3 t, Vec3 r, char type1 = 'p', Vec3 colorL = Vec3(1.0f, 1.0f, 1.0f)) {
		name = name2;

		
		globalId = globalId1;
		type = 'l';
		id = id1;
		layout = layout1;
		//dir = MRotationX3(r.x) * MRotationY3(r.y);
		//dir = dir * MRotationZ3(r.z);

		light.push_back(new Light(type1, t, colorL, r));

		
		rotation = r;
	}



	void draw(Shader shaderProgram, Camera& camera, map<int, Light*> lightV)  {

	}




};

class ObjectManager {
public:
	vector<vector<Object*>> object;
	vector<Camera> camers;
	vector<vector<string>> objectName;
	map<int, Light*> light;
	map<int, Object*> debugObject;
	sf::Vector2u windowSize;
	Cube skyBox = Cube("C:/textuesOGL/skybox");
	int globalId = 0;

	int mainCamera = 0;

	map<string, Shader> shaders = { 

		{"default", Shader("C:/openGL/ConsoleApplication123/Resources/Shader/default.vert",
			"C:/openGL/ConsoleApplication123/Resources/Shader/default.frag")},

		{"lightDebug", Shader("C:/openGL/ConsoleApplication123/Resources/Shader/light/light.vert",
			"C:/openGL/ConsoleApplication123/Resources/Shader/light/light.frag")},

		{"skyBox", Shader("C:/openGL/ConsoleApplication123/Resources/Shader/skyBox/skyBox.vert",
			"C:/openGL/ConsoleApplication123/Resources/Shader/skyBox/skyBox.frag")}
	};

	ObjectManager(vector<Camera> v, sf::Vector2u ws) {
		camers=v;
		windowSize = ws;
	}

	void addCamera(Vec3 pos, Vec3 dir, float fov) {
		camers.push_back(Camera(windowSize.x, windowSize.y, pos, dir, fov));
	}

	void addCube(string name2, unsigned layout = 0u, Vec3 t = Vec3(0.0f, 0.0f, 0.0f),  Vec3 r = Vec3(0.0f, 0.0f, 0.0f), Vec3 s = Vec3(1.0f, 1.0f, 1.0f)) {
		if (object.size() <= layout) {
			object.resize(layout+1u);
			objectName.resize(layout + 1u);
		}
		if (name2 == "") {
			name2 = "cubeId" + to_string(globalId++);
		}
		
		object[layout].push_back(new Cube(name2, globalId, layout, object[layout].size(), s, t, r));

		objectName[layout].push_back(name2);
	}

	void addLight(string name2, unsigned layout = 0u, Vec3 t = Vec3(0.0f, 0.0f, 0.0f), Vec3 r = Vec3(0.0f, 0.0f, 0.0f), char type = 'p', Vec3 colorL = Vec3(1.0f, 1.0f, 1.0f)) {
		if (object.size() <= layout) {
			object.resize(layout + 1u);
			objectName.resize(layout + 1u);
		}
		if (name2 == "") {
			name2 = "lightId" + to_string(globalId++);
		}

		object[layout].push_back(new LightObj(name2, globalId, layout, object[layout].size(), t, r, type, colorL));

		objectName[layout].push_back(name2);

		//light.insert(pair<int, Light*>(object[layout][object[layout].size() - 1]->globalId, &object[layout][object[layout].size() - 1]->light));
	}

	void addPlane(string name2, unsigned layout = 0u, Vec3 t = Vec3(0.0f, 0.0f, 0.0f), Vec3 r = Vec3(0.0f, 0.0f, 0.0f), Vec2 s = Vec2(1.0f, 1.0f)) {
		if (object.size() <= layout) {
			object.resize(layout + 1u);
			objectName.resize(layout + 1u);
		}

		if (name2 == "") {
			name2 = "planeId" + to_string(globalId++);
		}

		object[layout].push_back(new Plane(name2, globalId, layout, object[layout].size(), s, t, r));
		objectName[layout].push_back(name2);




	}

	void addSphere(string name2, unsigned layout = 0, Vec3 t = Vec3(0.0f, 0.0f, 0.0f), Vec3 r = Vec3(0.0f, 0.0f, 0.0f), Vec3 s = Vec3(1.0f, 1.0f, 1.0f)) {
		if (object.size() <= layout) {
			object.resize(layout + 1u);
			objectName.resize(layout + 1u);
		}

		if (name2 == "") {
			name2 = "sphereId" + to_string(globalId++);
		}


		object[layout].push_back(new Sphere(name2, globalId, layout, object[layout].size(), s, t, r));
		objectName[layout].push_back(name2);
	}


	void addModel(string path, string name2, unsigned layout = 0, Vec3 t = Vec3(0.0f, 0.0f, 0.0f), Vec3 r = Vec3(0.0f, 0.0f, 0.0f), Vec3 s = Vec3(1.0f, 1.0f, 1.0f)) {
		if (object.size() <= layout) {
			object.resize(layout + 1u);
			objectName.resize(layout + 1u);
		}

		if (name2 == "") {
			name2 = "modelId" + to_string(globalId++);
		}


		object[layout].push_back(new ModelObj(path, name2, globalId, layout, s, t, r));
		objectName[layout].push_back(name2);
	}


	void updateLaout(unsigned layout, Camera camera) {

		for (int i = 0; i < object[layout].size(); i++) {

		}

	}

	void update() {
		camers[mainCamera].look();
		//loadLight();
		int k = 0;

		for (int i = 0; i < object.size(); i++) {
			for (int j = 0; j < object[i].size(); j++) {
				for (int y = 0; y < object[i][j]->light.size(); y++) {
					if (object[i][j]->light[y]->isOn) {
						shaders["default"].Activate();

						float type = 0;

						if (object[i][j]->light[y]->type == 'd') {
							type = 1.0f;
						}
						else if (object[i][j]->light[y]->type == 's') {
							type = 2.0f;
						}


						string tmp = "gPointLights[" + to_string(k) + "].pos";
						glUniform3f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), object[i][j]->translate.x + object[i][j]->light[y]->pos.x, object[i][j]->translate.y + object[i][j]->light[y]->pos.y, object[i][j]->translate.z + object[i][j]->light[y]->pos.z);

						Vec3 dir2 = object[i][j]->matRotation * object[i][j]->light[y]->direction;
						tmp = "gPointLights[" + to_string(k) + "].direction";
						glUniform3f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), -dir2.x, -dir2.y, -dir2.z);

						tmp = "gPointLights[" + to_string(k) + "].color";
						glUniform3f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), object[i][j]->light[y]->colorDif.x, object[i][j]->light[y]->colorDif.y, object[i][j]->light[y]->colorDif.z);
						tmp = "gPointLights[" + to_string(k) + "].intens";
						glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), object[i][j]->light[y]->intens);
						//tmp = "gPointLights[" + to_string(k) + "].isOn";
						//glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), object[i][j]->light[y]->isOn);

						tmp = "gPointLights[" + to_string(k) + "].type";
						glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), type);

						if (object[i][j]->light[y]->debug && object[i][j]->light[y]->isOn) {
							shaders["lightDebug"].Activate();

							Cube().mesh[0].drawCubeLight(shaders["lightDebug"], 
								camers[mainCamera], object[i][j]->translate + object[i][j]->light[y]->pos, Vec3(object[i][j]->light[y]->intens, object[i][j]->light[y]->intens, object[i][j]->light[y]->intens) / 10.0f, Vec4(object[i][j]->light[y]->colorDif, 1.0f));

						}

						k++;
					}
				}
			}
		}
		shaders["default"].Activate();

		if (camers[mainCamera].light.isOn) {
			string tmp = "gPointLights[" + to_string(k) + "].pos";
			glUniform3f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), camers[mainCamera].light.pos.x, camers[mainCamera].light.pos.y, camers[mainCamera].light.pos.z);
			tmp = "gPointLights[" + to_string(k) + "].direction";
			glUniform3f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), camers[mainCamera].light.direction.x, camers[mainCamera].light.direction.y, camers[mainCamera].light.direction.z);

			tmp = "gPointLights[" + to_string(k) + "].color";
			glUniform3f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), camers[mainCamera].light.colorDif.x, camers[mainCamera].light.colorDif.y, camers[mainCamera].light.colorDif.z);
			tmp = "gPointLights[" + to_string(k) + "].intens";
			glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), camers[mainCamera].light.intens);
			//tmp = "gPointLights[" + to_string(k) + "].isOn";
			//glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), camera.light.isOn);

			tmp = "gPointLights[" + to_string(k) + "].type";
			glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), 2.0f);
			k++;
		}
		glUniform1f(glGetUniformLocation(shaders["default"].id, "lightCount"), k);


		for (int i = 0; i < object.size(); i++) {
			for (int j = 0; j < object[i].size(); j++) {
				object[i][j]->draw(shaders["default"], camers[mainCamera]);
			}
		}

		shaders["skyBox"].Activate();
		skyBox.mesh[0].drawSkyBox(shaders["skyBox"], camers[mainCamera]);
	}

	void deleteObject(int l, int i) {
		object[l].erase(object[l].begin() + i);
		objectName[l].erase(objectName[l].begin() + i);
	}


	void Delete() {
		std::vector<string> key;
		for (std::map<string, Shader>::iterator it = shaders.begin(); it != shaders.end(); ++it) {
			key.push_back(it->first);
		}
		for (int i = 0; i < key.size(); i++) {
			shaders[key[i]].Delete();
		}

	}

};

