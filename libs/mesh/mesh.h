#pragma onc


class Mesh {
public:
	vector<Vertex> vert;
	vector<unsigned> indes;
	vector<Texture> tex;
	Texture* difMap = nullptr;
	Texture* normMap = nullptr;
	//Texture parMap;

	VAO vao;

	Mesh() = default;

	Mesh(vector<Vertex>& vertex, vector<unsigned>& indices, string difTex, string normTex/*vector<Texture>& textures*/) {
		vert = vertex;
		indes = indices;
		//tex = textures;

		if (difTex != "") {
			difMap = new Texture(difTex.c_str(), 'd', GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
		}
		if (normTex != "") {
			cout << "hehe";
			normMap = new Texture(normTex.c_str(), 'n', GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
		}

		//parMap = parTex;
		vao.bind();

		VBO vbo = VBO(vertex);
		EBO ebo = EBO(indices);


		vao.linkVBO(vbo, 0, 3, sizeof(Vertex), (void*)0);
		vao.linkVBO(vbo, 1, 3, sizeof(Vertex), (void*)(3 * sizeof(float)));
		vao.linkVBO(vbo, 2, 2, sizeof(Vertex), (void*)(6 * sizeof(float)));

		vao.unBind();
		vbo.unBind();
		ebo.unBind();
	}

	void updateTex(string difTex) {
		//tex = tex2;
		if (difTex != "") {
			difMap = new Texture(difTex.c_str(), 'd', GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
		}
	}

	void updateNormal(string normTex) {
		//tex = tex2;
		if (normTex != "") {
			normMap = new Texture(normTex.c_str(), 'n', GL_TEXTURE_2D, 1, GL_RGB, GL_UNSIGNED_BYTE);
		}
	}

	void draw(Shader& shader, Camera& camera, Vec3 translate, Mat3 rotation, Vec3 scale, Vec4 color,  map<int, Light*> light) {
		//shader.Activate();
		vao.bind();

		if (difMap != nullptr) {
			difMap->texUnit(shader, "diffuse0", 0);
			difMap->bind();
		}
		if (normMap != nullptr){
			//cout << "normal";
			normMap->texUnit(shader, "normalMap0", 1);
			normMap->bind();
			glUniform1i(glGetUniformLocation(shader.id, "isNormalMap"), true);
		}
		else {
			glUniform1i(glGetUniformLocation(shader.id, "isNormalMap"), false);
		}

		//cout << light[0]->pos<<endl;
		glUniformMatrix4fv(glGetUniformLocation(shader.id, "matPV"), 1, GL_FALSE, &(camera.matPV).matrix[0][0]);

		glUniform3fv(glGetUniformLocation(shader.id, "translate"), 1,  reinterpret_cast<float*>(&translate));
		glUniformMatrix3fv(glGetUniformLocation(shader.id, "rotation"), 1, GL_FALSE, &(rotation).matrix[0][0]);
		glUniform3fv(glGetUniformLocation(shader.id, "scale"), 1, reinterpret_cast<float*>(&scale));
		glUniform4f(glGetUniformLocation(shader.id, "color"), color.a, color.v.x, color.v.y, color.v.z);
		glUniform3f(glGetUniformLocation(shader.id, "camPos"), camera.pos.x, camera.pos.y, camera.pos.z);
		
		//float type = 0;
		//int i = 0;
		//for (std::map<int,	Light*>::iterator it = light.begin(); it != light.end(); ++it) {
		//	

		//	if (it->second->type == "d") {
		//		type = 1.0f;
		//	}
		//	else if (it->second->type == "s") {
		//		type = 2.0f;
		//	}
		//	else if (it->second->type == "p") {
		//		type = 0.0f;
		//	}
		//	string tmp = "gPointLights[" + to_string(i) + "].pos";
		//	glUniform3f(glGetUniformLocation(shader.id, tmp.c_str()), it->second->pos.x, it->second->pos.y , it->second->pos.z);
		//	tmp = "gPointLights[" + to_string(i) + "].direction";
		//	glUniform3f(glGetUniformLocation(shader.id, tmp.c_str()), it->second->direction.x, it->second->direction.y, it->second->direction.z);
		//	
		//	tmp = "gPointLights[" + to_string(i) + "].color";
		//	glUniform4f(glGetUniformLocation(shader.id, tmp.c_str()), it->second->colorDif.a, it->second->colorDif.v.x, it->second->colorDif.v.y, it->second->colorDif.v.z);
		//	tmp = "gPointLights[" + to_string(i) + "].intens";
		//	glUniform1f(glGetUniformLocation(shader.id, tmp.c_str()), it->second->intens);
		//	tmp = "gPointLights[" + to_string(i) + "].isOn";
		//	glUniform1f(glGetUniformLocation(shader.id, tmp.c_str()), it->second->isOn);
		//	
		//	tmp = "gPointLights[" + to_string(i) + "].type";
		//	glUniform1f(glGetUniformLocation(shader.id, tmp.c_str()), type);
		//	i++;
		//}

		glDrawElements(GL_TRIANGLES, (indes.size()), GL_UNSIGNED_INT, 0);
		vao.unBind();
	}
};