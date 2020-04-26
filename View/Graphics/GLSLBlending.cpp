#include "GLSLBlending.h"
#include "define.h"

GLSLBlending::GLSLBlending(QObject *parent) : GLSLProgram(parent)
{
}

GLSLBlending::~GLSLBlending()
{
}

void GLSLBlending::initialize(int panoWidth, int panoHeight, int viewCount)
{
	this->panoramaWidth = panoWidth;
	this->panoramaHeight = panoHeight;
	this->m_viewCount = viewCount;
	
	// frame buffer
	m_gl->glGenTextures(1, &m_fboTextureId);
	m_gl->glBindTexture(GL_TEXTURE_2D, m_fboTextureId);
	m_gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	m_gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	m_gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	m_gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_gl->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, panoramaWidth, panoramaHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, NULL);

	// load textures and create framebuffers
	m_gl->glGenFramebuffers(1, &m_fboId);
	m_gl->glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
	m_gl->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fboTextureId, 0);
	m_gl->glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// create fbo shader
	m_program = new QOpenGLShaderProgram();
#ifdef USE_SHADER_CODE
	ADD_SHADER_FROM_CODE(m_program, "vert", "stitcher");
	ADD_SHADER_FROM_CODE(m_program, "frag", "blending");
#else
	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "./Shaders/stitcher.vert");
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "./Shaders/blending.frag");
#endif
	m_program->link();
	m_vertexAttr = m_program->attributeLocation("vertex");
	m_texCoordAttr = m_program->attributeLocation("texCoord");
	m_program->bind();

	int colorTextureIds[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	m_gl->glUniform1iv(m_program->uniformLocation(QString("colorMap")), 8, colorTextureIds);
	int alphaTextureIds[8] = { 8, 9, 10, 11, 12, 13, 14, 15 };
	m_gl->glUniform1iv(m_program->uniformLocation(QString("blendMap")), 8, alphaTextureIds);
	m_program->setUniformValue("viewCnt", m_viewCount);

	QMatrix4x4 matrix;
	matrix.ortho(-panoramaWidth / 2, panoramaWidth / 2, -panoramaHeight / 2, panoramaHeight / 2, -10.0f, 10.0f);
	matrix.translate(0, 0, -2);
	m_program->setUniformValue("matrix", matrix);
	m_program->release();

	levelScaleUnif = m_program->uniformLocation("levelScale");

	m_initialized = true;
}


void GLSLBlending::render(GLuint colorTextures[], GLuint alphaTextures[], int colorLevel, int alphaLevel)
{
	m_program->bind();
	m_gl->glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

	float width = panoramaWidth;
	float height = panoramaHeight;

	m_gl->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	m_gl->glClear(GL_COLOR_BUFFER_BIT);

	m_gl->glViewport(0, 0, width, height);

	for (int i = 0; i < m_viewCount; i++)
	{
		m_gl->glActiveTexture(GL_TEXTURE0 + i);
		m_gl->glBindTexture(GL_TEXTURE_2D, colorTextures[i]);

		m_gl->glActiveTexture(GL_TEXTURE8 + i);
		m_gl->glBindTexture(GL_TEXTURE_2D, alphaTextures[i]);
	}

	float levelScale = getLevelScale(colorLevel);
	m_program->setUniformValue(levelScaleUnif, getLevelScale(colorLevel - alphaLevel));

	GLfloat vertices[] = {
		-width / 2, -height / 2,
		-width / 2, height / 2,
		width / 2, height / 2,
		width / 2, -height / 2
	};

	GLfloat texCoords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f / levelScale,
		1.0f / levelScale, 1.0f / levelScale,
		1.0f / levelScale, 0.0f,
	};

	int vertexAttr = m_vertexAttr;
	int texCoordAttr = m_texCoordAttr;

	m_gl->glVertexAttribPointer(vertexAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	m_gl->glVertexAttribPointer(texCoordAttr, 2, GL_FLOAT, GL_FALSE, 0, texCoords);

	m_gl->glEnableVertexAttribArray(vertexAttr);
	m_gl->glEnableVertexAttribArray(texCoordAttr);

	m_gl->glDrawArrays(GL_QUADS, 0, 4);

	m_gl->glDisableVertexAttribArray(texCoordAttr);
	m_gl->glDisableVertexAttribArray(vertexAttr);

	m_gl->glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_program->release();
}

const int GLSLBlending::getWidth()
{
	return panoramaWidth;
}

const int GLSLBlending::getHeight()
{
	return panoramaHeight;
}