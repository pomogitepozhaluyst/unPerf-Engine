#pragma once

class LightComponent : public Component {
public:
	vector<Light> light;
	int currentLight = 0;
	const char* lightType[3] = { "p", "d", "s" };
	int numAttributeLight;
	Transform* parentTransform;




	LightComponent(Transform* parTrans) {
		parentTransform = parTrans;
	}

	void inImGui() {
		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		if (ImGui::CollapsingHeader("light")) {

			vector<string> tmpNums;
			for (int j = 0; j < light.size(); j++) {
				tmpNums.push_back(to_string(j));
			}
			Combo("lights", tmpNums, &currentLight);


			if (ImGui::Button("add Light"))
			{
				light.push_back(Light());
			}
			if (light.size() != 0) {
				if (light[currentLight].type != 'd') {
					dragFloat3(&light[currentLight].transform.pos, "positionL");
				}
				dragFloat4(&light[currentLight].transform.color, "colorL");
				if (light[currentLight].type != 'p') {
					dragFloat3(&light[currentLight].transform.rotation, "directionL");
				}



				dragFloat(&light[currentLight].intens, "intensiveL");
				ImGui::Checkbox("isOn", &light[currentLight].transform.isOn);
				if (light[currentLight].type != 'd') {
					ImGui::Checkbox("debug", &light[currentLight].debug);
				}
				if (light[currentLight].type == 'p') {
					numAttributeLight = 0;
				}
				else if (light[currentLight].type == 'd') {
					numAttributeLight = 1;
				}
				else if (light[currentLight].type == 's') {
					numAttributeLight = 2;
				}

				ImGui::Combo("type", &numAttributeLight, lightType, IM_ARRAYSIZE(lightType));
				light[currentLight].type = lightType[numAttributeLight][0];
				if (ImGui::Button("delete Light"))
				{
					light.erase(light.begin() + currentLight);
				}
			}
		}

	}



	void update(map<string, Shader> shaders, sf::Event windowEvent) {
		parentTransform->updateMarixRotation();

		for (int y = 0; y < light.size(); y++) {
			if (light[y].transform.isOn) {
				shaders["default"].Activate();

				float type = 0.0f;

				if (light[y].type == 'd') {
					type = 1.0f;
				}
				else if (light[y].type == 's') {
					type = 2.0f;
				}

				Transform resultTransform = parentTransform->getTransformMesh(light[y].transform);
				string tmp = "gPointLights[" + to_string(countLight) + "].pos";
				glUniform3f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), resultTransform.pos.x, resultTransform.pos.y, resultTransform.pos.z);
				Vec3 dir2;
				if (parentTransform->localRotation) {
					dir2 = QRotationX(light[y].direction, parentTransform->rotation.x + light[y].transform.rotation.x);
					dir2 = QRotationY(dir2, parentTransform->rotation.y + light[y].transform.rotation.y);
					dir2 = QRotationZ(dir2, parentTransform->rotation.z + light[y].transform.rotation.z);
				}
				else {
					dir2 = resultTransform.matRotation * light[y].direction;
				}
				tmp = "gPointLights[" + to_string(countLight) + "].direction";
				glUniform3f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), dir2.x, dir2.y, dir2.z);

				tmp = "gPointLights[" + to_string(countLight) + "].color";
				glUniform3f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), resultTransform.color.a, resultTransform.color.v.x, resultTransform.color.v.y);
				tmp = "gPointLights[" + to_string(countLight) + "].intens";
				glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), light[y].intens);


				tmp = "gPointLights[" + to_string(countLight) + "].type";
				glUniform1f(glGetUniformLocation(shaders["default"].id, tmp.c_str()), type);

				if (light[y].debug && light[y].transform.isOn && type != 1.0f) {
					shaders["lightDebug"].Activate();
					Cube().mesh.drawCubeLight(shaders["lightDebug"],
						camers[mainCamera]->matPV, Transform(resultTransform.pos, Vec3(), Vec3(light[y].intens, light[y].intens, light[y].intens) / 5.0f, resultTransform.color));

				}

				countLight++;
			}
		}
		shaders["default"].Activate();

	}
};
