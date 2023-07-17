#include <iostream>
#include<../json/json.h>

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

int countLight = 0;

//glew
//#define GLEW STATIC
#include <GL/glew.h>


//sfml
#include <SFML/Window.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <../stb/stb_image.h>
#include <format>
#include <string>
#include <string_view>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <../glm/glm/glm.hpp>
#include <../glm/glm/gtc/matrix_transform.hpp>
#include <../glm/glm/gtc/type_ptr.hpp>
using namespace std;
#include <../oGLReq/klevchMath.h>
#include <../vertex/vertex.h>

#include <../Shader/vbo.h>
#include <../Shader/ebo.h>
#include <../Shader/vao.h>
#include <../Shader/shader.h>







#include <../textures/textures.h>
#include <../Component/Component.h>

#include <../Component/Transform.h>
#include <../oGLReq/cumera.h>
map<int, Camera*> camers;
int mainCamera = 0;
int idCamers = 0;
int idCurObject = 0;
#include <../Component/Camera.h>

#include <../Component/Input.h>
#include <../mesh/mesh.h>
#include <../object/object.h>
#include <../Component/Mesh.h>

#include <../light/light.h>
#include <../Component/Light.h>




#include <../object/object_manager.h>



#include <../imguiEasyLibs/imguiWindow.h>

using namespace std;


int main() {
	sf::ContextSettings settings;
	settings.depthBits = 24; // количество битов буффера глубины
	settings.stencilBits = 8; //количество битов буфера трафарета
	settings.majorVersion = 4;
	settings.minorVersion = 6;
	

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT, 32), "UnPerf Engine", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	window.setActive();

	glewExperimental = GL_TRUE; // включить все современные функции ogl

	if (GLEW_OK != glewInit()) { // включить glew
		cout << "Error:: glew not init =(" << endl;
		return -1;
	}


	sf::Clock clock;
	float speed = 0.1f;

	

	ImguiWindow img = ImguiWindow();
	img.create(window);

	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_DEPTH_TEST);


	glShadeModel(GL_SMOOTH);
	ObjectManager manager = ObjectManager(window.getSize());

	manager.addObject("default camera");
	manager.object[0]->component.insert(std::pair<int, Component*>{1, new CameraComponent(&manager.object[0]->transform, 0)});
	manager.object[0]->component.insert(std::pair<int, Component*>{0, new InputComponent(&window,  &manager.object[0]->transform)});
	camers.insert(std::pair<int, Camera*>{idCamers, new Camera(WIDTH, HEIGHT, Vec3(0.0f, 0.0f, -1.0f), &manager.object[0]->transform)});
	manager.globalId++;

	idCamers++;

	float curTime;
	bool isGo = true;

	while (isGo) {
		clock.restart();
		sf::Event windowEvent;


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //отчистка экрана
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		while (window.pollEvent(windowEvent)) { // обработка ивентов

			ImGui::SFML::ProcessEvent(windowEvent);
			;
			if (manager.object[idCurObject]->component.find(0) != manager.object[idCurObject]->component.end()) {
				manager.object[idCurObject]->component[0]->update(manager.shaders, windowEvent);
			}
		}

		switch (windowEvent.type)
		{
		case sf::Event::Closed:
			isGo = false;
			break;

		default:
			break;
		}

		img.update(window, &clock);


		glEnable(GL_DEPTH_TEST);


		img.basicWindow(&manager, &window, &clock, &windowEvent, &idCurObject);

		manager.update(windowEvent);







		img.render(window);

		window.display();

	}
	
	manager.Delete();
	window.close();
	img.shotDown();

	return 0;
}