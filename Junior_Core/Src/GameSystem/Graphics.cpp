/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Graphics.cpp
* Description: Write the functionality of the window and the renderer under the same class
* Created: 20-Apr-2018
* Last Modified: 14-Feb-2019
*/


// Includes //
#include "Graphics.h"
#ifdef _DEBUG
#include "MemoryLeakGuard.h"		// Memory Leak Guard
#endif

#include <iostream>					// IO streams
// Testing
#include <random>

#include "DrawProgram.h"			// Draw Program
#include "RenderJob.h"				// Render Jobs
#include "LinearMath.h"				// Linear Math Helper Functions
#include "Input.h"					// Class Input
#include "Texture.h"				// Texture
#include "Vec3.h"					// Vec3
#include "Mat3.h"					// Mat3
#include "TextureAtlas.h"			// Texture Atlas Tree

// Defines
#define MAX_ATLAS_SIZE 512
#define TEXTURE_ATLAS_POS 0

// Defining the Input's Friend Functions
void Junior::JoystickConnectionCallback(int joystick, int event);
void Junior::MouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
void Junior::MouseCursorCallback(GLFWwindow* window, double xPos, double yPos);
void Junior::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void Junior::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Private Member Functions
Junior::Graphics::Graphics()
	: GameSystem("Graphics")
{
}

Junior::Graphics::Graphics(const Graphics& graphics)
	: GameSystem("Graphics")
{
}

Junior::Graphics& Junior::Graphics::operator=(const Graphics& other)
{
	return *this;
}

// Public Member Functions
bool Junior::Graphics::Load()
{
	// Load the window and the context
	// Set the default window width and height
	windowWidth_ = 1920;
	windowHeight_ = 1080;

	// Initialize GLFW so that we can use its library
	if (!glfwInit())
	{
#ifdef _DEBUG
		std::cout << "Failed to create the window" << std::endl;
#endif
		return 0;
	}

	// Set the window's hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create the window
	windowHandle_ = glfwCreateWindow(windowWidth_, windowHeight_, "Junior Game Engine", NULL, NULL);
	if (!windowHandle_)
	{
		return 0;
	}

	// Make the window's context
	glfwMakeContextCurrent(windowHandle_);
	glfwSwapInterval(1);

	// Initialize GLAD after we created the context
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
#ifdef _DEBUG
		std::cout << "Failed to initialize GLEW" << std::endl;
#endif
		return 0;
	}
	
	// Check OpenGL's version
	char* openGLVersion = (char*)(glGetString(GL_VERSION));
#ifdef _DEBUG
	std::cout << "Running OpenGL Version " << openGLVersion << std::endl;
#endif
	glGetIntegerv(GL_MAJOR_VERSION, &openGLVersionMajor_);
	glGetIntegerv(GL_MINOR_VERSION, &openGLVersionMinor_);

	// Set up the input callbacks
	glfwSetKeyCallback(windowHandle_, Junior::KeyCallback);
	glfwSetMouseButtonCallback(windowHandle_, Junior::MouseButtonCallback);
	glfwSetCursorPosCallback(windowHandle_, Junior::MouseCursorCallback);
	glfwSetScrollCallback(windowHandle_, Junior::MouseScrollCallback);
	glfwSetJoystickCallback(Junior::JoystickConnectionCallback);
	glfwSetWindowSizeCallback(windowHandle_, WindowResizeCallback);

	// Set the back buffer's clear color
	glClearColor(0.2f, 0.4f, 0.6f, 1);

	// Set up a pointer to make sure we can access this instance of the class whenever we need to change something graphics-wise
	glfwSetWindowUserPointer(windowHandle_, this);

	// Set up the OpenGL debug error messages when the major version is >= 4
	if (openGLVersionMajor_ >= 4)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);
	}

	// defaultProgram_ = 0;
	// Set up the draw program used to draw the triangle
	defaultProgram_ = new Junior::DrawProgram;
	defaultProgram_->LoadFromDisk("..//Assets//Shaders//starter");
	// Generate the texture 
	atlas_ = new TextureAtlas(MAX_ATLAS_SIZE, MAX_ATLAS_SIZE, 4);
	// Generate some pixels
	unsigned char* pixels = new unsigned char[MAX_ATLAS_SIZE * MAX_ATLAS_SIZE * 4];
	for (int y = 0; y >= MAX_ATLAS_SIZE; ++y)
	{
		for (int x = 0; x < MAX_ATLAS_SIZE; ++x)
		{
			unsigned offset = 4 * (MAX_ATLAS_SIZE * y + x);
			pixels[offset + 0] = 255;
			pixels[offset + 1] = 255;
			pixels[offset + 2] = 255;
			pixels[offset + 3] = 255;
		}
	}
	
	// Fill the pixels
	atlas_->UpdatePixels(pixels);
	delete[] pixels;
	
	// Generate the texture array
	textureBank_ = new Texture(GL_TEXTURE_2D_ARRAY, false, GL_RGBA, GL_RGB8, MAX_ATLAS_SIZE, MAX_ATLAS_SIZE, 2);
	textureBank_->AppendToArray2D(MAX_ATLAS_SIZE, MAX_ATLAS_SIZE, atlas_->GetPixels());
	//textureBank_->AppendedLoadToTextureArray2D("..//Assets//Private_Images//SmashBall.png");

	return true;
}

