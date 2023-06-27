class Camera {
public:
	Vec3 pos;
	Vec3 direction = Vec3(0.0f, 0.0f, -1.0f);
	Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
	Vec3 right;
	sf::Vector2i prevPos ;
	sf::Vector2i curPos ;
	sf::Vector2i localPos ;
	Mat4 matPV;
	float w;
	float h;
	bool firstClick = true;
	Light light;
	float speed = 0.1f;


	Camera(float width, float height, Vec3 pos1) {
		pos = pos1;
		w = width;
		h = height;
		light = Light('s', pos);

	}




	void look(float fov, float nearPlane, float farPlane,  const char* uniform) {
		

		//glUniformMatrix4fv(glGetUniformLocation(shaderId, uniform), 1, GL_FALSE, &matPV.matrix[0][0]);
		
		 matPV =Perspective(45.0f, static_cast<float>(w / h), 0.1f, 100.0f) * LookAt(pos, pos + direction, up);



	}

	

	void move(sf::RenderWindow *window, sf::Event &windowEvent, bool *cursor) {
		Vec3 right = CrossProduct(direction, Vec3(0, 1, 0)).Normalize();
		up = CrossProduct(right, direction).Normalize();

		// обработка ивентов
			
			switch (windowEvent.type)
			{
			case sf::Event::Closed:
				isGo = false;
				break;
			case sf::Event::KeyPressed: {
				if (windowEvent.key.code == sf::Keyboard::W) {
					pos += direction * (speed);
				}
				if (windowEvent.key.code == sf::Keyboard::S) {
					pos -= direction * (speed);
				}
				if (windowEvent.key.code == sf::Keyboard::D) {
					pos += CrossProduct(direction, up).Normalize() * (speed);
				}
				if (windowEvent.key.code == sf::Keyboard::A) {
					pos -= CrossProduct(direction, up).Normalize() * (speed);
				}
				if (windowEvent.key.code == sf::Keyboard::Space) {
					pos += up * (speed);
				}
				if (windowEvent.key.code == sf::Keyboard::X) {
					pos -= up * (speed);
				}
				if (windowEvent.key.code == sf::Keyboard::LShift) {
					speed = 0.4f;
				}

				break;
			}
			
			default:
				break;
			}


			if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			{
				//ImGui::SetMouseCursor(ImGuiMouseCursor_None);
				*cursor = true;
				window->setMouseCursorVisible(false);
				sf::Vector2u tmp = window->getSize();
				tmp.x /= 2;
				tmp.y /= 2;
				// left click...
				if (firstClick) {
					localPos = sf::Mouse::getPosition(*window);
					firstClick = false;
					sf::Mouse::setPosition(sf::Vector2i(tmp.x, tmp.y), *window);
					curPos = sf::Mouse::getPosition(*window);

				}
					prevPos = curPos;
				// sf::Vector2i(tmp.x, tmp.y); //curPos;// sf::Vector2i(tmp.x, tmp.y);

				curPos =  sf::Mouse::getPosition(*window);
				curPos = curPos;
				float rotX = speed * (float)(curPos.x - prevPos.x);//sens * (float)(curPos.y - (h / 2)) / h;
				float rotY = speed * (float)(curPos.y - prevPos.y);//sens * (float)(curPos.x - (w / 2)) / w;
				if (rotX != 0.0f && rotY != 0.0f) {
					direction = QRotation(direction, CrossProduct(direction, up), -rotY);
					direction = QRotation(direction, up, -rotX);
				}
				//window->setMouseCursorVisible(false);

				//direction = direction;

			/*	auto dxy = curPos - prevPos;

				yaw = static_cast<float>(dxy.x) * speed;
				pitch = static_cast<float>(-dxy.y) * speed;

				if (pitch > 89.0f) {
					pitch = 89.0f;
				}
				if (pitch < -89.0f) {
					pitch = -89.0f;
				}

				direction.x = cos(rad * yaw) * cos(rad * pitch);
				direction.y = sin(rad * pitch);
				direction.z = sin(rad * yaw) * cos(rad * pitch);
				direction = direction.Normalize();

				up = CrossProduct(CrossProduct(direction, Vec3(0.0f, 1.0f, 0.0f)).Normalize(), direction).Normalize();
				*/
				//sf::Mouse::setPosition(sf::Vector2i(tmp.x, tmp.y), window);

			}
			else if (sf::Event::MouseButtonReleased){
				if (windowEvent.key.code == sf::Mouse::Middle) {
					firstClick = true;
					sf::Mouse::setPosition(localPos, *window);
					//window->setMouseCursorVisible(true);
					//ImGui::SetMouseCursor(true);
					*cursor = false;

				}


			


	/*		else if (sf::Event::MouseButtonReleased) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					firstClick = true;
				}
			}

			*/
			//pos += direction;
			//cout << angle();
			//direction = QRotation(direction, CrossProduct(direction, up).Normalize(), -rotX);
			//direction = glm::rotate(direction,  glm::radians( - rotY), up);

			

		}
			light.direction = direction;
			light.pos = pos;
		//cout << pos<<'\n';
	}
};