#pragma once



class ImguiWindow{
public:
	ImguiWindow() {};
	const char* imHuiAttribute[4] = { "main camera", "add object", "all object", "general" }; 
	
	const char* addComponent[4] = { "Light Component", "Camera Component", "Input Event Component", "Mesh Component" };

	int  currentAddComponent = 0;

	

	int  numAttribute = 0;
	int  numAttributeLight = 0;
	int  numLayout = 0;
	char inputField[256] = "";
	char skyboxPath[256] = "";

	bool addLight = false;
	int lightNums = 0;
	bool lightView = false;

	Transform addObjectTransform;

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
	Vec3 tmpColorLight = Vec3(1.0f, 1.0f, 1.0f);


	void basicWindow(ObjectManager *manager, sf::RenderWindow *window, sf::Clock *clock, sf::Event* windowEvent, int* currentObject) {
		beginRender("Window");
			ImGui::Combo("object", &numAttribute, imHuiAttribute, IM_ARRAYSIZE(imHuiAttribute));
			switch (numAttribute)
			{
			case 0: {
				dragFloat3(&camers[mainCamera]->transform.pos, "camera position");
				dragFloat3(&camers[mainCamera]->transform.rotation, "camera rotation");
				dragFloat(&camers[mainCamera]->fov, "fov (default: 45)");
				dragFloat(&camers[mainCamera]->nearPlane, "near plane");
				dragFloat(&camers[mainCamera]->farPlane, "far plane");
				break;

			}
			case 1:
			{
				ImGui::InputText("Name", inputField, IM_ARRAYSIZE(inputField));
				addObjectTransform.inImGui();
				if (ImGui::Button("add empty Object"))
				{
					manager->addObject(inputField, (unsigned)numLayout, addObjectTransform);
				}		

				break;
			}


			case 2:
			{
				if (manager->object.size() > 0 && manager->object.size() > 0) {
					Combo("all object", manager->objectName, currentObject);
					ImGui::PushID(1);
					manager->object[*currentObject]->transform.inImGui();
					ImGui::PopID();

					for (std::map<int, Component*>::iterator it = manager->object[*currentObject]->component.begin(); it != manager->object[*currentObject]->component.end(); ++it) {
						it->second->inImGui();
						ImGui::PushID(it->first + 2);

						if (*currentObject != 0 || it->first != 1) {
							if (ImGui::Button("delete component"))
							{
								printf("%d", it->first);

								it->second->onDelete();
								manager->object[*currentObject]->component.erase(it->first);

							}
						}
						ImGui::PopID();

					}
					ImGui::Dummy(ImVec2(0.0f, 40.0f));

					ImGui::Combo("select add component", &currentAddComponent, addComponent, IM_ARRAYSIZE(addComponent));
					if (ImGui::Button("add component"))
					{
						switch (currentAddComponent)
						{
						case 0: {
							manager->object[*currentObject]->component.insert(std::pair<int, Component*>{ 2, new LightComponent(&manager->object[*currentObject]->transform)});
							break;
						}
						case 1: {
							manager->object[*currentObject]->component.insert(std::pair<int, Component*>{ 1, new CameraComponent(&manager->object[*currentObject]->transform)});
							break;
						}
						case 2: {
							manager->object[*currentObject]->component.insert(std::pair<int, Component*>{ 0, new InputComponent(window, &manager->object[*currentObject]->transform)});
							break;
						}
						case 3: {
							manager->object[*currentObject]->component.insert(std::pair<int, Component*>{ 3, new MeshComponent(&manager->object[*currentObject]->transform)});
							break;
						}
						default:
							break;
						}
					}

					if (*currentObject != 0) {
						if (ImGui::Button("delete"))
						{
							manager->deleteObject(*currentObject);
	
							*currentObject = 0;

						}
					}
				}
				break;
			}

			case 3: {
				ImGui::InputText("skybox path", skyboxPath, IM_ARRAYSIZE(skyboxPath));

				if (ImGui::Button("update skybox")) {
					manager->updateSkyBox(skyboxPath);
				}
				if (manager->skyBox.mesh.isStatusLoadDTex) {
					ImGui::Checkbox("active skybox", &manager->skyBox.mesh.isDTex);
				}
			}

			default: {
				break;
			}
			}

		endRender();



	}

}; 

