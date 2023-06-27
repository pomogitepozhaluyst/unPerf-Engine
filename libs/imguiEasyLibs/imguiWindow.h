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
	const char* imHuiAttribute[6] = { "Camera", "Cube", "Sphere", "Plane", "Light", "All Object"};
	const char* lightType[3] = { "p", "d", "s"};
	const char* layout[4] = { "0", "1", "2", "3" };
	int  numAttribute = 0;
	int  numAttributeLight = 0;
	int  numLayout = 0;
	bool cumeraFreeMove = false;
	char inputField[100] = "";
	char texturePath[100] = "";
	char normaMapPath[100] = "";
	int currentObject = 0;
	bool addLight = false;
	int lightNums = 0;
	bool lightView = false;

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
	Vec2 tmpSize2 = Vec2(1.0f, 1.0f);
	Vec4 tmpRot= Vec4(0.0f, 1.0f, 1.0f, 1.0f);

	void basicWindow(ObjectManager *manager, Camera *camera, sf::RenderWindow *window, sf::Clock *clock) {
		beginRender("Window");
		if (!addLight) {
			ImGui::Combo("object", &numAttribute, imHuiAttribute, IM_ARRAYSIZE(imHuiAttribute));
			switch (numAttribute)
			{
			case 0: {

				dragFloat3(&camera->pos, "cumera position");

				ImGui::Checkbox("flashlight", &camera->light.isOn);
				dragFloat(&camera->light.intens, "lightIntens");

				break;


			}
			case 1:
			{
				ImGui::InputText("Name", inputField, IM_ARRAYSIZE(inputField));
				dragFloat3(&tmpPos, "position");
				dragFloat3(new Vec3(tmpRot.a, tmpRot.v.x, tmpRot.v.y), "rotation");
				dragFloat3(&tmpSize3, "size");
				//if (tmpRot.v == Vec3(0.0f, 0.0f, 0.0f)) {
				//	tmpRot.v = Vec3(1.0f, 1.0f, 1.0f);
				//}

				dragFloat3(&tmpPos, "position Light");
				//if (tmpRot.v == Vec3(0.0f, 0.0f, 0.0f)) {
				//	tmpRot.v = Vec3(1.0f, 1.0f, 1.0f);
				//}

				if (lightType != 0) {
					dragFloat4(&tmpRot, "direction Light");
				}

				ImGui::Combo("type", &numAttributeLight, lightType, IM_ARRAYSIZE(lightType));





				if (ImGui::Button("add cube"))
				{
					auto tmpStr = inputField;
					manager->addCube((unsigned)numLayout, tmpPos, tmpRot, tmpSize3, tmpStr);
				}
				break;
			}
			case 2:
			{
				ImGui::InputText("Name", inputField, sizeof(inputField));

				dragFloat3(&tmpPos, "position");
				dragFloat3(&tmpSize3, "size");
				if (tmpRot.v == Vec3(0.0f, 0.0f, 0.0f)) {
					tmpRot.v = Vec3(1.0f, 1.0f, 1.0f);
				}
				dragFloat4(&tmpRot, "rotation");
				if (ImGui::Button("add sphere"))
				{

					manager->addSphere((unsigned)numLayout, tmpPos, tmpRot, tmpSize3, inputField);
				}
				break;

			}
			case 3:
			{
				ImGui::InputText("Name", inputField, sizeof(inputField));

				dragFloat3(&tmpPos, "position");
				dragFloat2(&tmpSize2, "size");
				if (tmpRot.v == Vec3(0.0f, 0.0f, 0.0f)) {
					tmpRot.v = Vec3(1.0f, 1.0f, 1.0f);
				}
				dragFloat4(&tmpRot, "rotation");
				if (ImGui::Button("add sphere"))
				{
					manager->addPlane((unsigned)numLayout, tmpPos, tmpRot, tmpSize2, inputField);
				}
				break;

			}

			case 4: {
				dragFloat3(&tmpPos, "position");
				if (tmpRot.v == Vec3(0.0f, 0.0f, 0.0f)) {
					tmpRot.v = Vec3(1.0f, 1.0f, 1.0f);
				}
				dragFloat4(&tmpRot, "direction");
				ImGui::Combo("type", &numAttributeLight, lightType, IM_ARRAYSIZE(lightType));

				if (ImGui::Button("add light"))
				{
					cout << lightType[numAttributeLight] << endl;
					manager->addLight((unsigned)numLayout, tmpPos, tmpRot, *lightType[numAttributeLight], inputField);
				}
				break;
			}


			case 5:
			{

				//ImGui::Combo("all object", &currentObject, tmp12, IM_ARRAYSIZE(tmp12));
				Combo("all object", manager->objectName[0], &currentObject);
				dragFloat3(&manager->object[0][currentObject]->translate, "position");
				dragFloat4(&manager->object[0][currentObject]->rotation, "rotation");
				dragFloat3(&manager->object[0][currentObject]->scale, "scale");
				dragFloat4(&manager->object[0][currentObject]->color, "color");
				//dragFloat3(&manager->object[0][currentObject]->light.pos, "lightPos(local)");
				//dragFloat4(&manager->object[0][currentObject]->light.colorDif, "colorLight");
				//dragFloat(&manager->object[0][currentObject]->light.intens, "lightIntens");

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
						dragFloat3(&manager->object[0][currentObject]->light[lightNums]->pos, "positionL");
						dragFloat4(&manager->object[0][currentObject]->light[lightNums]->colorDif, "colorL");

						dragFloat3(&manager->object[0][currentObject]->light[lightNums]->direction, "directionL");
						dragFloat(&manager->object[0][currentObject]->light[lightNums]->intens, "intensiveL");
						ImGui::Checkbox("isOn", &manager->object[0][currentObject]->light[lightNums]->isOn);
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
					//cout << manager->object[0][currentObject]->light[lightNums]->type<<endl;
				}

				if (ImGui::Button("add Light"))
				{
					addLight = true;
					break;
					//addLight(window, clock);
					//manager->object[0][currentObject]->light.push_back(addLightWindow());
					//manager->object[0][currentObject]->updateTexture(texturePath);
				}


				ImGui::InputText("texture path", texturePath, IM_ARRAYSIZE(texturePath));
				if (ImGui::Button("add/update texture"))
				{
					manager->object[0][currentObject]->updateTexture(texturePath);
				}

				ImGui::InputText("normalMap path", normaMapPath, IM_ARRAYSIZE(normaMapPath));
				if (ImGui::Button("add/update normalMap"))
				{
					manager->object[0][currentObject]->updateNormalTexture(normaMapPath);
				}

				if (ImGui::Button("delete"))
				{
					manager->deleteObject(0, currentObject);
				}
				break;
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
			dragFloat4(&tmpSize4, "color");

			dragFloat3(&tmpSize3, "direction");
			dragFloat(&tmpSize1, "intensive");
			ImGui::Combo("type", &numAttributeLight, lightType, IM_ARRAYSIZE(lightType));

			if (ImGui::Button("add light"))
			{
				addLight = false;

				//cout << lightType[numAttributeLight] << endl;
				manager->object[0][currentObject]->addLight(*lightType[numAttributeLight], tmpPos, tmpSize4, tmpSize3, tmpSize1);
				//manager->addLight((unsigned)numLayout, tmpPos, tmpRot, lightType[numAttributeLight], inputField);
			}
		}
		endRender();



	}

}; 

