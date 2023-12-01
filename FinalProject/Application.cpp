#include "Application.h"

Application::Application()
{
	angle = 0;
}

Application::~Application()
{
}

void Application::setupPerspective()
{
	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 1000.0f);
	shader->setMat4("projection", projection);
}

void Application::setupCamera()
{
	// LookAt camera (position, target/direction, up)
	viewPos = glm::vec3(0, 1, 5);
	glm::mat4 view = glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	shader->setMat4("view", view);
}

void Application::setupLighting()
{
	// set lighting attributes
	glm::vec3 lightPos = glm::vec3(4, 4, 0);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", viewPos);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader->setVec3("lightColor", lightColor);
}

void Application::Init()
{
	// Build a lighting map shader
	shader = new Shader("cube.vert", "cube.frag");
	shader->Init();
	// Create instance of cube
	cube = new Cube(shader);
	cube->Init();
	cube->SetRotation(0, 0, 1, 0);

	// setup perspective 
	setupPerspective();
	// setup camera
	setupCamera();
	// setup lighting
	setupLighting();
}

void Application::DeInit()
{
	delete cube;
}

void Application::Update(double deltaTime)
{
	lastLightToggled += deltaTime;
	angle += (float)((deltaTime * 0.5f) / 1000);
	ProcessInput(this->window);
}

