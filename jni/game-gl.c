#include <jni.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "org_gleason_opengles2_opengl_model_Sprite.h"

#define LOG_TAG "Native"

#include <android/log.h>
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static GLint vertices[][3] = { { -0x10000, -0x10000, -0x10000 }, { 0x10000,
		-0x10000, -0x10000 }, { 0x10000, 0x10000, -0x10000 }, { -0x10000,
		0x10000, -0x10000 }, { -0x10000, -0x10000, 0x10000 }, { 0x10000,
		-0x10000, 0x10000 }, { 0x10000, 0x10000, 0x10000 }, { -0x10000, 0x10000,
		0x10000 } };


GLbyte vShaderStr[] = "attribute vec4 vPosition;   \n"
		"void main()                 \n"
		"{                           \n"
		"   gl_Position = vPosition; \n"
		"}                           \n";

GLbyte fShaderStr[] = "precision mediump float;                   \n"
		"void main()                                \n"
		"{                                          \n"
		"  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
		"}                                          \n";

GLuint programObject;

GLuint LoadShader(GLenum type, const char *shaderSrc) {
	GLuint shader;
	GLint compiled;
	// Create the shader object
	shader = glCreateShader(type);
	if (shader == 0)
		return 0;
	// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);

	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLint infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);


		glDeleteShader(shader);
		return 0;
	}

	return shader;

}

void InitializeOpenGL() {
	GLuint vertexShader;
	GLuint fragmentShader;
	vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
	fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);

	programObject = glCreateProgram();
	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);
	glBindAttribLocation(programObject, 0, "vPosition");
	glLinkProgram(programObject);
	glUseProgram(programObject);
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
}
void resizeViewport(int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
}
void renderFrame() {
	GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
			0.0f };

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// Use the program object
	glUseProgram(programObject);

	// Load the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void getEGLInfo(){
	EGLDisplay display;
	EGLint major, minor;
	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(display, &major, &minor);
	LOGD("Major is: %d. Minor is: %d\n", major, minor );
}
JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Sprite_eglinfo(JNIEnv* env, jclass class)
{
	getEGLInfo();
}
JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Sprite_init(JNIEnv* env, jclass class)
{
	InitializeOpenGL();
}
JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Sprite_resize(JNIEnv* env, jclass class, jint width, jint height)
{
	resizeViewport(width, height);
}
JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Sprite_render(JNIEnv* env, jclass class)
{
	renderFrame();
}





