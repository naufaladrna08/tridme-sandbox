#include <engine.h>
#include <logging.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace Tridme;

Camera* camera;
Renderer* render;
Renderer* light;
Window* window;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(int argc, char const *argv[]) {
	window = new Window(1280, 720, "Tridme Engine");
	window->Run();

	return 0;
}


// void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
// 	camera->EulerAngle(xpos, ypos);
// }

// int main(int argc, char* argv[]) {
// 	if (!glfwInit()) { LOG(ERROR, "Cannot Initialize GLFW!"); }

// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// 	window = new Window(1280, 720, "Tridme Engine");

// 	{
// 		/* Setup ImGUI context */
// 		IMGUI_CHECKVERSION();
// 		ImGui::CreateContext();
// 		ImGuiIO& io = ImGui::GetIO(); (void) io;
// 		ImGui::StyleColorsDark();

// 		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

// 		ImGui_ImplGlfw_InitForOpenGL(window->GetInstance(), true);
//     ImGui_ImplOpenGL3_Init("#version 330");

// 		/* ImGui state */
// 		bool show_demo_window = true;
// 		bool show_another_window = true;
// 		ImVec4 clear_color = ImVec4(0.43f, 0.55f, 0.12f, 1.0f);

// 		// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
// 		// glfwSetCursorPosCallback(window, mouse_callback);

// 		glEnable(GL_DEPTH_TEST);


// 		Shader* shader 			= new Shader("Color.shader");
// 		Shader* lightShader = new Shader("Light.shader");
// 		camera = new Camera((float) 800, (float) 600, 0.1f, 1000.0f, 
//                     	  glm::vec3(0.0f, 0.0f, 10.0f));
		
// 		/* Object */
// 		render = new Renderer(MESH_TYPE::MESH_CUBE, camera); 

// 		render->SetShader(shader);
// 		render->SetPosition(glm::vec3(0.0f));
// 		render->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
// 		render->SetScale(glm::vec3(3.0f));

// 		shader->Bind();
// 		shader->SetUniform3f("objectColor", render->GetColor().x, render->GetColor().y, render->GetColor().z);
// 		shader->SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
// 		shader->SetUniform3f("lightPosition", 8.0f, 8.0f, 8.0f);
// 		shader->SetUniform3f("viewPosition", camera->getCameraPosition().x, camera->getCameraPosition().y, camera->getCameraPosition().z);

// 		shader->SetUniform3f("material.ambient", 1.0f, 0.5f, 0.31f);
// 		shader->SetUniform3f("material.diffuse", 1.0f, 0.5f, 0.31f);
// 		shader->SetUniform3f("material.specular", 0.5f, 0.5f, 0.5f);
// 		shader->SetUniform1f("material.shininess", 32.0f);


// 		/* End of object */
// 		light = new Renderer(MESH_TYPE::MESH_CUBE, camera);
// 		light->SetShader(lightShader);
// 		light->SetPosition(glm::vec3(3.0f, 3.0f, 10.0f));

// 		while (!glfwWindowShouldClose(window)) {
// 			/* Each frame */
// 			float currentFrame = glfwGetTime();
// 			deltaTime = currentFrame - lastFrame;
// 			lastFrame = currentFrame;

// 			/* ImGui frame */
// 			ImGui_ImplOpenGL3_NewFrame();
// 			ImGui_ImplGlfw_NewFrame();
// 			ImGui::NewFrame();

// 			if (show_demo_window)
// 				ImGui::ShowDemoWindow(&show_demo_window);

// 			{
// 				static float f = 0.0f;
// 				static int counter = 0;

// 				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

// 				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
// 				ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
// 				ImGui::Checkbox("Another Window", &show_another_window);

// 				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
// 				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

// 				if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
// 						counter++;
// 				ImGui::SameLine();
// 				ImGui::Text("counter = %d", counter);

// 				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
// 				ImGui::End();
// 			}

// 			if (show_another_window) {
// 				ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
// 				ImGui::Text("Hello from another window!");
// 				if (ImGui::Button("Close Me"))
// 					show_another_window = false;
// 				ImGui::End();
// 			}

// 			ImGui::Render();
// 			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

// 			render->DrawMesh();
// 			light->DrawMesh();

// 			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

// 			glfwPollEvents();
// 			glfwSwapBuffers(window);
// 		}
// 	}

// 	glfwTerminate();
// 	return 0;
// }