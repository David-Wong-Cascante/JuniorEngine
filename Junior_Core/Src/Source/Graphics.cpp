/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Graphics.cpp
* Description: Write the functionality of the window and the renderer under the same class
* Created: 20 Apr 2018
* Last Modified: 8 Aug 2019
*/


// Includes
#include "Graphics.h"
#ifdef _DEBUG
#include "MemoryLeakGuard.h"		// Memory Leak Guard
#endif

#include <iostream>					// IO streams
// Testing
#include <random>

#include "DefaultMesh.h"			// Default Mesh
#include "RenderJob.h"				// Render Jobs
#include "LinearMath.h"				// Linear Math Helper Functions
#include "Input.h"					// Class Input
#include "Texture.h"				// Texture
#include "Vec3.h"					// Vec3
#include "Mat3.h"					// Mat3
#include "TextureAtlas.h"			// Texture Atlas Tree
#include "Camera.h"					// Camera
#include "Debug.h"					// Debug
#include "EventManager.h"			// Event Manager

// Defines
#define MAX_ATLAS_SIZE 512
#define TEXTURE_ATLAS_POS 0

// Defining the Input's Friend Functions
void Junior::JoystickConnectionCallback(int joystick, int event);
void Junior::MouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
void Junior::MouseCursorCallback(GLFWwindow* window, double xPos, double yPos);
void Junior::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void Junior::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Initializing static names

std::string Junior::WindowResizeEvent::WindowResizeEventName = "WindowResize";
std::string Junior::WindowQuitEvent::WindowQuitEventName = "WindowQuit";

// Private Member Functions
Junior::Graphics::Graphics()
	: GameSystem("Graphics"), windowWidth_(0), windowHeight_(0), openGLVersionMajor_(0), openGLVersionMinor_(0),
							  windowHandle_(nullptr), mainCamera_(nullptr), orthographicMatrix_()
{
}

// Public Member Functions
bool Junior::Graphics::Load()
{
	// Debug print information
	Debug& debug = Debug::GetInstance();

	// Load the window and the context
	// Set the default window width and height
	windowWidth_ = 1920;
	windowHeight_ = 1080;

	// Initialize GLFW so that we can use its library
	if (!glfwInit())
	{
		debug.Print(debug.GetDebugLevelName(DebugLevel::ERROR));
		debug.PrintLn("Failed to create the window");
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
		debug.Print(debug.GetDebugLevelName(DebugLevel::ERROR));
		debug.PrintLn("Failed to create the window handle");
		return 0;
	}

	// Make the window's context
	glfwMakeContextCurrent(windowHandle_);
	glfwSwapInterval(1);

	// Initialize GLAD after we created the context
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		debug.Print<std::string>(debug.GetDebugLevelName(DebugLevel::ERROR));
		debug.PrintLn<std::string>("Failed to initialize the window");
		return 0;
	}
	
	// Check OpenGL's version
	char* openGLVersion = (char*)(glGetString(GL_VERSION));
	debug.Print(debug.GetDebugLevelName(DebugLevel::NOTIFICATION));
	debug.Print("Running OpenGL version ");
	debug.PrintLn(openGLVersion);

	glGetIntegerv(GL_MAJOR_VERSION, &openGLVersionMajor_);
	glGetIntegerv(GL_MINOR_VERSION, &openGLVersionMinor_);

	// Set up the input callbacks
	glfwSetKeyCallback(windowHandle_, Junior::KeyCallback);
	glfwSetMouseButtonCallback(windowHandle_, Junior::MouseButtonCallback);
	glfwSetCursorPosCallback(windowHandle_, Junior::MouseCursorCallback);
	glfwSetScrollCallback(windowHandle_, Junior::MouseScrollCallback);
	glfwSetJoystickCallback(Junior::JoystickConnectionCallback);
	glfwSetWindowSizeCallback(windowHandle_, WindowResizeCallback);
	glfwSetWindowCloseCallback(windowHandle_, WindowQuitCallback);

	// Set the back buffer's clear color
	glClearColor(0.2f, 0.4f, 0.6f, 1);
	// Set the blend mode
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	debug.Print(debug.GetDebugLevelName(DebugLevel::NOTIFICATION));
	debug.PrintLn("Creating the default shading program");

	//defaultProgram_ = new Junior::DrawProgram;
	//defaultProgram_->LoadFromDisk("..//Assets//Shaders//starter");
	// Generate the texture 
	debug.Print(debug.GetDebugLevelName(DebugLevel::NOTIFICATION));
	debug.PrintLn("Creating the texture atlas");

	atlas_ = new TextureAtlas(MAX_ATLAS_SIZE, MAX_ATLAS_SIZE, 4, 0);
	// Generate some pixels
	unsigned char* pixels = new unsigned char[MAX_ATLAS_SIZE * MAX_ATLAS_SIZE * 4];
	for (int y = 0; y < MAX_ATLAS_SIZE; ++y)
	{
		for (int x = 0; x < MAX_ATLAS_SIZE; ++x)
		{
			unsigned offset = 4 * (MAX_ATLAS_SIZE * y + x);
			pixels[offset + 0] = 255;
			pixels[offset + 1] = 0;
			pixels[offset + 2] = 255;
			pixels[offset + 3] = 255;
		}
	}
	
	// Fill the pixels
	atlas_->UpdatePixels(pixels);
	delete[] pixels;
	
	// Generate the texture array
	textureBank_ = new Texture(GL_TEXTURE_2D_ARRAY, false, GL_RGBA, GL_RGBA8, MAX_ATLAS_SIZE, MAX_ATLAS_SIZE, 2);
	textureBank_->AppendToArray2D(MAX_ATLAS_SIZE, MAX_ATLAS_SIZE, atlas_->GetPixels());

	return true;
}