void Application::Render()
{
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetBackgroundColor(94, 232, 247);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	//Human
		// Create the Head
		cube->SetColor(0.0f, 0.0f, 0.0f);
		cube->SetPosition(0.0f, 0.55f, 0.0f);
		cube->SetScale(0.75f, 0.5f, 0.5f);
		cube->Draw();

		// Create the Torso
		cube->SetColor(100.0f, 100.0f, 100.0f);
		cube->SetPosition(0.0f, -0.2f, 0.0f);
		cube->SetScale(0.75f, 1.0f, 0.3f);
		cube->Draw();

		// Create the Limbs (arms and legs)
		cube->SetColor(125.0f, 125.0f, 125.0f);

		// Left arm
		cube->SetPosition(-0.55f, -0.2f, 0.0f);
		cube->SetScale(0.2f, 0.75f, 0.2f);
		cube->Draw();

		// Right arm
		cube->SetPosition(0.55f, -0.2f, 0.0f);
		cube->SetScale(0.2f, 0.75f, 0.2f);
		cube->Draw();

		// Left leg
		cube->SetPosition(-0.2f, -1.4f, 0.0f);
		cube->SetScale(0.3f, 1.4f, 0.3f);
		cube->Draw();

		// Right leg
		cube->SetPosition(0.2f, -1.4f, 0.0f);
		cube->SetScale(0.3f, 1.4f, 0.3f);
		cube->Draw();

	//The Wall
		// Create the first wall (back wall)
		cube->SetColor(250.0f, 250.0f, 250.0f);
		cube->SetPosition(0.0f, 0.0f, -5.0f);
		cube->SetScale(10.0f, 5.0f, 0.1f);
		cube->Draw();

		// Set the color for the wall
		cube->SetColor(50.0f, 50.0f, 50.0f);

		// Create the second wall (left wall)
		cube->SetPosition(-5.0f, 0.0f, 0.0f);
		cube->SetScale(0.1f, 5.0f, 10.0f);
		cube->Draw();

		// Create the third wall (right wall)
		cube->SetPosition(5.0f, 0.0f, 0.0f);
		cube->SetScale(0.1f, 5.0f, 10.0f);
		cube->Draw();

	//The Roof & Floor 
		// Create the Roof
		cube->SetColor(250.0f, 250.0f, 250.0f);
		cube->SetPosition(0.0f, 2.55f, 0.0f);
		cube->SetScale(10.0f, 0.1f, 10.0f);
		cube->Draw();

		// Set the color
		cube->SetColor(220.0f, 220.0f, 220.0f);

		// Create the Roof2
		cube->SetPosition(0.0f, 2.35f, 0.0f);
		cube->SetScale(5.0f, 0.2f, 5.0f);
		cube->Draw();

		// Create the floor
		cube->SetPosition(0.0f, -1.45f, 0.0f);
		cube->SetScale(5.0f, 0.2f, 5.0f);
		cube->Draw();

		// Create the floor2
		cube->SetColor(50.0f, 50.0f, 50.0f);
		cube->SetPosition(0.0f, -1.5f, 0.0f);
		cube->SetScale(10.0f, 0.1f, 10.0f);
		cube->Draw();

	//The Lamp
		// Set the color for the lamp
		cube->SetColor(255.0f, 255.0f, 255.0f);

		// Create the first lamp
		cube->SetPosition(1.2f, 2.25f, 1.2f);
		cube->SetScale(0.25f, 0.15f, 0.25f);
		cube->Draw();

		// Create the second lamp
		cube->SetPosition(-1.2f, 2.25f, 1.2f);
		cube->SetScale(0.25f, 0.15f, 0.25f);
		cube->Draw();

		// Create the third lamp
		cube->SetPosition(1.2f, 2.25f, -1.2f);
		cube->SetScale(0.25f, 0.15f, 0.25f);
		cube->Draw();

		// Create the fourth lamp
		cube->SetPosition(-1.2f, 2.25f, -1.2f);
		cube->SetScale(0.25f, 0.15f, 0.25f);
		cube->Draw();

	//The Elevator
		// Set the color for the elevator body
		cube->SetColor(70.0f, 70.0f, 70.0f); // Gray color for the elevator

		// Create the first elevator body on left wall
		cube->SetPosition(-4.80f, 0.0f, 2.0f);
		cube->SetScale(1.0f, 3.0f, 2.0f);
		cube->Draw();

		// Create the second elevator body on left wall
		cube->SetPosition(-4.80f, 0.0f, -2.0f);
		cube->SetScale(1.0f, 3.0f, 2.0f);
		cube->Draw();

		// Create the third elevator body on right wall
		cube->SetPosition(4.80f, 0.0f, -2.0f);
		cube->SetScale(1.0f, 3.0f, 2.0f);
		cube->Draw();

		// Create the fourth elevator body on right wall
		cube->SetPosition(4.80f, 0.0f, 2.0f);
		cube->SetScale(1.0f, 3.0f, 2.0f);
		cube->Draw();

		// Set the color for the door
		cube->SetColor(100.0f, 100.0f, 100.0f); // Gray color for the door

		// Create the first elevator door on left wall
		cube->SetPosition(-4.75f, 0.0f, 2.0f);
		cube->SetScale(1.0f, 3.0f, 1.5f);
		cube->Draw();

		// Create the second elevator door on left wall
		cube->SetPosition(-4.75f, 0.0f, -2.0f);
		cube->SetScale(1.0f, 3.0f, 1.5f);
		cube->Draw();

		// Create the third elevator door on right wall
		cube->SetPosition(4.75f, 0.0f, -2.0f);
		cube->SetScale(1.0f, 3.0f, 1.5f);
		cube->Draw();

		// Create the fourth elevator door on right wall
		cube->SetPosition(4.75f, 0.0f, 2.0f);
		cube->SetScale(1.0f, 3.0f, 1.5f);
		cube->Draw();

		// Set Light gray color for the button
		cube->SetColor(100.0f, 100.0f, 100.0f);

		//Create button lift left
		cube->SetPosition(-4.75f, 0.3f, 0.0f);
		cube->SetScale(0.15f, 0.5f, 0.2f);
		cube->Draw();

		//Create button lift right
		cube->SetPosition(4.75f, 0.3f, 0.0f);
		cube->SetScale(0.15f, 0.5f, 0.2f);
		cube->Draw();

	// Trash Bin
		// Trash Bin Left
		// Create the Top Trash
		cube->SetColor(120.0f, 120.0f, 120.0f);
		cube->SetPosition(-4.75f, -0.4f, 0.0f);
		cube->SetScale(0.7f, 0.3f, 0.5f);
		cube->Draw();

		// Create the Body Trash
		cube->SetColor(110.0f, 110.0f, 110.0f);
		cube->SetPosition(-4.75f, -1.0f, 0.0f);
		cube->SetScale(0.7f, 1.0f, 0.5f);
		cube->Draw();

		// Trash Bin Right
		// Create the Top Trash
		cube->SetColor(120.0f, 120.0f, 120.0f);
		cube->SetPosition(4.75f, -0.4f, 0.0f);
		cube->SetScale(0.7f, 0.3f, 0.5f);
		cube->Draw();

		// Create the Body Trash
		cube->SetColor(110.0f, 110.0f, 110.0f);
		cube->SetPosition(4.75f, -1.0f, 0.0f);
		cube->SetScale(0.7f, 1.0f, 0.5f);
		cube->Draw();

	//The Chair
		// Draw Chair
		cube->SetColor(100.0f, 100.0f, 100.0f);

		// Create the seat
		cube->SetPosition(0.0f, -0.75f, -3.45f); // Adjust the position of the chair
		cube->SetScale(2.2f, 0.1f, 1.3f);
		cube->Draw();

		// Create the backrest
		cube->SetPosition(0.0f, -0.4f, -4.0f); // Adjust the position of the backrest
		cube->SetScale(2.2f, 0.9f, 0.2f);
		cube->Draw();

		// Create the four legs
		cube->SetPosition(-1.0f, -1.3f, -3.1f); // Adjust the position of the legs
		cube->SetScale(0.2f, 1.0f, 0.2f);
		cube->Draw();

		cube->SetPosition(1.0f, -1.3f, -3.1f); // Adjust the position of the legs
		cube->SetScale(0.2f, 1.0f, 0.2f);
		cube->Draw();

		cube->SetPosition(-1.0f, -1.3f, -4.0f); // Adjust the position of the legs
		cube->SetScale(0.2f, 1.0f, 0.2f);
		cube->Draw();

		cube->SetPosition(1.0f, -1.3f, -4.0f); // Adjust the position of the legs
		cube->SetScale(0.2f, 1.0f, 0.2f);
		cube->Draw();

	glDisable(GL_DEPTH_TEST);

}

