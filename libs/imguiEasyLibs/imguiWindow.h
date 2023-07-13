#pragma once

struct Combo
{
	std::string name;
	std::vector<string> items;

	// обновляет состояние
	Combo(string name1, vector<string> data, int *current_item) {
		name = name1;
		items = data;
		update(current_item);
	}
	bool update(int *current_item)
	{
		// колбэк для ImGui::Combo
		auto get_item = [](void* data, int idx, const char** text) noexcept -> bool
		{
			*text = static_cast<Combo*>(data)->items[idx].c_str();
			return true;
		};
		return ImGui::Combo(name.c_str(), current_item, get_item, this, items.size());
	}
};

class ImguiWindow{
public:
	ImguiWindow() {};
	const char* imHuiAttribute[7] = { "Camera", "Cube", "Sphere", "Plane", "Model", "Light", "All Object"};
	const char* lightType[3] = { "p", "d", "s"};
	const char* layout[4] = { "0", "1", "2", "3" };
	int  numAttribute = 0;
	int  numAttributeLight = 0;
	int  numLayout = 0;
	bool cumeraFreeMove = false;
	char inputField[100] = "";
	char pathModel[100] = "";
	char texturePath[100] = "";
	char localTexturePath[100] = "";
	char localNormaMapPath[100] = "";
	char normaMapPath[100] = "";
	char parallaxMapPath[100] = "";
	int currentObject = 0;
	int currentMeshes = 0;
	bool addLight = false;
	int lightNums = 0;
	bool lightView = false;
	bool hideMenuMeshes = false;
	bool showMaterial = false;



	void create(sf::RenderWindow &window) {
		ImGui::SFML::Init(window);
	}
	void close();


	void event();

	void beginRender(const char* text) {
		ImGui::Begin(text);
	}

	void render(sf::RenderWindow &window) {
		ImGui::SFML::Render(window);
	}
	
	void endRender() {
		ImGui::End();
	}
	
	void update(sf::RenderWindow &window, sf::Clock *clock) {
		ImGui::SFML::Update(window, clock->restart());
	}

	void shotDown() {
		ImGui::SFML::Shutdown();
	}
	
	void dragFloat3(Vec3  *v, const char* text = "tmp", float speed = 0.1f) {
		ImGui::DragFloat3(text, reinterpret_cast<float*>(v), speed);
	}

	void dragFloat4(Vec4* v, const char* text = "tmp", float speed = 0.1f) {
		ImGui::DragFloat4(text, reinterpret_cast<float*>(v), speed);
	}
	void dragFloat2(Vec2* v, const char* text = "tmp", float speed = 0.1f) {
		ImGui::DragFloat2(text, reinterpret_cast<float*>(v), speed);
	}
	void dragFloat(float *v, const char* text = "tmp", float speed = 0.1f) {
		ImGui::DragFloat(text, v, speed);
	}

	Vec3 tmpPos = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 tmpSize3 = Vec3(1.0f, 1.0f, 1.0f);
	float tmpSize1 = 0.0f;
	Vec4 tmpSize4 = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Vec3 tmpColorLight = Vec3(1.0f, 1.0f, 1.0f);
	Vec2 tmpSize2 = Vec2(1.0f, 1.0f);
	Vec3 tmpRot= Vec3(0.0f, 1.0f, 1.0f);

