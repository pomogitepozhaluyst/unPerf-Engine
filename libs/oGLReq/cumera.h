class Camera {
public:


	Transform transform;

	Vec3 direction = Vec3(0.0f, 0.0f, -1.0f);
	Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
	sf::Vector2i prevPos ;
	sf::Vector2i curPos ;
	sf::Vector2i localPos ;
	Mat4 matPV;
	float w;
	float h;
	bool firstClick = true;
	//Light light;

	float fov = 45.0f;
	float nearPlane = 0.1f;
	float farPlane = 10000.0f;


	Transform* parentTransorm;

	Camera(float width, float height, Vec3 pos1, Transform* parentTransform1 = nullptr, Vec3 dir = Vec3(0.0f, 0.0f, -1.0f), float fov1 = 45.0f) {
		transform.pos = pos1;
		w = width;
		h = height;
		//light = Light('s', pos);
		direction = dir;
		fov = fov1;
		parentTransorm = parentTransform1;
	}




	void look() {



		if (parentTransorm) {
			parentTransorm->updateMarixRotation();


			Vec3 globalPos = parentTransorm->matRotation * transform.pos;

			if (!parentTransorm->localRotation) {
				Vec3 localDirection = QRotationX(direction, transform.rotation.x);
				localDirection = QRotationY(localDirection, transform.rotation.y);
				localDirection = QRotationZ(localDirection, transform.rotation.z);
				Vec3 localUp = QRotationX(up, transform.rotation.x);
				localUp = QRotationY(localUp, transform.rotation.y );
				localUp = QRotationZ(localUp, transform.rotation.z );
				 localUp = parentTransorm->matRotation * localUp;

				matPV = Perspective(fov, static_cast<float>(w / h), nearPlane, farPlane) * LookAt(globalPos + parentTransorm->pos, globalPos + parentTransorm->pos + parentTransorm->matRotation * localDirection, localUp);
			}
			else {
				Vec3 localDirection = QRotationX(direction, transform.rotation.x + parentTransorm->rotation.x);
				localDirection = QRotationY(localDirection, transform.rotation.y + parentTransorm->rotation.y);
				localDirection = QRotationZ(localDirection, transform.rotation.z + parentTransorm->rotation.z);

				Vec3 localUp = QRotationX(up, transform.rotation.x+ parentTransorm->rotation.x);
				localUp = QRotationY(localUp, transform.rotation.y + parentTransorm->rotation.y);
				localUp = QRotationZ(localUp, transform.rotation.z + parentTransorm->rotation.z);

				matPV = Perspective(fov, static_cast<float>(w / h), nearPlane, farPlane) * LookAt(transform.pos + parentTransorm->pos, transform.pos + parentTransorm->pos + localDirection, localUp);
			}
			//matPV = Perspective(fov, static_cast<float>(w / h), nearPlane, farPlane) * LookAt(pos + parentTransorm->pos, pos + parentTransorm->matRotation * localDirection, up);

		}
		else {
			Vec3 localDirection = QRotationX(direction, transform.rotation.x);
			localDirection = QRotationY(localDirection, transform.rotation.y);
			localDirection = QRotationZ(localDirection, transform.rotation.z);
			Vec3 localUp = QRotationX(up, transform.rotation.x);
			localUp = QRotationY(localUp, transform.rotation.y);
			localUp = QRotationZ(localUp, transform.rotation.z);

			matPV = Perspective(fov, static_cast<float>(w / h), nearPlane, farPlane) * LookAt(transform.pos, transform.pos + localDirection, (localUp));

		}
	}

	//

	//void move(sf::RenderWindow *window, sf::Event &windowEvent, bool *cursor) {
	//	Vec3 right = CrossProduct(direction, up).Normalize();
	//	up = CrossProduct(right, direction).Normalize();

	//		
	//		switch (windowEvent.type)
	//		{
	//		case sf::Event::Closed:
	//			isGo = false;
	//			break;
	//		case sf::Event::KeyPressed: {
	//			Vec3 localDirection = QRotationX(direction, transform.rotation.x);
	//			localDirection = QRotationY(localDirection, transform.rotation.y);
	//			localDirection = QRotationZ(localDirection, transform.rotation.z);
	//			if (windowEvent.key.code == sf::Keyboard::W) {
	//				transform.pos += localDirection * (speed);
	//			}
	//			if (windowEvent.key.code == sf::Keyboard::S) {
	//				transform.pos -= localDirection * (speed);
	//			}
	//			if (windowEvent.key.code == sf::Keyboard::D) {
	//				transform.pos += CrossProduct(localDirection, up).Normalize() * (speed);
	//			}
	//			if (windowEvent.key.code == sf::Keyboard::A) {
	//				transform.pos -= CrossProduct(localDirection, up).Normalize() * (speed);
	//			}
	//			if (windowEvent.key.code == sf::Keyboard::Space) {
	//				transform.pos += up * (speed);
	//			}
	//			if (windowEvent.key.code == sf::Keyboard::X) {
	//				transform.pos -= up * (speed);
	//			}
	//			break;
	//		}
	//		
	//		default:
	//			break;
	//		}


	//		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	//		{
	//			*cursor = true;
	//			window->setMouseCursorVisible(false);
	//			sf::Vector2u tmp = window->getSize();
	//			tmp.x /= 2;
	//			tmp.y /= 2;
	//			if (firstClick) {
	//				localPos = sf::Mouse::getPosition(*window);
	//				firstClick = false;
	//				sf::Mouse::setPosition(sf::Vector2i(tmp.x, tmp.y), *window);
	//				curPos = sf::Mouse::getPosition(*window);

	//			}
	//			prevPos = curPos;

	//			curPos = sf::Mouse::getPosition(*window);
	//			transform.rotation.y -= sens * (curPos.x - prevPos.x);
	//			transform.rotation.x -= sens * (curPos.y - prevPos.y);

	//			//Vec3 newDir = QRotation(direction, CrossProduct(direction, up), -rotY);
	//			////if (newDir.y < 0.95f && newDir.y > -0.95f)
	//			////{
	//			//	direction = newDir;
	//			////}
	//			//direction = QRotation(direction, up, -rotX);

	//			sf::Mouse::setPosition(sf::Vector2i(tmp.x, tmp.y), *window);
	//			curPos = sf::Mouse::getPosition(*window);

	//		}
	//		else if (sf::Event::MouseButtonReleased){
	//			if (windowEvent.key.code == sf::Mouse::Middle) {
	//				firstClick = true;
	//				sf::Mouse::setPosition(localPos, *window);
	//				*cursor = false;
	//			}
	//	}
	//	//	light.direction = direction;
	//		//light.pos = pos;
	//}
};