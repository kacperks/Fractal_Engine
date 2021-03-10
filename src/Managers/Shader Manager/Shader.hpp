#pragma once
#include "../../fractal.hpp"

namespace glth{
	class Shader {

		public:
			Shader() : program(0) {}
			Shader(const GLuint id) : program(id) {}

			void Bind() ;

			void UnBind() ;

			void SetSample2D(const GLchar* uName, GLuint tex2d, GLint unit = 0) ;

			void SetSampleCube(const GLchar* uName, GLuint cube, GLint unit = 0) ;

			void Set1i(const GLchar* uName, GLint value);

			void Set1f(const GLchar* uName, GLfloat value) ;

			void Set2f(const GLchar* uName, GLfloat x, GLfloat y) ;

			void SetV2f(const GLchar* uName, glm::vec2 v) ;

			void Set3f(const GLchar* uName, GLfloat x, GLfloat y, GLfloat z) ;

			void SetV3f(const GLchar* uName, glm::vec3 v) ;

			void Set4f(const GLchar* uName, GLfloat x, GLfloat y, GLfloat z, GLfloat w) ;

			void SetV4f(const GLchar* uName, glm::vec4 v) ;

			void SetMatrix4f(const GLchar* uName, const GLfloat* mtx) ;

			void SetUniform(const char * name, glm::mat4 * matrix);

			void SetUniform(const char * name, int n);

			void CreateUniform(const char * name);

			GLuint Program() const {
				return program;
			}

		private:
			GLuint program;
		};


};
