#pragma once
class VBO
{
public:
	unsigned id=0;
	VBO(vector<Vertex>& verts) {
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(Vertex), verts.data(), GL_STATIC_DRAW);
	}

	void bind() {
		glBindBuffer(GL_ARRAY_BUFFER, id);

	}

	void unBind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void Delete() {
		glDeleteBuffers(1, &id);

	}
};

