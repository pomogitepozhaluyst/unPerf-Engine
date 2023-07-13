class Camera {
public:



	Vec3 pos;
	Vec3 direction = Vec3(0.0f, 0.0f, -1.0f);
	Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
	sf::Vector2i prevPos ;
	sf::Vector2i curPos ;
	sf::Vector2i localPos ;
	Mat4 matPV;
	float w;
	float h;
	bool firstClick = true;
	Light light;
	float speed = 0.05f;
	float sens = 0.1f;
	float fov = 45.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	Camera(float width, float height, Vec3 pos1, Vec3 dir = Vec3(0.0f, 0.0f, -1.0f), float fov1 = 45.0f) {
		pos = pos1;
		w = width;
		h = height;
		light = Light('s', pos);
		direction = dir;
		fov = fov1;
	}




	void look() {
		
		matPV =Perspective(fov, static_cast<float>(w / h), nearPlane, farPlane) * LookAt(pos, pos + direction, up);

	}

	

	void move(sf::RenderWindow *window, sf::Event &windowEvent, bool *cursor) {
		Vec3 right = CrossProduct(direction, Vec3(0, 1, 0)).Normalize();
		up = CrossProduct(right, direction).Normalize();

			
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
				break;
			}
			
			default:
				break;
			}


			if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			{
				*cursor = true;
				window->setMouseCursorVisible(false);
				sf::Vector2u tmp = window->getSize();
				tmp.x /= 2;
				tmp.y /= 2;
				if (firstClick) {
					localPos = sf::Mouse::getPosition(*window);
					firstClick = false;
					sf::Mouse::setPosition(sf::Vector2i(tmp.x, tmp.y), *window);
					curPos = sf::Mouse::getPosition(*window);

				}
				prevPos = curPos;

				curPos = sf::Mouse::getPosition(*window);
				float rotX = sens * (curPos.x - prevPos.x);
				float rotY = sens * (curPos.y - prevPos.y);

				Vec3 newDir = QRotation(direction, CrossProduct(direction, up), -rotY);
				if (newDir.y < 0.95f && newDir.y > -0.95f)
				{
					direction = newDir;
				}
				direction = QRotation(direction, up, -rotX);

				sf::Mouse::setPosition(sf::Vector2i(tmp.x, tmp.y), *window);
				curPos = sf::Mouse::getPosition(*window);

			}
			else if (sf::Event::MouseButtonReleased){
				if (windowEvent.key.code == sf::Mouse::Middle) {
					firstClick = true;
					sf::Mouse::setPosition(localPos, *window);
					*cursor = false;
				}
		}
			light.direction = direction;
			light.pos = pos;
	}
};