bool Junior::Graphics::Initialize()
{
	// Delete any previous data if it existed
	glDeleteBuffers(1, &renderJobBuffer_);
	glDeleteBuffers(1, &vbo_);
	glDeleteVertexArrays(1, &vao_);

	// Set up the Vertex Array Object to draw a single triangle
	glGenVertexArrays(1, &vao_);

	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &renderJobBuffer_);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	float randomVertices[] = {
		// Vertices,			Texture Coords
		-0.5f,-0.5f, 0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,
	};
	
	// The buffer for all vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(randomVertices), randomVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(3 * sizeof(float)));

	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 0);

	// The buffer for all render job data
	glBindBuffer(GL_ARRAY_BUFFER, renderJobBuffer_);
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);

	// Transformation Matrix
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(RenderJob), 0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(RenderJob), reinterpret_cast<void*>(sizeof(float) * 1 * 4));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(RenderJob), reinterpret_cast<void*>(sizeof(float) * 2 * 4));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(RenderJob), reinterpret_cast<void*>(sizeof(float) * 3 * 4));

	// UV Coordinate Modification Data
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(RenderJob), reinterpret_cast<void*>(sizeof(float) * 4 * 4));

	// Texture Selection Data
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(RenderJob), reinterpret_cast<void*>(sizeof(float) * 5 * 4));

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);

	CHECK_GL_ERROR();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Set the orthographic matrix at the start
	orthographicMatrix_ = Orthographic(-windowWidth_/2.0f, windowWidth_/2.0f, windowHeight_/2.0f, -windowHeight_/2.0f, -5.0f, 5.0f);
	//orthographicMatrix_ = Perspective(90.0f, static_cast<float>(windowWidth_), static_cast<float>(windowHeight_), -5.0f, 100.f);
	//orthographicMatrix_ = Identity();

	return true;
}

bool Junior::Graphics::WindowRequestClosed()
{
	return glfwWindowShouldClose(windowHandle_);
}

void Junior::Graphics::SetDimensions(int width, int height)
{
	this->windowWidth_ = width;
	this->windowHeight_ = height;
	//float aspectRatio = (float)windowHeight_ / (float)windowWidth_;
	orthographicMatrix_ = Orthographic(-windowWidth_ / 2.0f, windowWidth_ / 2.0f, windowHeight_ / 2.0f, -windowHeight_ / 2.0f, -5.0f, 5.0f);
	//orthographicMatrix_ = Perspective(90.0f, static_cast<float>(width), static_cast<float>(height), 0.01f, 1000.f);
	glViewport(0, 0, width, height);
}

void Junior::Graphics::Update(double dt)
{
	// Initialization of static variables
	static double counter = 0;
	static int ticks = 0;

	// Change the window's title to include the fps
	++ticks;
	counter += dt;
	if (counter >= 1)
	{
		std::string name = "Junior Game Engine | FPS: ";
		name += std::to_string(ticks);
		glfwSetWindowTitle(windowHandle_, name.c_str());
		counter -= 1;
		ticks = 0;
	}
}

