#pragma once

class CameraComponent : public Component {
public:
	vector<int> objectCamersId;
	int currentCamera = 0;
	Transform* parentTransform;

	CameraComponent(Transform* parTrans, int addCamera = -1) {
		parentTransform = parTrans;
		if (addCamera != -1) {
			objectCamersId.push_back(addCamera);

		}
	}

	void inImGui() {
		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		if (ImGui::CollapsingHeader("camera")) {

			vector<string> camersName;

			for (int i = 0; i < objectCamersId.size(); i++) {
				camersName.push_back("camera" + to_string(objectCamersId[i]));
			}

			Combo("active Camera", camersName, &currentCamera);

			if (ImGui::Button("add camera"))
			{
				camers.insert(std::pair<int, Camera*>(idCamers, new Camera(WIDTH, HEIGHT, parentTransform->pos, parentTransform)));
				objectCamersId.push_back(idCamers);
				idCamers++;
			}
			if (objectCamersId.size() != 0) {
				dragFloat3(&camers[objectCamersId[currentCamera]]->transform.pos, "camera position");
				dragFloat3(&camers[objectCamersId[currentCamera]]->transform.rotation, "camera rotation");

				dragFloat(&camers[objectCamersId[currentCamera]]->fov, "fov (default: 45)");
				dragFloat(&camers[objectCamersId[currentCamera]]->nearPlane, "near plane");
				dragFloat(&camers[objectCamersId[currentCamera]]->farPlane, "far plane");
				if (ImGui::Button("use current camera"))
				{
					mainCamera = objectCamersId[currentCamera];
				}

				if (ImGui::Button("use default camera"))
				{
					mainCamera = 0;
				}
				if (objectCamersId[currentCamera] != 0) {
					if (ImGui::Button("delete camera"))
					{

						camers.erase(objectCamersId[currentCamera]);
						objectCamersId.erase(objectCamersId.begin() + currentCamera);
						currentCamera = 0;
						if (mainCamera == objectCamersId[currentCamera] && objectCamersId.size() != 0) {
							mainCamera = objectCamersId[0];
						}
						else if (mainCamera == objectCamersId[currentCamera]) {
							mainCamera = 0;
						}
					}
				}
			}

		}
	}


	void onDelete() {
		mainCamera = 0;

		for (int i = 0; i < objectCamersId.size(); i++) {
			camers.erase(objectCamersId[i]);

		}

	}

};
