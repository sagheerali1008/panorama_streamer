#include "GLSLPyramidSum.h"
#include "define.h"

GLSLMergeTexture::GLSLMergeTexture(QObject *parent) : GLSLProgram(parent)
{
}

GLSLMergeTexture::~GLSLMergeTexture()
{
}

void GLSLMergeTexture::initialize(int panoWidth, int panoHeight)
{
	this->panoramaWidth = panoWidth;
	this->panoramaHeight = panoHeight;

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
	ADD_SHADER_FROM_CODE(m_program, "frag", "merge");
#else
	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "./Shaders/stitcher.vert");
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "./Shaders/merge.frag");
#endif
	m_program->link();
	m_vertexAttr = m_program->attributeLocation("vertex");
	m_texCoordAttr = m_program->attributeLocation("texCoord");
	m_program->bind();

	m_program->setUniformValue("texture1", 0);
	m_program->setUniformValue("texture2", 1);

	QMatrix4x4 matrix;
	matrix.ortho(-panoramaWidth / 2, panoramaWidth / 2, -panoramaHeight / 2, panoramaHeight / 2, -10.0f, 10.0f);
	matrix.translate(0, 0, -2);
	m_program->setUniformValue("matrix", matrix);
	m_program->release();

	GLSLProgram::initialize();
}


void GLSLMergeTexture::render(GLuint texture1, GLuint texture2)
{
	m_program->bind();
	m_gl->glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

	float width = panoramaWidth;
	float height = panoramaHeight;

	m_gl->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	m_gl->glClear(GL_COLOR_BUFFER_BIT);

	m_gl->glViewport(0, 0, width, height);

	m_gl->glActiveTexture(GL_TEXTURE0);
	m_gl->glBindTexture(GL_TEXTURE_2D, texture1);
	m_gl->glActiveTexture(GL_TEXTURE1);
	m_gl->glBindTexture(GL_TEXTURE_2D, texture2);

	GLfloat vertices[] = {
		-width / 2, -height / 2,
		-width / 2, height / 2,
		width / 2, height / 2,
		width / 2, -height / 2
	};

	GLfloat texCoords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
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

void GLSLMergeTexture::clear()
{
	m_program->bind();
	m_gl->glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

	float width = panoramaWidth;
	float height = panoramaHeight;

	//m_gl->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	m_gl->glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	m_gl->glClear(GL_COLOR_BUFFER_BIT);

	m_gl->glViewport(0, 0, width, height);

	m_gl->glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_program->release();
}

const int GLSLMergeTexture::getWidth()
{
	return panoramaWidth;
}

const int GLSLMergeTexture::getHeight()
{
	return panoramaHeight;
}
////////////////

GLSLPyramidSum::GLSLPyramidSum(QObject *parent) : GLSLProgram(parent)
, m_merge1(NULL)
, m_merge2(NULL)
{
}

GLSLPyramidSum::~GLSLPyramidSum()
{
	if (m_merge1)
	{
		delete m_merge1;
		m_merge1 = NULL;
	}
	if (m_merge2)
	{
		delete m_merge2;
		m_merge2 = NULL;
	}
}

void GLSLPyramidSum::initialize(int panoWidth, int panoHeight)
{
	this->panoramaWidth = panoWidth;
	this->panoramaHeight = panoHeight;

	m_merge1 = new GLSLMergeTexture();
	m_merge1->setGL(m_gl, m_functions_2_0);
	m_merge1->initialize(panoWidth, panoHeight);
	m_merge2 = new GLSLMergeTexture();
	m_merge2->setGL(m_gl, m_functions_2_0);
	m_merge2->initialize(panoWidth, panoHeight);
	clear();
	
	GLSLProgram::initialize();
}

void GLSLPyramidSum::clear()
{
	lastTexture = -1;
	m_currentMerge = 1;
	m_merge2->clear();
}

void GLSLPyramidSum::render(GLuint texture)
{
	if (lastTexture == -1)
	{
		m_merge1->render(m_merge2->getTargetTexture(), texture);
		lastTexture = m_merge1->getTargetTexture();
		m_currentMerge = 2;
	}
	else
	{
		if (m_currentMerge == 1)
		{
			m_merge1->render(lastTexture, texture);
			lastTexture = m_merge1->getTargetTexture();
			m_currentMerge = 2;
		}
		else
		{
			m_merge2->render(lastTexture, texture);
			lastTexture = m_merge2->getTargetTexture();
			m_currentMerge = 1;
		}
	}
}

const int GLSLPyramidSum::getWidth()
{
	return panoramaWidth;
}

const int GLSLPyramidSum::getHeight()
{
	return panoramaHeight;
}

int GLSLPyramidSum::getTargetTexture()
{
	return lastTexture;
}