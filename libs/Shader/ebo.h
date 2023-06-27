#pragma once
class EBO
{
public:
	unsigned id=0;
	EBO(vector<unsigned>& indes) {
		glGenBuffers(1, &id);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indes.size()*sizeof(unsigned int ), indes.data(), GL_STATIC_DRAW);
	}

	void bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

	}

	void unBind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	void Delete() {
		glDeleteBuffers(1, &id);

	}
};

