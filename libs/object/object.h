#pragma once



class Object {
public:
	vector<Mesh> mesh;
	Vec4 color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//Vec4 light = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vector<Light*> light;
	Mat3 matRotation;
	int layout;
	int id;
	int globalId;
	Vec3 scale;
	Vec3 translate = Vec3(0,0,0);
	Vec4 rotation;
	Object() = default;

	virtual void draw(Shader shaderProgram, Camera& camera, map<int, Light*> lightV) {
		for (int i = 0; i < mesh.size(); i++) {
			matRotation = QRotationMat(Vec3(1.0f, 0.0f, 0.0f), rotation.a)* QRotationMat(Vec3(0.0f, 1.0f, 0.0f), rotation.v.x);
			matRotation = matRotation*QRotationMat(Vec3(0.0f, 0.0f, 1.0f), rotation.v.y);
			mesh[i].draw(shaderProgram, camera, translate, matRotation, scale, color, lightV);
		}
	}

	void addLight(char type1, Vec3 pos1, Vec4 col1, Vec3 dir1, float inten1) {
		light.push_back(new Light(type1, pos1, col1, dir1, inten1));
	}

	void updateTexture(const char* path) {
		for (int i = 0; i < mesh.size(); i++) {
			mesh[i].updateTex(path);
		}
	}

	void updateNormalTexture(const char* path) {
		for (int i = 0; i < mesh.size(); i++) {
			mesh[i].updateNormal(path);
		}
	}
};

#include<model.h>

class Cube : public Object {
public:
	Cube(int globalId1, int layout1, int id1, Vec3 s, Vec3 t, Vec4 r, const char* texture = "C:/textuesOGL/brick/diffuse.jpg", const char* normal = "") {

		layout = layout1;
		globalId = globalId1;
		id = id1;
		translate = t;
		rotation = r;
		scale = s;


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
			/*
			//top
			Vertex(Vec3(-1.0f,1.0f,-1.0f), Vec2(0.0f,0.0f), Vec3(0.0f, 1.0f, 0.0f)),
			Vertex(Vec3(1.0f,1.0f,1.0f),  Vec2(1.0f,1.0f), Vec3(0.0f, 1.0f, 0.0f)),
			Vertex(Vec3(-1.0f,1.0f,1.0f),  Vec2(0.0f,1.0f), Vec3(0.0f, 1.0f, 0.0f)),
			Vertex(Vec3(1.0f,1.0f,-1.0f),  Vec2(1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f)),

			//bottom
			Vertex(Vec3(-1.0f,-1.0f, -1.0f), Vec2(0.0f,0.0f), Vec3(0.0f, -1.0f, 0.0f)),
			Vertex(Vec3(1.0f,-1.0f, -1.0f), Vec2(1.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f)),
			Vertex(Vec3(-1.0f, -1.0f, 1.0f), Vec2(0.0f,1.0f), Vec3(0.0f, -1.0f, 0.0f)),
			Vertex(Vec3(1.0f, -1.0f, 1.0f), Vec2(1.0f, 1.0f), Vec3(0.0f, -1.0f, 0.0f)),

			//left
			Vertex(Vec3(1.0f,-1.0f,1.0f), Vec2(1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-1.0f,-1.0f,1.0f), Vec2(0.0f,0.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(1.0f,1.0f,1.0f), Vec2(1.0f,1.0f), Vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-1.0f,1.0f,1.0f), Vec2(0.0f,1.0f), Vec3(-1.0f, 0.0f, 0.0f)),

			//right

			Vertex(Vec3(1.0f,-1.0f,-1.0f), Vec2(1.0f,0.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(1.0f, 1.0f, -1.0f), Vec2(1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-1.0f, -1.0f, -1.0f), Vec2(0.0f,0.0f), Vec3(1.0f, 0.0f, 0.0f)),
			Vertex(Vec3(-1.0f, 1.0f, -1.0f), Vec2(0.0f,1.0f), Vec3(1.0f, 0.0f, 0.0f)),
			
			//front
			Vertex(Vec3(1.0f,-1.0f,-1.0f), Vec2(1.0f,0.0f), Vec3(0.0f, 0.0f, -1.0f)),
			Vertex(Vec3(1.0f, -1.0f, 1.0f), Vec2(1.0f, 1.0f), Vec3(0.0f, 0.0f, -1.0f)),
			Vertex(Vec3(1.0f, 1.0f, -1.0f), Vec2(0.0f,0.0f), Vec3(0.0f, 0.0f, -1.0f)),
			Vertex(Vec3(1.0f, 1.0f, 1.0f), Vec2(0.0f,1.0f), Vec3(0.0f, 0.0f, -1.0f)),

			//back
			Vertex(Vec3(-1.0f,-1.0f,-1.0f), Vec2(1.0f,0.0f), Vec3(0.0f, 0.0f, 1.0f)),
			Vertex(Vec3(-1.0f, -1.0f, 1.0f), Vec2(1.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f)),
			Vertex(Vec3(-1.0f, 1.0f, -1.0f), Vec2(0.0f,0.0f), Vec3(0.0f, 0.0f, 1.0f)),
			Vertex(Vec3(-1.0f, 1.0f, 1.0f), Vec2(0.0f,1.0f), Vec3(0.0f, 0.0f, 1.0f)),
			*/

			//Vertex(Vec3(-1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)),
			//Vertex(Vec3(-1.0f, 1.0f, -1.0f), Vec2(1.0f, 0.0f)),
			//Vertex(Vec3(1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)),
			//Vertex(Vec3(1.0f, 1.0f, -1.0f), Vec2(0.0f, 0.0f)),
		};
		vector<unsigned> indes;
		for (int i = 0; i < 36; i++) {
			indes.push_back(i);
		}
		/*vector<unsigned> indes = {
			//Top


			0, 1, 2,
			1, 0, 3,

			4, 5, 6,
			5, 6, 7,

			8, 9, 10,
			9, 10, 11,

			12, 13, 14,
			13, 14, 15,

			16, 17, 18,
			17, 18, 19,

			20, 21, 22,
			21, 22, 23



		};*/
		if (texture == "") {
			texture = "C:/textuesOGL/brick/diffuse.jpg";
		}


