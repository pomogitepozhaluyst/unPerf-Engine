#pragma once
struct Combo
{
	std::string name;
	std::vector<string> items;

	Combo(string name1, vector<string> data, int* current_item) {
		name = name1;
		items = data;
		update(current_item);
	}
	bool update(int* current_item)
	{
		auto get_item = [](void* data, int idx, const char** text) noexcept -> bool
		{
			*text = static_cast<Combo*>(data)->items[idx].c_str();
			return true;
		};
		return ImGui::Combo(name.c_str(), current_item, get_item, this, items.size());
	}
};

class Component {
	public:
	void dragFloat3(Vec3* v, const char* text = "tmp", float speed = 0.1f) {
		ImGui::DragFloat3(text, reinterpret_cast<float*>(v), speed);
	}

	void dragFloat4(Vec4* v, const char* text = "tmp", float speed = 0.1f) {
		ImGui::DragFloat4(text, reinterpret_cast<float*>(v), speed);
	}
	void dragFloat2(Vec2* v, const char* text = "tmp", float speed = 0.1f) {
		ImGui::DragFloat2(text, reinterpret_cast<float*>(v), speed);
	}
	void dragFloat(float* v, const char* text = "tmp", float speed = 0.1f) {
		ImGui::DragFloat(text, v, speed);
	}

	virtual void inImGui() {
	};
	virtual void update(map<string, Shader> shaders, sf::Event windowEvent) {};

	virtual void onDelete() {
	};

};







