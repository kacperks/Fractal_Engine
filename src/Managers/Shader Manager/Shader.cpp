#include "Shader.hpp"
//not finished yet

namespace glth{


			void Shader::Bind() {
				GLCALL(glUseProgram(program));
			}

			void Shader::Shader::UnBind() {
				GLCALL(glUseProgram(0));
			}

			void Shader::SetSample2D(const GLchar* uName, GLuint tex2d, GLint unit = 0) {
				GLCALL(glActiveTexture(GL_TEXTURE0 + unit));
				GLCALL(glBindTexture(GL_TEXTURE_2D, tex2d));
				GLCALL(glUniform1i(glGetUniformLocation(program, uName), unit));
			}

			void Shader::SetSampleCube(const GLchar* uName, GLuint cube, GLint unit = 0) {
				GLCALL(glActiveTexture(GL_TEXTURE0 + unit));
				GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, cube));
				GLCALL(glUniform1i(glGetUniformLocation(program, uName), unit));
			}

			void Shader::Set1i(const GLchar* uName, GLint value) {
				GLCALL(glUniform1i(glGetUniformLocation(program, uName), value));
			}

			void Shader::Set1f(const GLchar* uName, GLfloat value) {
				GLCALL(glUniform1f(glGetUniformLocation(program, uName), value));
			}

			void Shader::Set2f(const GLchar* uName, GLfloat x, GLfloat y) {
				GLCALL(glUniform2f(glGetUniformLocation(program, uName), x, y));
			}

			void Shader::SetV2f(const GLchar* uName, glm::vec2 v) {
				Set2f(uName, v.x, v.y);
			}

			void Shader::Set3f(const GLchar* uName, GLfloat x, GLfloat y, GLfloat z) {
				GLCALL(glUniform3f(glGetUniformLocation(program, uName), x, y, z));
			}

			void Shader::SetV3f(const GLchar* uName, glm::vec3 v) {
				Set3f(uName, v.x, v.y, v.z);
			}

			void Shader::Set4f(const GLchar* uName, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
				GLCALL(glUniform4f(glGetUniformLocation(program, uName), x, y, z, w));
			}

			void Shader::SetV4f(const GLchar* uName, glm::vec4 v) {
				Set4f(uName, v.x, v.y, v.z, v.z);
			}

			void Shader::SetMatrix4f(const GLchar* uName, const GLfloat* mtx) {
				GLCALL(glUniformMatrix4fv(glGetUniformLocation(program, uName), 1, GL_FALSE, mtx));
			}
			void Shader::SetUniform(const char * name, int n){
					GLint loc = glGetUniformLocation(ProgramObject, name);
					if (loc != -1)
					{
						glUniform1f(loc, 0.432);
					}
			}


};