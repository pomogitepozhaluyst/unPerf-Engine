#pragma once



class MeshComponent : public Component {
public:
	vector<Mesh*> mesh;
	Transform* parentTransform;
	const char* addMeshes[4] = { "Cube", "Sphere", "Plane", "Model" };
	int  currentAddMeshes = 0;
	int currentMeshes = 0;
	char pathModel[256] = "";

	char texturePath[256] = "";
	char normaMapPath[256] = "";
	char parallaxMapPath[256] = "";




	MeshComponent(Transform* parTrans) {
		parentTransform = parTrans;

	}
	void update(map<string, Shader> shaders, sf::Event windowEvent) {

		for (int i = 0; i < mesh.size(); i++) {
			if (mesh[i]->localTransform.isOn) {
				mesh[i]->draw(shaders["default"], *camers[mainCamera], *parentTransform);
			}
		}
	}
	void addCubeMesh() {

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
		mesh.push_back(new Mesh(verts, indes));
	}

	void addPlaneMesh() {

		vector<Vertex> verts = {

			Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f, 1.0f)),
			Vertex(Vec3(0.5f, -0.5f, -0.5f),  Vec2(1.0f,  0.0f), Vec3(0.0f,  0.0f, 1.0f)),
			Vertex(Vec3(0.5f,  0.5f, -0.5f),  Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f, 1.0f)),
			Vertex(Vec3(0.5f,  0.5f, -0.5f),  Vec2(1.0f,  1.0f), Vec3(0.0f,  0.0f, 1.0f)),
			Vertex(Vec3(-0.5f,  0.5f, -0.5f),  Vec2(0.0f,  1.0f), Vec3(0.0f,  0.0f, 1.0f)),
			Vertex(Vec3(-0.5f, -0.5f, -0.5f),  Vec2(0.0f,  0.0f), Vec3(0.0f,  0.0f, 1.0f)),

		};

		vector<unsigned> indes = {
			0,1,2,
			3, 4, 5
		};
		mesh.push_back(new Mesh(verts, indes));

	}

	void addSphereMesh() {

		Model* model = new  Model("Resources/sphere/untitled.gltf");

		mesh.push_back(&model->mesh[0]);

	}


	void addModelMesh(string path) {

		Model* model = new Model(path.c_str());


		for (int i = 0; i < model->mesh.size(); i++) {
			mesh.push_back(&model->mesh[i]);
		}

	}

	void inImGui() {

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		if (ImGui::CollapsingHeader("mesh")) {

			ImGui::Combo("select meshes", &currentAddMeshes, addMeshes, IM_ARRAYSIZE(addMeshes));


			if (currentAddMeshes == 3) {
				ImGui::InputText("Path Model", pathModel, sizeof(pathModel));

			}
			if (ImGui::Button("add meshes"))
			{
				switch (currentAddMeshes)
				{
				case 0: {
					addCubeMesh();

					break;
				}
				case 1: {
					addSphereMesh();

					break;
				}
				case 2: {
					addPlaneMesh();

					break;
				}
				case 3: {
					addModelMesh(pathModel);

					break;
				}
				default:
					break;
				}
			}

			vector<string> nameMesh;

			ImGui::Dummy(ImVec2(0.0f, 10.0f));

			if (mesh.size() != 0) {
				if (currentMeshes > mesh.size() - 1) {
					currentMeshes = 0;
				}
				for (int i = 0; i < mesh.size(); i++) {
					nameMesh.push_back("mesh" + to_string(i));
				}

				Combo("meshes", nameMesh, &currentMeshes);

				ImGui::PushID(2);

				dragFloat3(&mesh[currentMeshes]->localTransform.pos, "position");
				dragFloat3(&mesh[currentMeshes]->localTransform.rotation, "rotation");
				dragFloat3(&mesh[currentMeshes]->localTransform.scale, "size");
				dragFloat4(&mesh[currentMeshes]->localTransform.color, "color");

				ImGui::PopID();

				ImGui::InputText("texture path", texturePath, IM_ARRAYSIZE(texturePath));
				if (ImGui::Button("add/update texture"))
				{
					mesh[currentMeshes]->updateTex(texturePath);
				}
				if (mesh[currentMeshes]->isStatusLoadDTex) {
					dragFloat2(&mesh[currentMeshes]->textureOffset, "texturePos");

					ImGui::Checkbox("use diffuse map", &mesh[currentMeshes]->isDTex);
					if (ImGui::Button("delete diffuse texture"))
					{
						mesh[currentMeshes]->deleteDifMap();
					}
				}

				ImGui::InputText("normal map path", normaMapPath, IM_ARRAYSIZE(normaMapPath));
				if (ImGui::Button("add/update normalMap"))
				{
					mesh[currentMeshes]->updateNormal(normaMapPath);
				}

				if (mesh[currentMeshes]->isStatusLoadNTex) {

					ImGui::Checkbox("use normal map", &mesh[currentMeshes]->isNTex);
					if (ImGui::Button("delete normal texture"))
					{
						mesh[currentMeshes]->deleteNormMap();

					}
				}
				if (mesh[currentMeshes]->isStatusLoadDTex && mesh[currentMeshes]->isDTex) {

					ImGui::InputText("parallax map path", parallaxMapPath, IM_ARRAYSIZE(parallaxMapPath));

					if (ImGui::Button("add/update parallaxMap"))
					{
						mesh[currentMeshes]->updateParallax(parallaxMapPath);
					}


					if (mesh[currentMeshes]->isStatusLoadPTex) {
						dragFloat(&mesh[currentMeshes]->heightScale, "height scale");
						ImGui::Checkbox("use parallax map", &mesh[currentMeshes]->isPTex);
						if (ImGui::Button("delete parallax texture"))
						{
							mesh[currentMeshes]->deleteParallaxMap();
						}
					}
				}

				ImGui::Dummy(ImVec2(0.0f, 10.0f));
				if (ImGui::CollapsingHeader("material")) {
					dragFloat3(&mesh[currentMeshes]->material.ambient, "ambient");
					dragFloat3(&mesh[currentMeshes]->material.diffuse, "diffuse");
					dragFloat3(&mesh[currentMeshes]->material.specular, "specular");
					dragFloat(&mesh[currentMeshes]->material.shinines, "shininess");
				}

				if (ImGui::Button("delete mesh"))
				{
					mesh.erase(mesh.begin() + currentMeshes);
					currentMeshes = 0;
				}
			}
		}


	}
};