		mesh.push_back(Mesh(verts, indes, texture, normal));
	}

};

class Plane : public Object {
public:
	Plane(int globalId1, int layout1, int id1, Vec2 s, Vec3 t, Vec4 r, const char* texture = "C:/textuesOGL/brick/diffuse.jpg", const char* normal = "") {
		//objMat = Mat4().E() * matTranslate(t) * ( QRotationMat(r.v, r.a) * Mat4(s.x,1.0f, s.y,1.0f ));
		id = id1;
		layout = layout1;

		translate = t;
		rotation = r;
		scale = Vec3(s.x,1.0f,s.y);
		globalId = globalId1;

		vector<Vertex> verts = {

			Vertex(Vec3(-1.0f,0.0f,-1.0f), Vec2(0.0f,0.0f)),
			Vertex(Vec3(1.0f,0.0f,1.0f), Vec2(1.0f,1.0f)),
			Vertex(Vec3(-1.0f,0.0f,1.0f), Vec2(0.0f,1.0f)),
			Vertex(Vec3(1.0f,0.0f,-1.0f), Vec2(1.0f,0.0f)),

		};

		vector<unsigned> indes = {
			//Top
			0,1,2,
			1,0,3,
		};
		if (texture == "") {
			texture = "C:/textuesOGL/brick/diffuse.jpg";
		}

		mesh.push_back( Mesh(verts, indes, texture, normal));
	}


};

