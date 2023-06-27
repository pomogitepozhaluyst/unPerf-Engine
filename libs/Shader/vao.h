#pragma once
class VAO
{
public:
	unsigned id=0;
	VAO() {
		glCreateVertexArrays(1, &id);
	}

	void linkVBO(VBO vbo, int layout, int component,GLsizeiptr str, void* size  ) {
		vbo.bind();
		glVertexAttribPointer(layout, component, GL_FLOAT, GL_FALSE, str, size);
		glEnableVertexAttribArray(layout);

		vbo.unBind();

	}

	void bind() {
		glBindVertexArray(id);


	}

	void unBind() {
		glBindVertexArray(0);

	}

	void Delete() {
		glDeleteVertexArrays(1, &id);

	}
};

