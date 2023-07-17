#pragma once



class ObjectManager {
public:
	vector<Object*> object;
	
	vector<string> objectName;
	map<int, Light*> light;
	map<int, Object*> debugObject;
	sf::Vector2u windowSize;
	Cube skyBox = Cube();
	int globalId = 0;

	

	map<string, Shader> shaders = { 

		{"default", Shader("Resources/Shader/default.vert",
			"Resources/Shader/default.frag")},

		{"lightDebug", Shader("Resources/Shader/light/light.vert",
			"Resources/Shader/light/light.frag")},

		{"skyBox", Shader("Resources/Shader/skyBox/skyBox.vert",
			"Resources/Shader/skyBox/skyBox.frag")}
	};

	ObjectManager(sf::Vector2u ws) {
		windowSize = ws;
	}

	void addObject(string name2, unsigned layout = 0, Transform transform = Transform()) {


		if (name2 == "") {
			name2 = "objectId" + to_string(globalId++);
		}
		object.push_back(new Object(name2, layout, transform));
		objectName.push_back(name2);

	}
	void updateSkyBox(string path) {
		skyBox.mesh.updateSkyBox(path);
	}

	void update(sf::Event windowEvent) {
		camers[mainCamera]->look();
		//loadLight();
		shaders["default"].Activate();

		countLight = 0;
		for (int it = 1; it < 5; it++) {

			for (int i = 0; i < object.size(); i++) {

					if (it != 0 && (object[i]->component.find(it) != object[i]->component.end()) && object[i]->transform.isOn) {
						object[i]->component[it]->update(shaders, windowEvent);
						glUniform1f(glGetUniformLocation(shaders["default"].id, "lightCount"), countLight);

				}
			}

		}

	

		shaders["skyBox"].Activate();
		if (skyBox.mesh.isDTex) {
			skyBox.mesh.drawSkyBox(shaders["skyBox"], camers[mainCamera]);
		}
	}

	void deleteObject(int i) {
		object.erase(object.begin() + i);
		objectName.erase(objectName.begin() + i);
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