class Sphere : public Object {
public:
	Sphere(int globalId1, int layout1, int id1, Vec3 s, Vec3 t, Vec4 r, const char* texture = "C:/glModels/sphere/textures/football.jpg") {
		layout = layout1;
		globalId = globalId1;

		id = id1;
		translate = t;
		rotation = r;
		scale = s;
		Model model = Model("C:/glModels/sphere/untitled.gltf", "C:/textuesOGL/brick/diffuse.jpg");

		mesh = model.mesh;
	}

};


class LightObj: public Object {
public:
	Vec3 oldDir;
	Mat3 dir;
	LightObj(int globalId1, int layout1, int id1, Vec3 t, Vec4 r, char type = 'p', Vec4 colorL = Vec4(1.0f, 1.0f, 1.0f, 1.0f)) {
		globalId = globalId1;

		id = id1;
		layout = layout1;
		//light = Light(type, t);
		dir = MRotationX3(r.a) * MRotationY3(r.v.x);
		dir = dir * MRotationZ3(r.v.y);

		light.push_back(new Light(type, t, colorL, (dir * Vec3(1.0f, 1.0f, 1.0f))));

		
		rotation = r;
	}



	void draw(Shader shaderProgram, Camera& camera, map<int, Light*> lightV)  {
		dir = MRotationX3(rotation.a) * MRotationY3(rotation.v.x);
		dir = dir * MRotationZ3(rotation.v.y);
		light[0]->direction = dir * Vec3(1.0f, 1.0f, 1.0f);
		//cout << light[0]->direction << endl;
		//cout << light.direction << endl;
	}




};

class ObjectManager {
public:
	vector<vector<Object*>> object;
	vector<Camera> camers;
	vector<vector<string>> objectName;
	map<int, Light*> light;
	int globalId = 0;

	map<string, Shader> shaders = { {"default", Shader("C:/openGL/ConsoleApplication123/Resources/Shader/default.vert",
			"C:/openGL/ConsoleApplication123/Resources/Shader/default.frag")},
	};

	ObjectManager(vector<Camera> v) {
		camers=v;


	}

	void addCube(unsigned layout = 0u, Vec3 t = Vec3(0.0f, 0.0f, 0.0f),  Vec4 r = Vec4(0.0f, 0.0f, 0.0f, 0.0f), Vec3 s = Vec3(1.0f, 1.0f, 1.0f), string name2 = "Cube") {
		if (object.size() <= layout) {
			object.resize(layout+1u);
			objectName.resize(layout + 1u);
		}
		
		object[layout].push_back(new Cube(globalId++, layout, object[layout].size(), s, t, r));

		objectName[layout].push_back(name2);

		//light.push_back(&object[layout][object[layout].size() - 1]->light);
		//light.insert(pair<int, Light*>(object[layout][object[layout].size() - 1]->globalId, &object[layout][object[layout].size() - 1]->light));

	}

	void addLight(unsigned layout = 0u, Vec3 t = Vec3(0.0f, 0.0f, 0.0f), Vec4 r = Vec4(0.0f, 0.0f, 0.0f, 0.0f), char type = 'p', string name2 = "Light") {
		if (object.size() <= layout) {
			object.resize(layout + 1u);
			objectName.resize(layout + 1u);
		}
		object[layout].push_back(new LightObj(globalId++, layout, object[layout].size(), t, r, type));

		objectName[layout].push_back(name2);

		//light.insert(pair<int, Light*>(object[layout][object[layout].size() - 1]->globalId, &object[layout][object[layout].size() - 1]->light));
	}

	void addPlane(unsigned layout = 0u, Vec3 t = Vec3(0.0f, 0.0f, 0.0f), Vec4 r = Vec4(0.0f, 0.0f, 0.0f, 0.0f), Vec2 s = Vec2(1.0f, 1.0f), string name2 = "Plane") {
		if (object.size() <= layout) {
			object.resize(layout + 1u);
			objectName.resize(layout + 1u);
		}
		object[layout].push_back(new Plane(globalId++, layout, object[layout].size(), s, t, r));
		objectName[layout].push_back(name2);

		//light.insert(pair<int, Light*>(object[layout][object[layout].size() - 1]->globalId, &object[layout][object[layout].size() - 1]->light));



	}

