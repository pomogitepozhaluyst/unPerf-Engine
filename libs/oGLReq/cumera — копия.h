class Cumera {
public:
	Vec3 pos;
	Vec3 direction = Vec3(0.0f, 0.0f, -1.0f);
	Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
	sf::Vector2i prevPos;
	sf::Vector2i curPos;
	float w;
	float h;

	float speed = 0.1f;
	float sens = 10.0f;


	Cumera(float width, float height, Vec3 pos1) {
		pos = pos1;
		w = width;
		h = height;
	}

	void look(float fov, float nearPlane, float farPlane, int shaderId, const char* uniform) {
		

		//glUniformMatrix4fv(glGetUniformLocation(shaderId, uniform), 1, GL_FALSE, &matPV.matrix[0][0]);
	
		Mat4 matPV = Perspective(45.0f, static_cast<float>(w / h), 0.0000001f, 100.0f) * LookAt(pos, pos + direction, up);

		glUniformMatrix4fv(glGetUniformLocation(shaderId, "matPV"), 1, GL_FALSE, &(matPV).matrix[0][0]);


	}

	void move(bool* isGo, sf::RenderWindow &window) {
		sf::Event windowEvent;

		/*direction.x = cos(-89.0f * rad) * cos(0.0f * rad);
		direction.y = sin(0.0f * rad);
		direction.z = sin(-89.0f * rad) * cos(0.0f * rad);*/
		Vec3 right = CrossProduct(direction, Vec3(0, 1, 0)).Normalize();
		up = CrossProduct(right, direction).Normalize();
		while (window.pollEvent(windowEvent)) { // обработка ивентов
			ImGui::SFML::ProcessEvent(windowEvent);
			switch (windowEvent.type)
			{
			case sf::Event::Closed:
				*isGo = false;
				break;
			case sf::Event::KeyPressed: {

				if (windowEvent.key.code == sf::Keyboard::W) {
					pos += direction * (speed);
					cout << "press W\n";
				}
				if (windowEvent.key.code == sf::Keyboard::S) {
					pos -= direction * (speed);
				}
				if (windowEvent.key.code == sf::Keyboard::D) {
					pos += right * (speed);
				}
				if (windowEvent.key.code == sf::Keyboard::A) {
					pos -= right * (speed);
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
			}
            
			/*case sf::Event::KeyReleased:
				if (windowEvent.key.code == sf::Keyboard::LShift) {
					speed = 0.1f;
				}*/

			break;

			default:
				break;
			}



			prevPos = curPos;
			curPos = sf::Mouse::getPosition(window);

			float rotX = sens * (float)(curPos.y - (h / 2)) / h;
			float rotY = sens * (float)(curPos.x - (w / 2)) / w;
			//float rotY = curPos.x - prevPos.x;

			Vec3 newDirection = QRotation(direction, CrossProduct(direction, up).Normalize(), -rotX);
			
			
			if (abs(angle(newDirection, up) - rad*(90.0f)) <= rad*(85.0f))
			{
				direction = newDirection;
			}
			
			direction = QRotation(direction, up.Normalize(), -rotY);

			
			//pos += direction;
			//cout << angle();
			//direction = QRotation(direction, CrossProduct(direction, up).Normalize(), -rotX);
			//direction = glm::rotate(direction,  glm::radians( - rotY), up);

			

		}

		//cout << pos<<'\n';
	}
};