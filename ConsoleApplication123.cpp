#include <iostream>
#include<../json/json.h>

static bool isGo = true;
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
#include <../light/light.h>
#include <../vertex/vertex.h>

#include <../Shader/vbo.h>
#include <../Shader/ebo.h>
#include <../Shader/vao.h>

#include <../Shader/shader.h>
#include <../oGLReq/cumera.h>
#include <../textures/textures.h>
#include <../mesh/mesh.h>
#include <../object/object.h>



#include <../imguiEasyLibs/imguiWindow.h>

using namespace std;
constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

int main() {
	sf::ContextSettings settings;
	settings.depthBits = 24; // количество битов буффера глубины
	settings.stencilBits = 8; //количество битов буфера трафарета
	settings.majorVersion = 4;
	settings.minorVersion = 6;
	

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT, 32), "Window", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	window.setActive();

	glewExperimental = GL_TRUE; // включить все современные функции ogl

	if (GLEW_OK != glewInit()) { // включить glew
		cout << "Error:: glew not init =(" << endl;
		return -1;
	}

	//bool isGo = true;

	sf::Clock clock;
	float speed = 0.1f;
	bool cursor = false;

	Camera camera = Camera(WIDTH, HEIGHT, Vec3(0.0f, 0.0f, -1.0f));
	

	ImguiWindow img = ImguiWindow();
	img.create(window);

	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_DEPTH_TEST);


	glShadeModel(GL_SMOOTH);
	//glLight(GL_DIFFUSE);
	ObjectManager manager = ObjectManager(vector<Camera>(1, camera));
	manager.light.insert(pair<int, Light*>(123, &camera.light));
	//manager.loadLight();
	//manager.shaders["default"].Activate();

	while (isGo) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //отчистка экрана
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sf::Event windowEvent;


		auto dtclock = clock.restart();
		float delta = dtclock.asMilliseconds();

		//update imgui
		img.update(window, &clock);
		if (cursor) {
			ImGui::SetMouseCursor(ImGuiMouseCursor_None);

		}
			glEnable(GL_DEPTH_TEST);
			//glShadeModel(GL_SMOOTH);

			//begin imgui 
			img.basicWindow(&manager, &camera, &window, &clock);
			//end imgui



		manager.update(camera);

		while (window.pollEvent(windowEvent)) { // обработка ивентов

			ImGui::SFML::ProcessEvent(windowEvent);
			camera.move(&window, windowEvent, &cursor);
		}


		


		img.render(window);

		window.display();

	}
	
	manager.Delete();
	//shaderProgram.Delete();
	window.close();
	img.shotDown();
	//shoutdown

	return 0;
}

//int main() {
//	string vCode = get_file_contents("C:/openGL/ConsoleApplication123/Resources/Shader/default.vert");
//	const char* vSourse = vCode.c_str();
//	cout << vSourse;
//}
//
//int main() {
//	glm::vec3 front;
//	glm::vec3 right;
//	front.x = cos(50 * rad) * cos(70 * rad);
//	front.y = sin(70 * rad);
//	front.z = sin(50 * rad) * cos(70 * rad);
//	front = glm::normalize(front);
//	right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
//	glm::vec3 up = glm::normalize(glm::cross(right, front));
//
//	glm::mat4 view = glm::mat4(glm::vec4(1,2,1, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1));
//	glm::mat4 view2 = glm::mat4(glm::vec4(7, 2, 2, 2), glm::vec4(3, 2, 2, 2), glm::vec4(2, 2, 1, 2), glm::vec4(2, 2, 2, 2));
//	view *= view2;
//	//cout << v1.x<<' ' << v1.y << ' ' << v1.z <<  '\n';
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++)
//			cout << view[i][j]<< ' ';
//		cout << '\n';
//	}
//
//	cout << '\n';
//
//	Vec3 front1;
//	Vec3 right1;
//	front1.x = cos(50 * rad) * cos(70 * rad);
//	front1.y = sin(70 * rad);
//	front1.z = sin(50 * rad) * cos(70 * rad);
//	front1 = front1.Normalize();
//	right1 = CrossProduct(front1, Vec3(0, 1, 0)).Normalize();
//	Vec3 up1 = CrossProduct(right1, front1).Normalize();
//
//	Mat4 view1 = Mat4(1);
//	view1.matrix[0][1] = 2;
//	Mat4 view3 = Mat4(2);
//	view3.matrix[1][0] = 3;
//	view3.matrix[2][2] = 1;
//	view3.matrix[0][0] = 7;
//
//	
//
//
//
//
//	view1 = view1*view3;
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++)
//			cout << view1.matrix[i][j] << ' ';
//		cout << '\n';
//	}
//}