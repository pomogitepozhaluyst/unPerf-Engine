#pragma once

void ToggleButton(const char* str_id, bool* v)
{
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	float height = ImGui::GetFrameHeight();
	float width = height * 1.55f;
	float radius = height * 0.50f;

	if (ImGui::InvisibleButton(str_id, ImVec2(width, height)))
		*v = !*v;
	ImU32 col_bg;
	if (ImGui::IsItemHovered())
		col_bg = *v ? IM_COL32(145 + 20, 211, 68 + 20, 255) : IM_COL32(218 - 20, 218 - 20, 218 - 20, 255);
	else
		col_bg = *v ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);

	draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
	draw_list->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
}

class InputComponent : public Component {
public:
	sf::RenderWindow* window;


	sf::Vector2i localPos;
	sf::Vector2i prevPos;
	sf::Vector2i curPos;
	Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
	bool typeInput = false;

	Transform inputTransform = Transform(Vec3(0.0, 0.0f, -1.0f));
	Transform* parentTransorm;
	bool firstClick = true;

	float speed = 1.0f;


	InputComponent(sf::RenderWindow* window1, Transform* parentTransform1) {
		window = window1;
		parentTransorm = parentTransform1;

	}

	void inImGui() {
		ImGui::Dummy(ImVec2(0.0f, 20.0f));

		if (ImGui::CollapsingHeader("input")) {
			ToggleButton("", &typeInput);
			ImGui::SameLine();
			ImGui::Text("cursor rotation/translate");
			dragFloat(&speed, "speed");
		}
	}

	void update(map<string, Shader> shaders, sf::Event windowEvent) {
		Vec3 right = CrossProduct(inputTransform.pos, up).Normalize();
		up = CrossProduct(right, inputTransform.pos).Normalize();

		switch (windowEvent.type)
		{
		case sf::Event::KeyPressed: {
			Vec3 localDirection = QRotationX(inputTransform.pos, parentTransorm->rotation.x);
			localDirection = QRotationY(localDirection, parentTransorm->rotation.y);
			localDirection = QRotationZ(localDirection, parentTransorm->rotation.z);

			if (windowEvent.key.code == sf::Keyboard::W) {

				parentTransorm->pos += localDirection * (speed / 3.0f);
			}
			if (windowEvent.key.code == sf::Keyboard::S) {
				parentTransorm->pos -= localDirection * (speed / 3.0f);
			}
			if (windowEvent.key.code == sf::Keyboard::D) {
				parentTransorm->pos += CrossProduct(localDirection, up).Normalize() * (speed/3.0f);
			}
			if (windowEvent.key.code == sf::Keyboard::A) {
				parentTransorm->pos -= CrossProduct(localDirection, up).Normalize() * (speed);
			}
			if (windowEvent.key.code == sf::Keyboard::Space) {
				parentTransorm->pos += up * (speed / 3.0f);
			}
			if (windowEvent.key.code == sf::Keyboard::X) {
				parentTransorm->pos -= up * (speed / 3.0f);
			}
			break;
		}

		default:
			break;
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		{
			ImGui::SetMouseCursor(-1);

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

			if (typeInput) {
				parentTransorm->pos.x += speed/15.0f * (curPos.x - prevPos.x);
				parentTransorm->pos.y -= speed / 15.0f * (curPos.y - prevPos.y);
			}
			else {
				parentTransorm->rotation.y -= speed / 15.0f * (curPos.x - prevPos.x);
				parentTransorm->rotation.x -= speed / 15.0f * (curPos.y - prevPos.y);
			}

			sf::Mouse::setPosition(sf::Vector2i(tmp.x, tmp.y), *window);
			curPos = sf::Mouse::getPosition(*window);

		}
		if (sf::Event::MouseButtonReleased) {
			if (windowEvent.key.code == sf::Mouse::Middle) {
				firstClick = true;
				sf::Mouse::setPosition(localPos, *window);
				ImGui::SetMouseCursor(0);

			}
		}
	}


};
