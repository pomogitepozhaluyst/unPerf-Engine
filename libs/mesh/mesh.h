#pragma onc


class Material {
public:
	Vec3 ambient;
	Vec3 diffuse;
	Vec3 specular;
	float shinines;

	Material() {
		ambient = Vec3(1.0f, 1.0f, 1.0f);
		diffuse = Vec3(1.0f, 1.0f, 1.0f);
		specular = Vec3(1.0f, 1.0f, 1.0f);
		shinines = 32.0f;
	}


	Material(Vec3 amb, Vec3 dif, Vec3 spec, float shin) {
		ambient = amb;
		diffuse = dif;
		specular = spec;
		shinines = shin;
	}

};

class Mesh {
public:
	vector<Vertex> vert;
	vector<unsigned> indes;
	vector<Texture> tex;
	Texture* difMap = nullptr;
	Texture* normMap = nullptr;
	Texture* parallaxMap = nullptr;
	float heightScale = 1.0f;

	bool isDTex = false;
	bool isNTex = false;
	bool isPTex = false;

	bool isStatusLoadDTex = false;
	bool isStatusLoadNTex = false;
	bool isStatusLoadPTex = false;


	Vec3 localPos = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 localRot = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 localScale = Vec3(1.0f, 1.0f, 1.0f);
	Vec4 localColor = Vec4(0.0f, 0.0f, 0.0f, 0.0f);

	Material material;


	//Texture parMap;

	VAO vao;

	Mesh() = default;

	Mesh(vector<Vertex>& vertex, vector<unsigned>& indices) {
		vert = vertex;
		indes = indices;
		//tex = textures;


		calcTB();

		//parMap = parTex;
		vao.bind();

		VBO vbo = VBO(vertex);
		EBO ebo = EBO(indices);


		vao.linkVBO(vbo, 0, 3, sizeof(Vertex), (void*)0);
		vao.linkVBO(vbo, 1, 2, sizeof(Vertex), (void*)(3 * sizeof(float)));

		vao.linkVBO(vbo, 2, 3, sizeof(Vertex), (void*)(5 * sizeof(float)));
		vao.linkVBO(vbo, 3, 3, sizeof(Vertex), (void*)(8 * sizeof(float)));
		vao.linkVBO(vbo, 4, 3, sizeof(Vertex), (void*)(11 * sizeof(float)));

		vao.unBind();
		vbo.unBind();
		ebo.unBind();
	}




	Mesh(vector<Vertex>& vertex, vector<unsigned>& indices, string difTex, string normTex/*vector<Texture>& textures*/) {
		vert = vertex;
		indes = indices;
		//tex = textures;

		if (difTex != "") {
			difMap = new Texture(difTex.c_str(), 'd', GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &isDTex);
		}
		if (normTex != "") {
			cout << "hehe";
			normMap = new Texture(normTex.c_str(), 'n', GL_TEXTURE_2D, 1, GL_RGB, GL_UNSIGNED_BYTE, &isNTex);
		}
		calcTB();

		//parMap = parTex;
		vao.bind();

		VBO vbo = VBO(vert);
		EBO ebo = EBO(indes);


		vao.linkVBO(vbo, 0, 3, sizeof(Vertex), (void*)0);
		vao.linkVBO(vbo, 1, 2, sizeof(Vertex), (void*)(3 * sizeof(float)));

		vao.linkVBO(vbo, 2, 3, sizeof(Vertex), (void*)(5 * sizeof(float)));
		vao.linkVBO(vbo, 3, 3, sizeof(Vertex), (void*)(8 * sizeof(float)));
		vao.linkVBO(vbo, 4, 3, sizeof(Vertex), (void*)(11 * sizeof(float)));


		vao.unBind();
		vbo.unBind();
		ebo.unBind();
	}

