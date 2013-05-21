#include <jni.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <math.h>
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

void renderFrameLine() {
	GLfloat vVertices[] = { 0.0f, 0.8f, 0.0f, -0.8f, -0.8f, 0.0f, 0.8f, 0.0f };
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// Use the program object
	glUseProgram(programObject);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 4);
}

void renderFrameMix() {
	GLfloat vVerticesLine[] =
			{ 0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, 0.0f };
	GLfloat vVerticesTriangle[] = { 0.0f, -0.5f, 0.0f, -0.5f, -1.0f, 0.0f, 0.5f,
			-1.0f, 0.0f };

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// Use the program object
	glUseProgram(programObject);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vVerticesLine);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 4);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVerticesTriangle);
	glDrawArrays(GL_TRIANGLES, 0, 3);
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

void getEGLInfo() {
	LOGD("Getting EGL config");
	EGLDisplay display;
	EGLint major, minor;
	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(display, &major, &minor);
	LOGD("Major is: %d. Minor is: %d\n", major, minor);
	EGLint attribList[] = { EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_DEPTH_SIZE, 1, EGL_NONE };
	const EGLint MaxConfigs = 10;
	EGLConfig configs[MaxConfigs];
	EGLint numConf;
	LOGD("Getting Choose Config");
	if (!eglChooseConfig(display, attribList, configs, MaxConfigs, &numConf)) {
		LOGD("There was a problem");
	} else {
		LOGD("There were %d found.", numConf);
		int i;
		for (i = 0; i < numConf; i++) {
			EGLConfig c = configs[i];
			EGLint answer;
			if (!eglGetConfigAttrib(display, c, EGL_DEPTH_SIZE, &answer)) {
				LOGD("Config property not found");
			} else {
				LOGD("Answer is %d", answer);
			}
		}

		EGLSurface window;
		EGLint attribList2[] = { EGL_RENDER_BUFFER, EGL_BACK_BUFFER, EGL_NONE };

//		window = eglCreateWindowSurface(display, window, c, attribList2);
//		if(window == EGL_NO_SURFACE){
//			LOGD("There was a problem with the surface");
//		}
//		else{
//			EGLint width;
//			EGLint height;
//			eglQuerySurface(display,window,EGL_WIDTH,&width);
//			eglQuerySurface(display,window,EGL_HEIGHT,&height);
//			LOGD("Width %d Height %d",width, height);
//		}
	}

}

float static centerX = 0.0f;
int centerY = 0;

void renderMovingFrame() {
	//LOGD("Rendering... CenterX: %d CenterY: %d",centerX,centerY);
	GLfloat vVertices[] = { (0.0f + centerX), (0.5f + centerY), 0.0f, (-0.5f
			+ centerX), (-0.5f + centerY), 0.0f, (0.5f + centerX), (-0.5f
			+ centerY), 0.0f };
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(programObject);
	// Use the program object

	// Load the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

static int width;
static int height;
static float xLocation = -2;
static float yLocation = -2;
static float zLocation = -1;

void drawCircle() {
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(programObject);
	const float DEG2RAD = 3.14159f / 180.0f;
	//int totalVertices = 360 * 12;
	int totalVertices = 360 * 4;
	const float radsPerLine = (180.f / totalVertices) * DEG2RAD;
	float lineVertices[(totalVertices * 6)];
	int i;
	int ii = 0;
	float rad = 0.5f;
	float centerX = width;
	if (xLocation > 2) {
		xLocation = -2;
	} else {
		xLocation = xLocation + 0.01f;
	}
	if (yLocation > 2) {
		yLocation = -2;
	} else {
		yLocation = yLocation + 0.01f;
	}
	if (zLocation > 1) {
		zLocation = -1;
	} else {
		zLocation = zLocation + 0.01f;
		LOGD("%.1f", zLocation);
	}
	float xCorrect = height / ((float) width);
	float yCorrect = 1; //width/((float)height);

	for (i = 0; i < (totalVertices); i++) {

		float degInRad = radsPerLine * i;
		float cosine = cos(degInRad);
		float sine = sin(degInRad);
		GLfloat x1 = (-1 * (cosine * (rad * xCorrect))) + xLocation;
		GLfloat y1 = (-1 * (sine * (rad * yCorrect))) + yLocation;
		GLfloat z1 = zLocation;
		GLfloat x2 = (cosine * (rad * xCorrect)) + xLocation;
		GLfloat y2 = (sine * (rad * yCorrect)) + yLocation;
		GLfloat z2 = zLocation;
		lineVertices[ii++] = x1;
		lineVertices[ii++] = y1;
		lineVertices[ii++] = z1;
		lineVertices[ii++] = x2;
		lineVertices[ii++] = y2;
		lineVertices[ii++] = z2;
	}
	int size = sizeof(lineVertices) / sizeof(lineVertices[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, lineVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, totalVertices * 2);
}

int repeat = 0;

void drawStuff(int width, int height, int centerX, int centerY) {
	LOGD("Width %d", width);
	GLfloat vVerticesLine[] = { 0.0f, 0.8f, 0.0f, -1.0f * width, -0.5f, 0.0f,
			0.5f, 0.0f };
	GLfloat vVerticesTriangle[] = { 0.0f, -0.5f, 0.0f, -0.5f, -1.0f, 0.0f, 0.5f,
			-1.0f, 0.0f };

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// Use the program object
	glUseProgram(programObject);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vVerticesLine);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 4);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVerticesTriangle);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int stop = 0;

static void loop(void) {

	for (;;) {

		if (centerX >= 1) {
			centerX = -1;
		} else {
			centerX = centerX + .1;
		}
		// LOGD("Incremented... %d", centerX );
		if (stop == 1) {
			break;
		}
	}
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
JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Sprite_setHeight(JNIEnv* env, jclass class, jint h)
{
	LOGD("Setting height... %d", h);
height=h;
}
JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Sprite_setWidth(JNIEnv* env, jclass class, jint w)
{
width=w;
}
JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Sprite_render(JNIEnv* env, jclass class)
{
//renderFrame();
drawCircle();
}
JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Sprite_renderline(JNIEnv* env, jclass class)
{
renderFrameLine();
}
JNIEXPORT void JNICALL Java_org_gleason_opengles2_opengl_model_Sprite_loop(JNIEnv* env, jclass class)
{
loop();
}