	void addSphere(unsigned layout = 0, Vec3 t = Vec3(0.0f, 0.0f, 0.0f), Vec4 r = Vec4(0.0f, 0.0f, 0.0f, 0.0f), Vec3 s = Vec3(1.0f, 1.0f, 1.0f), string name2 = "Sphere") {
		if (object.size() <= layout) {
			object.resize(layout + 1u);
			objectName.resize(layout + 1u);
		}
		objectName[layout].push_back(name2);

		object[layout].push_back(new Sphere(globalId++, layout, object[layout].size(), s, t, r));

		//light.insert(pair<int, Light*>(object[layout][object[layout].size() - 1]->globalId, &object[layout][object[layout].size() - 1]->light));


	}

	void updateLaout(unsigned layout, Camera camera) {

		for (int i = 0; i < object[layout].size(); i++) {
			//object[layout][i]->draw(shaders["default"], camera, light);

		}

	}

	void update( Camera camera) {
		camera.look(45.0f, 0.1f, 100.0f, "matPV");
		//loadLight();
		float type = 0;
		int k = 0;
		shaders["default"].Activate();

		for (int i = 0; i < object.size(); i++) {
			for (int j = 0; j < object[i].size(); j++) {
				for (int y = 0; y < object[i][j]->light.size(); y++) {


					if (object[i][j]->light[y]->type == 'd') {
						type = 1.0f;
					}
					else if (object[i][j]->light[y]->type == 's') {
						type = 2.0f;
					}


					string tmp = "gPointLights[" + to_string(k) + "].pos";
					glUniform3f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), object[i][j]->light[y]->pos.x, object[i][j]->light[y]->pos.y, object[i][j]->light[y]->pos.z);
					tmp = "gPointLights[" + to_string(k) + "].direction";
					glUniform3f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), object[i][j]->light[y]->direction.x, object[i][j]->light[y]->direction.y, object[i][j]->light[y]->direction.z);

					tmp = "gPointLights[" + to_string(k) + "].color";
					glUniform4f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), object[i][j]->light[y]->colorDif.a, object[i][j]->light[y]->colorDif.v.x, object[i][j]->light[y]->colorDif.v.y, object[i][j]->light[y]->colorDif.v.z);
					tmp = "gPointLights[" + to_string(k) + "].intens";
					glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), object[i][j]->light[y]->intens);
					tmp = "gPointLights[" + to_string(k) + "].isOn";
					glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), object[i][j]->light[y]->isOn);

					tmp = "gPointLights[" + to_string(k) + "].type";
					glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), type);
					k++;
				}
			}
		}
		
		string tmp = "gPointLights[" + to_string(k) + "].pos";
		glUniform3f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), camera.light.pos.x, camera.light.pos.y, camera.light.pos.z);
		tmp = "gPointLights[" + to_string(k) + "].direction";
		glUniform3f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), camera.light.direction.x, camera.light.direction.y, camera.light.direction.z);

		tmp = "gPointLights[" + to_string(k) + "].color";
		glUniform4f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), camera.light.colorDif.a, camera.light.colorDif.v.x, camera.light.colorDif.v.y, camera.light.colorDif.v.z);
		tmp = "gPointLights[" + to_string(k) + "].intens";
		glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), camera.light.intens);
		tmp = "gPointLights[" + to_string(k) + "].isOn";
		glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), camera.light.isOn);

		tmp = "gPointLights[" + to_string(k) + "].type";
		glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), 2.0f);
		k++;
		glUniform1f(glGetUniformLocation(shaders["default"].id, "lightCount"), k);


		for (int i = 0; i < object.size(); i++) {
			for (int j = 0; j < object[i].size(); j++) {
				object[i][j]->draw(shaders["default"], camera, light);
			}
		}

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