	void calcTB() {
		for (int i = 0; i < indes.size() - 2; i += 3) {


			// Edges of the triangle : position delta
			Vec3 deltaPos1 = vert[indes[i + 1]].pos - vert[indes[i]].pos;
			Vec3 deltaPos2 = vert[indes[i + 2]].pos - vert[indes[i]].pos;

			// UV delta
			Vec2 deltaUV1 = vert[indes[i + 1]].tex - vert[indes[i]].tex;
			Vec2 deltaUV2 = vert[indes[i + 2]].tex - vert[indes[i]].tex;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
			vert[indes[i]].tan = vert[indes[i + 1]].tan = (vert[indes[i + 2]].tan = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r).Normalize();
			vert[indes[i]].bitan = vert[indes[i + 1]].bitan = vert[indes[i + 2]].bitan = ((deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r).Normalize();


		}
	}

	void updateTex(string difTex) {
		//tex = tex2;
		if (difTex != "") {
			difMap = new Texture(difTex.c_str(), 'd', GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &isStatusLoadDTex);
			isDTex=isStatusLoadDTex;
		}
	}

	void deleteDifMap() {
		delete difMap;
		isStatusLoadDTex=isDTex = false;
	}
	void deleteNormMap() {
		delete normMap;
		isStatusLoadNTex=isNTex = false;
	}
	void deleteParallaxMap() {
		delete parallaxMap;
		isStatusLoadPTex=isPTex = false;
	}

	void updateNormal(string normTex) {
		//tex = tex2;
		if (normTex != "") {
			normMap = new Texture(normTex.c_str(), 'n', GL_TEXTURE_2D, 1, GL_RGB, GL_UNSIGNED_BYTE, &isStatusLoadNTex);
			isNTex = isStatusLoadNTex;

		}
	}

	void updateParallax(string parallaxTex) {
		//tex = tex2;
		if (parallaxTex != "") {
			parallaxMap = new Texture(parallaxTex.c_str(), 'p', GL_TEXTURE_2D, 2, GL_RGB, GL_UNSIGNED_BYTE, &isStatusLoadPTex);
			isPTex = isStatusLoadPTex;

		}
	}


	void draw(Shader& shader, Camera& camera, Vec3 translate, Mat3 rotation, Vec3 scale, Vec4 color) {
		//shader.Activate();
		vao.bind();

		if (isDTex) {
			difMap->texUnit(shader, "diffuse0", 0);
			difMap->bind();
			glUniform1i(glGetUniformLocation(shader.id, "isDiffuseMap"), true);

		}
		else {
			glUniform1i(glGetUniformLocation(shader.id, "isDiffuseMap"), false);
		}
		if (isNTex){
			//cout << "normal";
			normMap->texUnit(shader, "normalMap0", 1);
			normMap->bind();
			glUniform1i(glGetUniformLocation(shader.id, "isNormalMap"), true);
		}
		else {
			glUniform1i(glGetUniformLocation(shader.id, "isNormalMap"), false);
		}
		if (isDTex && isPTex) {
			//cout << "normal";
			parallaxMap->texUnit(shader, "parallaxMap0", 2);
			parallaxMap->bind();
			glUniform1i(glGetUniformLocation(shader.id, "isParallaxMap"), true);
		}
		else {
			glUniform1i(glGetUniformLocation(shader.id, "isParallaxMap"), false);
	}


		glUniform3fv(glGetUniformLocation(shader.id, "material.ambient"), 1, reinterpret_cast<float*>(&material.ambient));
		glUniform3fv(glGetUniformLocation(shader.id, "material.specular"), 1, reinterpret_cast<float*>(&material.specular));
		glUniform3fv(glGetUniformLocation(shader.id, "material.diffuse"), 1, reinterpret_cast<float*>(&material.diffuse));
		glUniform1f(glGetUniformLocation(shader.id, "material.shininess"), material.shinines);
		glUniform1f(glGetUniformLocation(shader.id, "heightScale"), heightScale);



		glUniformMatrix3fv(glGetUniformLocation(shader.id, "rotationMat"), 1, GL_FALSE, &rotation.matrix[0][0]);
		glUniformMatrix3fv(glGetUniformLocation(shader.id, "matV"), 1, GL_FALSE, &LookAt3x3(camera.pos, camera.pos + camera.direction, camera.up).matrix[0][0]);

		glUniformMatrix4fv(glGetUniformLocation(shader.id, "matPV"), 1, GL_FALSE, &(camera.matPV).matrix[0][0]);
		Vec3 transTmp = translate + localPos;
		glUniform3fv(glGetUniformLocation(shader.id, "translate"), 1,  reinterpret_cast<float*>(&transTmp));
		glUniformMatrix3fv(glGetUniformLocation(shader.id, "rotation"), 1, GL_FALSE, &rotation.matrix[0][0]);
		Vec3 scaleTmp = scale + localScale;
		glUniform3fv(glGetUniformLocation(shader.id, "scale"), 1, reinterpret_cast<float*>(&scaleTmp));
		glUniform4f(glGetUniformLocation(shader.id, "color"), color.a+localColor.a, color.v.x + localColor.v.x, color.v.y + localColor.v.y, color.v.z + localColor.v.z);
		glUniform3f(glGetUniformLocation(shader.id, "camPos"), camera.pos.x, camera.pos.y, camera.pos.z);
		glUniform3f(glGetUniformLocation(shader.id, "camPos"), camera.pos.x, camera.pos.y, camera.pos.z);
		

		glDrawElements(GL_TRIANGLES, (indes.size()), GL_UNSIGNED_INT, 0);
		vao.unBind();
	}

	void drawCubeLight(Shader& shader, Camera& camera, Vec3 translate, Vec3 scale, Vec4 color) {
		vao.bind();
		glUniformMatrix4fv(glGetUniformLocation(shader.id, "matPV"), 1, GL_FALSE, &(camera.matPV).matrix[0][0]);

		glUniform4f(glGetUniformLocation(shader.id, "color"), color.a, color.v.x, color.v.y, color.v.z);
		glUniform3fv(glGetUniformLocation(shader.id, "translate"), 1, reinterpret_cast<float*>(&translate));
		glUniform3fv(glGetUniformLocation(shader.id, "scale"), 1, reinterpret_cast<float*>(&scale));
		glDrawElements(GL_TRIANGLES, (indes.size()), GL_UNSIGNED_INT, 0);
		vao.unBind();

	}

	void drawSkyBox(Shader& shader, Camera& camera) {
		vao.bind();
		difMap->texUnit(shader, "skybox", 0);
		difMap->bind();
		glUniformMatrix4fv(glGetUniformLocation(shader.id, "matPV"), 1, GL_FALSE, &(camera.matPV).matrix[0][0]);
		glUniform3fv(glGetUniformLocation(shader.id, "translate"), 1, reinterpret_cast<float*>(&camera.pos));
		Vec3 far = Vec3(camera.farPlane, camera.farPlane, camera.farPlane);
		glUniform3fv(glGetUniformLocation(shader.id, "scale"), 1, reinterpret_cast<float*>(&far));
		glDrawElements(GL_TRIANGLES, (indes.size()), GL_UNSIGNED_INT, 0);
		vao.unBind();

	}
};