

class Texture {
public:
	unsigned id;
	GLenum type;
	char typeTex;
	GLuint unit;
	Texture() = default;

	Texture(const char* image, char t,  GLenum texType, GLuint slot, GLuint  format, GLenum pixelType, bool *status) {
		type = texType;
		typeTex = t;
		glGenTextures(1, &id);

		int w, h, c;
		//stbi_set_flip_vertically_on_load(true);
		unsigned char* texData = stbi_load(image, &w, &h, &c, 0);
		glActiveTexture(GL_TEXTURE0 + slot);
		unit = slot;
		glBindTexture(texType, id);

		glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		if (texData) {

			GLenum format1 = GL_RGB;
			switch (c)
			{
			case 1:
				format1 = GL_LUMINANCE;
				break;
			case 2:
				format1 = GL_LUMINANCE_ALPHA;
				break;
			case 3:
				format1 = GL_RGB;
				break;
			case 4:
				format1 = GL_RGBA;
				break;
			}
	
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, format1, GL_UNSIGNED_BYTE, texData);


			glGenerateMipmap(texType);
			*status = true;
		}
		else {
			*status = false;
		}


		stbi_image_free(texData);
		glBindTexture(texType, 0);
	}


	Texture(string image, bool* isStatusLoadDTex)
	{
		vector<std::string> faces=
		{
			image+"/right.jpg",
				image + "/left.jpg",
				image + "/top.jpg",
				image + "/bottom.jpg",
				image + "/front.jpg",
				image + "/back.jpg"
		};

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_CUBE_MAP, id);


		int w, h, c;

		for (unsigned int i = 0; i < faces.size(); i++)
		{
			unsigned char* data = stbi_load(faces[i].c_str(), &w, &h, &c, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);
				stbi_image_free(data);
				*isStatusLoadDTex = true;
			}
			else
			{
				std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
				*isStatusLoadDTex = false;
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	}


	void texUnit(Shader& shader, const char* uniform, GLuint unit1) {
		shader.Activate();
		glUniform1i(glGetUniformLocation(shader.id, uniform), unit1);
	}

	void bind() {
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(type, id);
	}
	void unBind() {
		glBindTexture(type, 0);
	}
	void Delete() {
		glDeleteTextures(1, &id);
	}
};