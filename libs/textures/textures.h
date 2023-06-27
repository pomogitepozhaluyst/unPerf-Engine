

class Texture {
public:
	unsigned id;
	GLenum type;
	char typeTex;
	GLuint unit;
	Texture() = default;

	Texture(const char* image, char t,  GLenum texType, GLuint slot, GLuint  format, GLenum pixelType) {
		type = texType;
		typeTex = t;
		glGenTextures(1, &id);

		int w, h, c;
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
			glTexImage2D(texType, 0, GL_RGBA, w, h, 0, format, pixelType, texData);
			glGenerateMipmap(texType);
		}
		else {
			std::cout << "ERR" << std::endl;
		}

		stbi_image_free(texData);
		glBindTexture(texType, 0);
	}

	void texUnit(Shader& shader, const char* uniform, GLuint unit) {
		shader.Activate();
		glUniform1i(glGetUniformLocation(shader.id, uniform), unit);
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