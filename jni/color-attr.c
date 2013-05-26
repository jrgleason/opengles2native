#include <jni.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <math.h>

#define LOG_TAG "Native"

#include <android/log.h>
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

GLbyte vShaderStr[] = "attribute vec4 vPosition;   \n"
		"uniform mat4 Projection;   \n"
		"attribute vec4 color;   \n"
		"void main()                 \n"
		"{                           \n"
		"   gl_Position = Projection * vPosition; \n"
		"}                           \n";

GLbyte fShaderStr[] = "precision mediump float;"
	"attribute vec4 color;   \n"
    "void main()                                \n"
    "{                                          \n"
    "  gl_FragColor = color; \n"
    "}                                          \n";

GLuint programObject;

float widthScreen;
float heightScreen;

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

void glOrthof(float left, float right, float bottom, float top, float near, float far){
	        LOGD("In glOrtho");
	        float a = 2.0f / (right - left);
	        float b = 2.0f / (top - bottom);
	        float c = -2.0f / (far - near);

	        float tx = - (right + left)/(right - left);
	        float ty = - (top + bottom)/(top - bottom);
	        float tz = - (far + near)/(far - near);

	        float ortho[16] = {
	            a, 0, 0, 0,
	            0, b, 0, 0,
	            0, 0, c, 0,
	            tx, ty, tz, 1
	        };


	        GLint projectionUniform = glGetUniformLocation(programObject, "Projection");
	        glUniformMatrix4fv(projectionUniform, 1, 0, &ortho[0]);
	        LOGD("In finished glOrtho");
}

void InitializeOpenGL() {
	LOGD("Initialization Started");
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
	glOrthof(0, widthScreen, heightScreen, 0, 2.0, -2.0);
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	LOGD("Initialization Complete");
}
void resizeViewport(int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
}

static float currentZ = 1.0f;

void initColor(){
	GLint location = glGetUniformLocation(programObject, "color");
	glUniform4f(location,1.0f,0.0f,currentZ,1.0f);
}

void toggleColor(){
	if(currentZ == 1.0f){
		currentZ = 0.0f;
	}
	else{
		currentZ = 1.0f;
	}
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



float static centerX = 0.0f;
int centerY = 0;
static int width;
static int height;
static float xLocation = 0;
static float yLocation = 0;
static float zLocation = 0;
int repeat = 0;

JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Native_init(JNIEnv* env, jclass class)
{
	InitializeOpenGL();
}
JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Native_resize(JNIEnv* env, jclass class, jint width, jint height)
{
	resizeViewport(width, height);
}
JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Native_render(JNIEnv* env, jclass class)
{
  renderFrame();
}
JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Sprite_setCords(JNIEnv* env, jclass class, jfloat y, jfloat x)
{
	widthScreen = x;
	heightScreen = y;
//	glOrthof(0, x, y, 0, 2.0, -2.0);
}
JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Sprite_toggleColor(JNIEnv* env, jclass class)
{
	toggleColor();
}