void Application::UpdateCameraDirection(double xpos, double ypos)
{
	// Update yaw dan pitch berdasarkan input mouse
	yaw += xpos;
	pitch += ypos;

	// Batasi pitch agar tidak melebihi batas atas dan bawah
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	// Hitung vektor arah kamera berdasarkan yaw dan pitch
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	// Normalisasi vektor arah kamera
	viewDir = glm::normalize(front);

	// Perbarui matriks pandangan (view matrix)
	glm::mat4 view = glm::lookAt(viewPos, viewPos + viewDir, glm::vec3(0, 1, 0));
	shader->setMat4("view", view);
}


void Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	// Faktor sensitivitas mouse
	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	// Update orientasi kamera berdasarkan input mouse
	UpdateCameraDirection(xoffset, yoffset);

	// Fixed camera movement speed
	float fixedMovementSpeed = 0.05f;

	// Update camera position based on keyboard input
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		viewPos += fixedMovementSpeed * viewDir;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		viewPos -= fixedMovementSpeed * viewDir;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		viewPos -= glm::normalize(glm::cross(viewDir, glm::vec3(0.0f, 1.0f, 0.0f))) * fixedMovementSpeed;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		viewPos += glm::normalize(glm::cross(viewDir, glm::vec3(0.0f, 1.0f, 0.0f))) * fixedMovementSpeed;


	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && lastLightToggled > 200) {
		lampOn = !lampOn;
		lastLightToggled = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && lastLightToggled > 200) {
		skyOn = !skyOn;
		lastLightToggled = 0;
	}
}



int main(int argc, char** argv) {
	Application app = Application();
	app.Start("Cube Example",
		1366, 768,
		false,
		false);
}