void Junior::Graphics::Render()
{
	// Clear the back buffer if necessary
	// Which for now, its pretty much always
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind the program and draw the triangle
	
	if (defaultProgram_)
	{
		defaultProgram_->Bind();
		// Do the instanced rendering
		glBindVertexArray(vao_);

		// Fill in the render job data
		size_t renderJobBufferSize = sizeof(RenderJob) * renderJobs_.size();
		readyToRenderJobs_.clear();
		readyToRenderJobs_.reserve(renderJobs_.size());
		for (unsigned i = 0; i < renderJobs_.size(); ++i)
		{
			readyToRenderJobs_.push_back(*renderJobs_[i]);
		}

		glBindBuffer(GL_ARRAY_BUFFER, renderJobBuffer_);
		glBufferData(GL_ARRAY_BUFFER, renderJobBufferSize, nullptr, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, renderJobBufferSize, readyToRenderJobs_.data());
		CHECK_GL_ERROR();

		// Render the all of the render jobs (instanced)
		GLuint projLoc = glGetUniformLocation(defaultProgram_->programID_, "orthographic");
		glUniformMatrix4fv(projLoc, 1, GL_TRUE, orthographicMatrix_.m_);

		// Set the temporal texture
		GLuint textureLoc = glGetUniformLocation(defaultProgram_->programID_, "diffuse");
		glActiveTexture(GL_TEXTURE0);
		textureBank_->BindTexture();
		glUniform1i(textureLoc, 0);
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);
		glEnableVertexAttribArray(6);
		glEnableVertexAttribArray(7);

		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, static_cast<GLsizei>(renderJobs_.size()));

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
		glDisableVertexAttribArray(5);
		glDisableVertexAttribArray(6);
		glDisableVertexAttribArray(7);

		textureBank_->UnbindTexture();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	// And swap the buffers
	glfwSwapBuffers(windowHandle_);
}

void Junior::Graphics::PollWindow()
{
	glfwPollEvents();
}

void Junior::Graphics::Shutdown()
{
	// Delete all the Vertex Buffer stuff
	glDeleteBuffers(1, &renderJobBuffer_);
	glDeleteBuffers(1, &vbo_);
	glDeleteVertexArrays(1, &vao_);
}

void Junior::Graphics::Unload()
{
	// Delete the texture atlas
	delete atlas_;
	// Delete the shader program
	defaultProgram_->CleanUp();
	delete defaultProgram_;
	//manager_->DeAllocate(defaultProgram_);
	// Delete the texture
	delete textureBank_;
	//manager_->DeAllocate(textureAtlas_);
	// Terminate all the GLFW stuff
	glfwWindowShouldClose(windowHandle_);
	glfwTerminate();
}

void Junior::Graphics::UpdateTextureAtlas()
{
	textureBank_->ModifyTextureArray(TEXTURE_ATLAS_POS, atlas_->GetPixels());
}

Junior::RenderJob * Junior::Graphics::GetNewRenderJob()
{
	RenderJob* newJob = new /*(manager_->Allocate(sizeof(RenderJob)))*/ RenderJob();
	renderJobs_.push_back(newJob);
	return newJob;
}

Junior::TextureAtlas* Junior::Graphics::GetTextureAtlas()
{
	return atlas_;
}

void Junior::Graphics::RemoveRenderJob(RenderJob* renderJob)
{
	for (unsigned i = 0; i < renderJobs_.size(); ++i)
	{
		if (renderJobs_[i] == renderJob)
		{
			renderJobs_.erase(renderJobs_.begin() + i);
		}
	}
}

Junior::Graphics& Junior::Graphics::GetInstance()
{
	static Graphics graphics;
	return graphics;
}

void Junior::WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	// Change the dimensions of the window via the pointer
	Graphics* g = (Graphics*) glfwGetWindowUserPointer(window);
	g->SetDimensions(width, height);
}

const char* Junior::IdentifyGLError(unsigned id)
{
	switch (id)
	{
	case GL_INVALID_ENUM:
		return "INVALID ENUM";
	case GL_INVALID_VALUE:
		return "INVALID VALUE";
	case GL_INVALID_OPERATION:
		return "INVALID OPERATION";
	case GL_STACK_OVERFLOW:
		return "STACK OVERFLOW";
	case GL_STACK_UNDERFLOW:
		return "STACK UNDERFLOW";
	case GL_OUT_OF_MEMORY:
		return "OUT OF MEMORY - CONTEXTS OR OBJECT MAY BE UNDEFINED";
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "INVALIED FRAMEBUFFER OPERATION";
	case GL_CONTEXT_LOST:
		return "CONTEXT LOST";
	default:
		return "UNKNOWN";
	}
}

const char* Junior::IdentifyGLSeverity(unsigned severity)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		return "SEVERITY HIGH";
	case GL_DEBUG_SEVERITY_MEDIUM:
		return "SEVERITY MEDIUM";
	case GL_DEBUG_SEVERITY_LOW:
		return "SEVERITY LOW";
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		return "NOTIFICATION";
	default:
		return "UKNOWN SEVERITY";
	}
}

void GLAPIENTRY Junior::MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const char * message, const void * userParam)
{
	// Ignore notifications
	//if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
	//	return;
	// Get the correct name for the error
	const char* errorName = IdentifyGLError(id);
	const char* severityName = IdentifyGLSeverity(severity);

	// Print the error message
	std::cout << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "GL ERROR -> " : "")
		<< "type: " << errorName
		<< ", severity: " << severityName
		<< std::endl << "\"" << message << "\"" << std::endl;
}