	void basicWindow(ObjectManager *manager, sf::RenderWindow *window, sf::Clock *clock) {
		beginRender("Window");
		if (!addLight) {
			ImGui::Combo("object", &numAttribute, imHuiAttribute, IM_ARRAYSIZE(imHuiAttribute));
			switch (numAttribute)
			{
			case 0: {
				vector<string> camersName;
				for (int i = 0; i < manager->camers.size(); i++) {
					camersName.push_back("camera" + to_string(i));
				}

				Combo("active Camera", camersName, &manager->mainCamera);

				dragFloat3(&manager->camers[manager->mainCamera].pos, "camera position");
				dragFloat3(&manager->camers[manager->mainCamera].direction, "camera direction");

				ImGui::Checkbox("flashlight", &manager->camers[manager->mainCamera].light.isOn);
				dragFloat(&manager->camers[manager->mainCamera].light.intens, "lightIntens");
				dragFloat(&manager->camers[manager->mainCamera].speed, "speed");
				dragFloat(&manager->camers[manager->mainCamera].fov, "fov (default: 45)");
				dragFloat(&manager->camers[manager->mainCamera].nearPlane, "near plane");
				dragFloat(&manager->camers[manager->mainCamera].farPlane, "far plane");

				if (ImGui::Button("add camera")){
					manager->addCamera(manager->camers[manager->mainCamera].pos, manager->camers[manager->mainCamera].direction, manager->camers[manager->mainCamera].fov);
				}	
				if (manager->camers.size() > 1) {
					if (ImGui::Button("delete camera")) {
						manager->camers.erase(manager->camers.begin() + manager->mainCamera);
						manager->mainCamera = 0;
					}
				}

				break;

			}
			case 1:
			{
				ImGui::InputText("Name", inputField, IM_ARRAYSIZE(inputField));
				dragFloat3(&tmpPos, "position");
				dragFloat3(new Vec3(tmpRot.x, tmpRot.y, tmpRot.z), "rotation");
				dragFloat3(&tmpSize3, "size");
				if (ImGui::Button("add cube"))
				{
					manager->addCube(inputField, (unsigned)numLayout, tmpPos, tmpRot, tmpSize3);
				}
				break;
			}
			case 2:
			{
				ImGui::InputText("Name", inputField, sizeof(inputField));

				dragFloat3(&tmpPos, "position");
				dragFloat3(&tmpSize3, "size");
				if (tmpRot == Vec3(0.0f, 0.0f, 0.0f)) {
					tmpRot = Vec3(1.0f, 1.0f, 1.0f);
				}
				dragFloat3(&tmpRot, "rotation");
				if (ImGui::Button("add sphere"))
				{

					manager->addSphere(inputField, (unsigned)numLayout, tmpPos, tmpRot, tmpSize3);
				}
				break;

			}
			case 3:
			{
				ImGui::InputText("Name", inputField, sizeof(inputField));

				dragFloat3(&tmpPos, "position");
				dragFloat2(&tmpSize2, "size");
				if (tmpRot == Vec3(0.0f, 0.0f, 0.0f)) {
					tmpRot = Vec3(1.0f, 1.0f, 1.0f);
				}
				dragFloat3(&tmpRot, "rotation");
				if (ImGui::Button("add sphere"))
				{
					manager->addPlane(inputField, (unsigned)numLayout, tmpPos, tmpRot, tmpSize2);
				}
				break;

			}
			case 4:
			{
				ImGui::InputText("Name", inputField, sizeof(inputField));
				ImGui::InputText("Path Model", pathModel, sizeof(pathModel));

				dragFloat3(&tmpPos, "position");
				dragFloat3(&tmpSize3, "size");
				if (tmpRot == Vec3(0.0f, 0.0f, 0.0f)) {
					tmpRot = Vec3(1.0f, 1.0f, 1.0f);
				}
				dragFloat3(&tmpRot, "rotation");
				if (ImGui::Button("add model"))
				{

					manager->addModel(pathModel, inputField, (unsigned)numLayout, tmpPos, tmpRot, tmpSize3);
				}
				break;

			}
			case 5: {
				dragFloat3(&tmpPos, "position");
				if (tmpRot == Vec3(0.0f, 0.0f, 0.0f)) {
					tmpRot = Vec3(1.0f, 1.0f, 1.0f);
				}
				if (lightType != 0) {
					dragFloat3(&tmpColorLight, "direction");
				}
				dragFloat3(&tmpColorLight, "colorL");

				ImGui::Combo("type", &numAttributeLight, lightType, IM_ARRAYSIZE(lightType));

				if (ImGui::Button("add light"))
				{
					manager->addLight("", (unsigned)numLayout, tmpPos, tmpRot, *lightType[numAttributeLight],  tmpColorLight);
				}
				break;
			}


			case 6:
			{
				if (manager->object.size() > 0 && manager->object[0].size() > 0) {
					Combo("all object", manager->objectName[0], &currentObject);
					

					if (manager->object[0][currentObject]->type != 'l') {
						
						if (manager->object[0][currentObject]->type == 'm') {
							ImGui::InputText("Path Model", pathModel, sizeof(pathModel));
							if (ImGui::Button("update model"))
							{

								manager->object[0][currentObject] = new ModelObj(pathModel, inputField, manager->globalId++, (unsigned)numLayout, tmpSize3, tmpPos, tmpRot);
							}
						}
						
						dragFloat3(&manager->object[0][currentObject]->translate, "position");
						dragFloat3(&manager->object[0][currentObject]->rotation, "rotation");
						dragFloat3(&manager->object[0][currentObject]->scale, "scale");
						dragFloat4(&manager->object[0][currentObject]->color, "color");

						vector<string> nameMesh;

						ImGui::Dummy(ImVec2(0.0f, 20.0f));

						if (manager->object[0][currentObject]->mesh.size() > 1 ) {
							for (int i = 0; i < manager->object[0][currentObject]->mesh.size(); i++) {
								nameMesh.push_back("mesh" + to_string(i));
							}

							Combo("meshes", nameMesh, &currentMeshes); 						
							ImGui::SameLine();
							ImGui::Checkbox("show meshes", &hideMenuMeshes);
							if (hideMenuMeshes) {

								dragFloat3(&manager->object[0][currentObject]->mesh[currentMeshes].localPos, "local position");
								dragFloat3(&manager->object[0][currentObject]->mesh[currentMeshes].localRot, "local rotation");
								dragFloat3(&manager->object[0][currentObject]->mesh[currentMeshes].localScale, "local scale");
								dragFloat4(&manager->object[0][currentObject]->mesh[currentMeshes].localColor, "local color");

								ImGui::InputText("texture path", localTexturePath, IM_ARRAYSIZE(localTexturePath));
								if (ImGui::Button("add/update texture"))
								{
									manager->object[0][currentObject]->mesh[currentMeshes].updateTex(localTexturePath);
								}
								if (manager->object[0][currentObject]->mesh[currentMeshes].isStatusLoadDTex) {

									ImGui::Checkbox("use diffuse map", &manager->object[0][currentObject]->mesh[currentMeshes].isDTex);
									if (ImGui::Button("delete diffuse texture"))
									{
										manager->object[0][currentObject]->mesh[currentMeshes].deleteDifMap();
									}
								}

								ImGui::InputText("normalMap path", localNormaMapPath, IM_ARRAYSIZE(localNormaMapPath));
								if (ImGui::Button("add/update normalMap"))
								{
									manager->object[0][currentObject]->mesh[currentMeshes].updateNormal(localNormaMapPath);
								}

							}
							if (manager->object[0][currentObject]->mesh[currentMeshes].isStatusLoadNTex) {

								ImGui::Checkbox("use normal map", &manager->object[0][currentObject]->mesh[currentMeshes].isNTex);
								if (ImGui::Button("delete normal texture"))
								{
									manager->object[0][currentObject]->mesh[currentMeshes].deleteNormMap();

								}
							}

								ImGui::InputText("parallaxMap path (all meshes)", parallaxMapPath, IM_ARRAYSIZE(parallaxMapPath));
								if (ImGui::Button("add/update parallaxMap"))
								{
									manager->object[0][currentObject]->updateParallaxTexture(parallaxMapPath);
								}

								if (manager->object[0][currentObject]->mesh[currentMeshes].isStatusLoadPTex) {
									dragFloat(&manager->object[0][currentObject]->mesh[currentMeshes].heightScale, "height scale");
									ImGui::SameLine();
									ImGui::Checkbox("use parallax map", &manager->object[0][currentObject]->mesh[currentMeshes].isPTex);
									if (ImGui::Button("delete parallax texture"))
									{
										manager->object[0][currentObject]->mesh[currentMeshes].deleteParallaxMap();
									}
								}
						}
						ImGui::Dummy(ImVec2(0.0f, 20.0f));
						ImGui::Checkbox("show Material", &showMaterial);
						if (showMaterial) {
							dragFloat3(&manager->object[0][currentObject]->mesh[currentMeshes].material.ambient, "ambient");
							dragFloat3(&manager->object[0][currentObject]->mesh[currentMeshes].material.diffuse, "diffuse");
							dragFloat3(&manager->object[0][currentObject]->mesh[currentMeshes].material.specular, "specular");
							dragFloat(&manager->object[0][currentObject]->mesh[currentMeshes].material.shinines, "shininess");
						}

					}

					ImGui::Dummy(ImVec2(0.0f, 20.0f));

					if (!manager->object[0][currentObject]->light.empty()) {


						vector<string> tmpNums;
						for (int j = 0; j < manager->object[0][currentObject]->light.size(); j++) {
							tmpNums.push_back(to_string(j));
						}
						if (lightNums >= manager->object[0][currentObject]->light.size()) {
							lightNums = 0;
						}
						Combo("lights", tmpNums, &lightNums);
						ImGui::SameLine();
						ImGui::Checkbox("show light", &lightView);

						if (lightView) {
							if (manager->object[0][currentObject]->light[lightNums]->type != 'd') {
								dragFloat3(&manager->object[0][currentObject]->light[lightNums]->pos, "positionL");
							}
							dragFloat3(&manager->object[0][currentObject]->light[lightNums]->colorDif, "colorL");
							if (manager->object[0][currentObject]->light[lightNums]->type != 'p') {
								dragFloat3(&manager->object[0][currentObject]->light[lightNums]->direction, "directionL");
							}



							dragFloat(&manager->object[0][currentObject]->light[lightNums]->intens, "intensiveL");
							ImGui::Checkbox("isOn", &manager->object[0][currentObject]->light[lightNums]->isOn);
							ImGui::Checkbox("debug", &manager->object[0][currentObject]->light[lightNums]->debug);
							if (manager->object[0][currentObject]->light[lightNums]->type == 'p') {
								numAttributeLight = 0;
							}
							else if (manager->object[0][currentObject]->light[lightNums]->type == 'd') {
								numAttributeLight = 1;
							}
							else if (manager->object[0][currentObject]->light[lightNums]->type == 's') {
								numAttributeLight = 2;
							}

							ImGui::Combo("type", &numAttributeLight, lightType, IM_ARRAYSIZE(lightType));
							manager->object[0][currentObject]->light[lightNums]->type = lightType[numAttributeLight][0];
							if (ImGui::Button("delete Light"))
							{
								manager->object[0][currentObject]->light.erase(manager->object[0][currentObject]->light.begin() + lightNums);
							}
						}
					}

					if (ImGui::Button("add Light"))
					{
						addLight = true;
						break;

					}

					ImGui::Dummy(ImVec2(0.0f, 40.0f));

					if (manager->object[0][currentObject]->type != 'l') {

						ImGui::InputText("texture path (all meshes)", texturePath, IM_ARRAYSIZE(texturePath));
						if (ImGui::Button("add/update texture (all meshes)"))
						{
							manager->object[0][currentObject]->updateTexture(texturePath);
						}
						if (manager->object[0][currentObject]->mesh[currentMeshes].isStatusLoadDTex) {

							if (ImGui::Button("enable/disable diffuse map"))
							{
								manager->object[0][currentObject]->enDisDMap();

							}
							ImGui::SameLine();

							if (ImGui::Button("delete diffuse texture"))
							{
								manager->object[0][currentObject]->deleteDMap();

							}
						}


						ImGui::InputText("normalMap path (all meshes)", normaMapPath, IM_ARRAYSIZE(normaMapPath));
						if (ImGui::Button("add/update normalMap (all meshes)"))
						{
							manager->object[0][currentObject]->updateNormalTexture(normaMapPath);
						}
						if (manager->object[0][currentObject]->mesh[currentMeshes].isStatusLoadNTex) {

							if (ImGui::Button("enable/disable normal map"))
							{
								manager->object[0][currentObject]->enDisNMap();

							}
							ImGui::SameLine();

							if (ImGui::Button("delete normal texture (all meshes)"))
							{
								manager->object[0][currentObject]->deleteNMap();

							}
						}
							ImGui::InputText("parallaxMap path (all meshes)", parallaxMapPath, IM_ARRAYSIZE(parallaxMapPath));
							if (ImGui::Button("add/update parallaxMap (all meshes)"))
							{
								manager->object[0][currentObject]->updateParallaxTexture(parallaxMapPath);
							}

							if (manager->object[0][currentObject]->mesh[currentMeshes].isStatusLoadPTex) {
								dragFloat(&manager->object[0][currentObject]->heightScale, "height scale (all meshes)");
								if (manager->object[0][currentObject]->mesh.size() == 1) {
									manager->object[0][currentObject]->mesh[0].heightScale = manager->object[0][currentObject]->heightScale;
								}
								if (ImGui::Button("enable/disable parallax map"))
								{
									manager->object[0][currentObject]->enDisPMap();

								}
								ImGui::SameLine();

								if (ImGui::Button("delete parallax texture (all meshes)"))
								{
									manager->object[0][currentObject]->deletePMap();

								}
							}

					}

					if (ImGui::Button("delete"))
					{
						manager->deleteObject(0, currentObject);
						if (manager->object.size() != 0) {
							currentObject = 0;
						}
						else {
							numAttribute = 0;
							currentObject = 0;

						}
					}
					break;
				}
				else {
					ImGui::Text("add models");
				}
			}

			default: {
				//ImGui::Combo("layout", &numLayout, layout, IM_ARRAYSIZE(layout));
			}
			}
		}
		else {
			if (ImGui::Button("back"))
			{
				addLight = false;
			}
			dragFloat3(&tmpPos, "position");
			dragFloat3(&tmpColorLight, "color");
			if (lightType != 0) {
				dragFloat3(&tmpSize3, "direction");
			}
			dragFloat(&tmpSize1, "intensive");
			ImGui::Combo("type", &numAttributeLight, lightType, IM_ARRAYSIZE(lightType));

			if (ImGui::Button("add light"))
			{
				addLight = false;
				manager->object[0][currentObject]->addLight(*lightType[numAttributeLight], tmpPos, tmpColorLight, tmpSize3, tmpSize1);
			}
		}
		endRender();



	}

}; 

