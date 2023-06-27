
#include<string>
#include <fstream>
#include <sstream>
#include <cerrno>

string get_file_contents(const char* filename)
{
	/*ifstream fin(filename);
	string result = "";

	if (fin) {
		string tmp;
		while (!fin.eof()) {
			getline(fin, tmp);
			result += tmp;
		}
	}
	return result;*/
	std::ifstream in(filename, std::ios::binary);
	/*if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}*/
	if (in) {
		string content = "";
		string line;
		while (getline(in, line)) {
			content += line;
		}
		return content;
	}
	
}

class Shader {
public:
	int id;
	Shader() = default;
	Shader(const char* vFile, const char* fFile) {
		string vCode = get_file_contents(vFile);
		string fCode = get_file_contents(fFile);

		const char* vSourse = vCode.c_str();
		const char* fSourse = fCode.c_str();
		//cout << fSourse;
/*
		// Create Vertex Shader Object and get its reference
		GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
		// Attach Vertex Shader source to the Vertex Shader Object
		glShaderSource(vShader, 1, &vSourse, NULL);
		// Compile the Vertex Shader into machine code
		glCompileShader(vShader);

		// Create Fragment Shader Object and get its reference
		GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
		// Attach Fragment Shader source to the Fragment Shader Object
		glShaderSource(fShader, 1, &fSourse, NULL);
		// Compile the Vertex Shader into machine code
		glCompileShader(fShader);

		// Create Shader Program Object and get its reference
		id = glCreateProgram();
		// Attach the Vertex and Fragment Shaders to the Shader Program
		glAttachShader(id, vShader);
		glAttachShader(id, fShader);
		// Wrap-up/Link all the shaders together into the Shader Program
		glLinkProgram(id);

		// Delete the now useless Vertex and Fragment Shader objects
		glDeleteShader(vShader);
		glDeleteShader(fShader);
	*/
		int vertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShader, 1, &vSourse, nullptr);
		glCompileShader(vertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fSourse, nullptr);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		id = glCreateProgram();
		glAttachShader(id, vertexShader);
		glAttachShader(id, fragmentShader);
		glLinkProgram(id);

		glGetShaderiv(id, GL_LINK_STATUS, &success);

		if (!success) {
			char log[512];
			glGetShaderInfoLog(id, 512, nullptr, log);
			return;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Activate() {
		glUseProgram(id);
	}

	void Delete() {
		glDeleteProgram(id);
	}
};