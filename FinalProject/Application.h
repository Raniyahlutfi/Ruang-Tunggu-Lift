#pragma once

#include "RenderEngine.h"
#include "Cube.h"
#include "Shader.h"

class Application :
    public RenderEngine
{
public:
    Application();
    ~Application();
private:
	Shader *shader;
	Cube* cube; 
	float angle;
	glm::vec3 viewPos;
	double lastFrameTime = glfwGetTime();
	void setupPerspective();
	void setupCamera();
	void setupLighting();
	void UpdateCameraDirection(double xpos, double ypos);
	virtual void Init();
	virtual void DeInit(); 
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow* window);
	const int windowWidth = 1280;
	const int windowHeight = 768;
	glm::vec3 entityPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	bool lampOn = true;
	bool skyOn = true;
	double lastLightToggled = 0;
	float yaw = -90.0f;
	float pitch = 0.0f;
	glm::vec3 viewDir = glm::vec3(0.0f, 0.0f, 0.0f);
	bool firstMouse = true;
	float lastX = windowWidth / 2.0f;
	float lastY = windowHeight / 2.0f;
};