bool Junior::Graphics::Initialize()
{
	// Debug printing
	Debug& debug = Debug::GetInstance();
	debug.Print(debug.GetDebugLevelName(DebugLevel::NOTIFICATION));
	debug.PrintLn("Initialize general vertex data for graphics");

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
	if (mainCamera_)
	{
		mainCamera_->UpdateProjection(ProjectionMode::ORTHOGRAPHIC, static_cast<float>(windowWidth_), static_cast<float>(windowHeight_), -5.0f, 5.0f);
	}
	//orthographicMatrix_ = Orthographic(-windowWidth_ / 2.0f, windowWidth_ / 2.0f, windowHeight_ / 2.0f, -windowHeight_ / 2.0f, -5.0f, 5.0f);
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

	// Bind each program and draw the meshes
	for (auto program = programs_.cbegin(); program != programs_.end(); ++program)
	{
		(*program)->Bind();
		// Update the camera
		GLuint projLoc = glGetUniformLocation((*program)->programID_, "camera");
		if (mainCamera_)
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, mainCamera_->GetCameraMatrix().m_);
		else
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, Identity().m_);

		// Set the texture atlas
		GLuint textureLoc = glGetUniformLocation((*program)->programID_, "diffuse");
		glActiveTexture(GL_TEXTURE0);
		textureBank_->BindTexture();
		glUniform1i(textureLoc, 0);

		// Draw the instanced meshes
		(*program)->Draw();

		textureBank_->UnbindTexture();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		(*program)->UnBind();
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
}

void Junior::Graphics::Unload()
{
	// Debug printing
	Debug& debug = Debug::GetInstance();
	debug.Print(debug.GetDebugLevelName(DebugLevel::NOTIFICATION));
	debug.PrintLn("Unloading Graphics");
	// Delete the meshes
	for (auto citer = programs_.cbegin(); citer != programs_.cend(); ++citer)
	{
		(*citer)->CleanUp();
		delete (*citer);
	}
	programs_.clear();
	// Delete the texture atlas
	delete atlas_;
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

Junior::TextureAtlas* Junior::Graphics::GetTextureAtlas()
{
	return atlas_;
}

int Junior::Graphics::GetWindowWidth() const
{
	return windowWidth_;
}

int Junior::Graphics::GetWindowHeight() const
{
	return windowHeight_;
}

Junior::Graphics& Junior::Graphics::GetInstance()
{
	static Graphics graphics;
	return graphics;
}

void Junior::WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	// Get the event manager
	EventManager& eventManager = EventManager::GetInstance();
	// Change the dimensions of the window via the pointer
	// Send a new window event
	Graphics* g = (Graphics*) glfwGetWindowUserPointer(window);

	int oldWidth = g->GetWindowWidth();
	int oldHeight = g->GetWindowHeight();
	// Send a window resize event to the event manager
	WindowResizeEvent* windowEvent = new WindowResizeEvent;
	windowEvent->oldWidth_ = oldWidth;
	windowEvent->oldHeight_ = oldHeight;
	windowEvent->newWidth_ = width;
	windowEvent->newHeight_ = height;
	eventManager.SendEvent(windowEvent);

	g->SetDimensions(width, height);
}

void Junior::WindowQuitCallback(GLFWwindow* window)
{
	// Get the event manager
	EventManager& eventManager = EventManager::GetInstance();
	// Send a window quit event
	eventManager.SendEvent(new WindowQuitEvent);
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
	Debug& debug = Debug::GetInstance();
	// Ignore notifications
	//if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
	//	return;
	// Get the correct name for the error
	const char* errorName = IdentifyGLError(id);
	const char* severityName = IdentifyGLSeverity(severity);

	// Print the error message
	if (type == GL_DEBUG_TYPE_ERROR)
	{
		debug.Print(debug.GetDebugLevelName(DebugLevel::ERROR));
	}
	else
	{
		debug.Print(debug.GetDebugLevelName(DebugLevel::NOTIFICATION));
	}

	debug.Print("Type: ");
	debug.Print(errorName);
	debug.Print(", Severity: ");
	debug.PrintLn(severityName);
	debug.Print("\"");
	debug.Print(message);
	debug.PrintLn("\"");
}