#include <engine.h>
#include <logging.h>
#include <GLFW/glfw3.h>

Camera* camera;
Renderer* render;
Renderer* light;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	camera->EulerAngle(xpos, ypos);
}

int main(int argc, char* argv[]) {
	if (!glfwInit()) { LOG(ERROR, "Cannot Initialize GLFW!"); }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Tridme Engine", NULL, NULL);

	if (!window) {
		LOG(ERROR, "Cannot create GLFW window!");
		return -1;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		LOG(ERROR, "Cannot load OpenGL process!");
		return -1;
		glfwTerminate();
	}

	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
		glfwSetCursorPosCallback(window, mouse_callback);

		glEnable(GL_DEPTH_TEST);

		
		Shader* shader 			= new Shader("Color.shader");
		Shader* lightShader = new Shader("Light.shader");
		camera = new Camera((float) 800, (float) 600, 0.1f, 1000.0f, 
                    	  glm::vec3(0.0f, 0.0f, 6.0f));
		
		/* Object */
		render = new Renderer(MESH_TYPE::MESH_CUBE, camera); 

		render->SetShader(shader);
		render->SetPosition(glm::vec3(0.0f));
		render->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
		render->SetScale(glm::vec3(3.0f));

		shader->Bind();
		shader->SetUniform3f("objectColor", render->GetColor().x, render->GetColor().y, render->GetColor().z);
		shader->SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
		shader->SetUniform3f("lightPosition", 8.0f, 8.0f, 8.0f);
		shader->SetUniform3f("viewPosition", camera->getCameraPosition().x, camera->getCameraPosition().y, camera->getCameraPosition().z);

		shader->SetUniform3f("material.ambient", 1.0f, 0.5f, 0.31f);
		shader->SetUniform3f("material.diffuse", 1.0f, 0.5f, 0.31f);
		shader->SetUniform3f("material.specular", 0.5f, 0.5f, 0.5f);
		shader->SetUniform1f("material.shininess", 32.0f);


		/* End of object */
		light = new Renderer(MESH_TYPE::MESH_CUBE, camera);
		light->SetShader(lightShader);
		light->SetPosition(glm::vec3(3.0f, 3.0f, 10.0f));

		while (!glfwWindowShouldClose(window)) {
			/* Each frame */
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			camera->Move(window, deltaTime)	;
			render->DrawMesh();
			light->DrawMesh();

			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	}

	glfwTerminate();
	return 0;
}