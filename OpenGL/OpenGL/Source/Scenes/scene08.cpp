#include "Scene08.h"
#include "Objects/camera.h"
#include "Objects/sphere.h"
#include "Objects/cube.h"
#include "Objects/point_light.h"
#include "Objects/plane.h"
#include "Core/input.h"
#include "Objects/directional_light.h"
#include "Objects/spot_light.h"
#include "Math/transform.h"

bool Scene08::Initialize()
{
	m_engine->Get<Input>()->AddAction("point", SDL_SCANCODE_1, Input::eDevice::KEYBOARD);
	m_engine->Get<Input>()->AddAction("directional", SDL_SCANCODE_2, Input::eDevice::KEYBOARD);

	Camera * camera = this->CreateObject<Camera>();
	camera->Initialize();
	camera->SetView(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f));

	SpotLight* spot_light = this->CreateObject<SpotLight>("spot_light"); 
	spot_light->diffuse = glm::vec3(1.0f, 0.0f, 1.0f); 
	spot_light->specular = glm::vec3(1.0f, 1.0f, 1.0f); 
	spot_light->cutoff = glm::radians(45.0f); 
	spot_light->exponent = 10.0f;
	spot_light->transform.translation = glm::vec3(0.0f, 2.0f, 2.0f);
	spot_light->SetDirection(spot_light->transform.translation, glm::vec3(0.0f, 0.0f, 0.0f));

	//Model 1
	Model* model = this->CreateObject<Model>("Model1");
	model->Import(m_engine->Get<FileSystem>()->GetPathname() + "Meshes\\cube.obj");
	model->transform.scale = glm::vec3(400.0f);
	model->transform.translation = glm::vec3(0.0f, 0.0f, 0.0f);

	// shader
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\cubemap.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\cubemap.fs", GL_FRAGMENT_SHADER);

	model->m_shader.Link();
	model->m_shader.Use();

	m_engine->Get<Input>()->AddAction("left", SDL_SCANCODE_LEFT, Input::eDevice::KEYBOARD);
	m_engine->Get<Input>()->AddAction("right", SDL_SCANCODE_RIGHT, Input::eDevice::KEYBOARD);

	model->m_material.ambient = glm::vec3(0.2f);
	model->m_material.diffuse = glm::vec3(1.0f);
	model->m_material.specular = glm::vec3(1.0f);
	model->m_material.shininess = 1.0f;

	std::vector<std::string> suffixes = { "_posx", "_negx", "_posy", "_negy", "_posz", "_negz" };
	model->m_material.AddTextureCube(m_engine->Get<FileSystem>()->GetPathname() + "textures\\lancellotti", suffixes, "jpg", GL_TEXTURE0);
	model->m_shader.AddSubroutine(GL_VERTEX_SHADER, "skybox");

	model->m_shader.SetUniform("material.ambient", model->m_material.ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.shininess);

	model->m_shader.SetUniform("light.cutoff", spot_light->cutoff); 
	model->m_shader.SetUniform("light.exponent", spot_light->exponent);

	//Model 2
	model = this->CreateObject<Plane>("Model2");
	model->Import(m_engine->Get<FileSystem>()->GetPathname() + "Meshes\\sphere.obj");
	model->transform.translation = glm::vec3(0.0f, 0.0f, 0.0f);

	// shader
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\cubemap.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\cubemap.fs", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();

	m_engine->Get<Input>()->AddAction("left", SDL_SCANCODE_LEFT, Input::eDevice::KEYBOARD);
	m_engine->Get<Input>()->AddAction("right", SDL_SCANCODE_RIGHT, Input::eDevice::KEYBOARD);

	model->m_material.ambient = glm::vec3(0.2f);
	model->m_material.diffuse = glm::vec3(1.0f);
	model->m_material.specular = glm::vec3(1.0f);
	model->m_material.shininess = 1.0f;
	model->m_material.AddTextureCube(m_engine->Get<FileSystem>()->GetPathname() + "textures\\lancellotti", suffixes, "jpg", GL_TEXTURE0);
	model->m_shader.AddSubroutine(GL_VERTEX_SHADER, "reflection");

	model->m_shader.SetUniform("material.ambient", model->m_material.ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.shininess);

	model->m_shader.SetUniform("light.cutoff", spot_light->cutoff); 
	model->m_shader.SetUniform("light.exponent", spot_light->exponent);

	return true;
}

void Scene08::Shutdown()
{

}

void Scene08::Update()
{
	float dt = m_engine->Get<Timer>()->DeltaTime();

	if (m_engine->Get<Input>()->GetActionButton("point") == Input::eButtonState::HELD) m_lightIndex = 0;
	if (m_engine->Get<Input>()->GetActionButton("directional") == Input::eButtonState::HELD) m_lightIndex = 1;

	Model* model = this->GetObject<Model>("Model2");
	model->transform.rotation = model->transform.rotation * glm::angleAxis(glm::radians(45.0f * dt), glm::vec3(0.0f, 1.0f, 0.0f));

	Camera* camera = this->GetObject<Camera>();

	std::vector<Object*> objects = this->GetObjects<Object>();
	for (Object* object : objects)
	{
		object->Update();
	}

	SpotLight* light = this->GetObject<SpotLight>();

	glm::vec4 lightPosition = light->GetPositionFromView(camera->transform.matrix);
	glm::vec3 lightDirection = light->GetDirectionFromView(camera->transform.matrix);

	model->m_shader.SetUniform("light.diffuse", light->diffuse);
	model->m_shader.SetUniform("light.specular", light->specular);

	std::vector<Model*> models = this->GetObjects<Model>();
	for (Model* model : models)
	{
		model->m_shader.Use();
		model->m_shader.SetUniform("light.position", lightPosition);
		//model->m_shader.SetUniform("light.direction", lightDirection); 
		//model->m_shader.SetUniform("light.diffuse", light->diffuse); 
		//model->m_shader.SetUniform("light.specular", light->specular); 
		//model->m_shader.SetUniform("light.cutoff", light->cutoff); 
		//model->m_shader.SetUniform("light.exponent", light->exponent);

		model->m_shader.SetUniform("model_matrix", model->transform.matrix);
		model->m_shader.SetUniform("camera_position", camera->transform.translation);

	}

	m_engine->Get<UI>()->Start();
	ImGui::Begin("Window");
	ImGui::ColorEdit3("Diffuse", (float*)&light->diffuse);
	ImGui::ColorEdit3("Specular", (float*)&light->specular);
	ImGui::End();

	ImGui::Begin("Transform");
	Model* _model = this->GetObject<Model>("Model1");
	Transform::Edit(&_model->transform);
	ImGui::End();


}

void Scene08::Render()
{
	glDisable(GL_CULL_FACE);
	m_engine->Get<Renderer>()->ClearBuffer();

	std::vector<Renderable*> renderables = this->GetObjects<Renderable>();
	for (Renderable* renderable : renderables)
	{
		renderable->Draw();
	}
	m_engine->Get<UI>()->Draw();

	Model* model = this->GetObject<Model>();
	model->Draw();

	m_engine->Get<Renderer>()->SwapBuffer();

}
