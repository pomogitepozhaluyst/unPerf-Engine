#pragma once

class Transform : public Component {
public:
	Vec3 pos;
	Vec3 rotation;
	Vec3 scale;
	Vec4 color;
	bool isOn = true;
	bool localRotation = true;
	Mat3 matRotation = Mat3().E();


	Transform(Vec3 pos1 = Vec3(0.0f, 0.0f, 0.0f), Vec3 rot1 = Vec3(0.0f, 0.0f, 0.0f), Vec3 scale1 = Vec3(1.0f, 1.0f, 1.0f), Vec4 color1 = Vec4(0.5f, 0.5f, 0.5f, 0.5f)) {
		pos = pos1;
		rotation = rot1;
		scale = scale1;
		color = color1;

	}

	void updateMarixRotation() {

		matRotation = MRotationX3(rotation.x) * MRotationY3(rotation.y);

		matRotation = matRotation * MRotationZ3(rotation.z);
	}



	Transform getTransformMesh(Transform localTransform = Transform()) {
		Transform result;
		updateMarixRotation();

		if (localRotation) {
			result.pos = pos + localTransform.pos;
		}
		else {
			result.pos = pos + matRotation * localTransform.pos;
		}

		result.matRotation = MRotationX3(-(rotation.x + localTransform.rotation.x)) * MRotationY3(-(rotation.y + localTransform.rotation.y));
		result.matRotation = result.matRotation * MRotationZ3(-(rotation.z + localTransform.rotation.z));
		result.scale = scale * localTransform.scale;
		result.color = color + localTransform.color;
		return result;
	}


	void inImGui() {

		if (ImGui::CollapsingHeader("transform")){
			dragFloat3(&pos, "position");
			dragFloat3(&rotation, "rotation");
			ImGui::SameLine();
			ImGui::Checkbox("is local rotation", &localRotation);

			dragFloat3(&scale, "size");
			dragFloat4(&color, "color");
			ImGui::Checkbox("is draw", &isOn);
		}

	}



};

