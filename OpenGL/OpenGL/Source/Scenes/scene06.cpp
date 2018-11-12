#include "Scene06.h"
#include "Objects/camera.h"
#include "Objects/sphere.h"
#include "Objects/cube.h"
#include "Objects/point_light.h"
#include "Objects/plane.h"
#include "Core/input.h"
#include "Objects/directional_light.h"


static float cube_vertices[] = {
	// Front
	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
	// Right
	 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	 // Back
	 -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	 -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
	  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
	  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
	  // Left
	  -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	  -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	  -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	  -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	  // Bottom
	  -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	  -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
	   1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
	   1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
	   // Top
	   -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
	   -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
};

static GLushort cube_indices[] =
{
	 0,  1,  2,  0,  2,  3,
	 4,  5,  6,  4,  6,  7,
	 8,  9, 10,  8, 10, 11,
	12, 13, 14, 12, 14, 15,
	16, 17, 18, 16, 18, 19,
	20, 21, 22, 20, 22, 23
};


bool Scene06::Initialize()
{
	m_engine->Get<Input>()->AddAction("point", SDL_SCANCODE_1, Input::eDevice::KEYBOARD);
	m_engine->Get<Input>()->AddAction("directional", SDL_SCANCODE_2, Input::eDevice::KEYBOARD);

	Camera * camera = this->CreateObject<Camera>();
	camera->Initialize();
	camera->SetView(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f));

	PointLight * light = this->CreateObject<PointLight>();
	light->transform.translation = glm::vec3(10.0f, 10.0f, 10.0f);
	light->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	light->specular = glm::vec3(1.0f);
	
	//Model 1
	Model* model = this->CreateObject<Sphere>("Model1");
	((Sphere*)(model))->Initialize(1.0f, 20, 20);
	model->transform.scale = glm::vec3(1.0f);
	model->transform.translation = glm::vec3(0.0f, 0.0f, -1.0f);

	// shader
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_fog.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_fog.fs", GL_FRAGMENT_SHADER);

	model->m_shader.Link();
	model->m_shader.Use();
	
	m_engine->Get<Input>()->AddAction("left", SDL_SCANCODE_LEFT, Input::eDevice::KEYBOARD);
	m_engine->Get<Input>()->AddAction("right", SDL_SCANCODE_RIGHT, Input::eDevice::KEYBOARD);
	
	model->m_material.ambient = glm::vec3(0.2f);
	model->m_material.diffuse = glm::vec3(1.0f);
	model->m_material.specular = glm::vec3(1.0f);
	model->m_material.shininess = 1.0f;
	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\uvgrid.jpg", GL_TEXTURE0);



	model->m_shader.SetUniform("material.ambient", model->m_material.ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.shininess);

	model->m_shader.SetUniform("light.diffuse", light->diffuse);
	model->m_shader.SetUniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	model->m_shader.SetUniform("uv_scale", glm::vec2(1.0f, 1.0f));

	model->m_shader.SetUniform("fog.distance_min", 25.0f);
	model->m_shader.SetUniform("fog.distance_max", 100.0f);
	model->m_shader.SetUniform("fog.color", glm::vec3(0.0f, 0.5f, 0.5f));

	//Model 2
	model = this->CreateObject<Plane>("Model2");
	((Plane*)(model))->Initialize(10.0f, 10.0f, 10, 10, 10.0f, 10.0f);
	model->transform.translation = glm::vec3(0.0f, -2.0f, 0.0f);

	// shader
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_specular_map.fs", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();

	m_engine->Get<Input>()->AddAction("left", SDL_SCANCODE_LEFT, Input::eDevice::KEYBOARD);
	m_engine->Get<Input>()->AddAction("right", SDL_SCANCODE_RIGHT, Input::eDevice::KEYBOARD);

	model->m_material.ambient = glm::vec3(0.2f);
	model->m_material.diffuse = glm::vec3(1.0f);
	model->m_material.specular = glm::vec3(1.0f);
	model->m_material.shininess = 1.0f;
	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\cobble-diffuse.tga", GL_TEXTURE0);
	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\cobble-specular.tga", GL_TEXTURE1);



	model->m_shader.SetUniform("material.ambient", model->m_material.ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.shininess);

	model->m_shader.SetUniform("light.diffuse", light->diffuse);
	model->m_shader.SetUniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	//model->m_shader.SetUniform("uv_scale", glm::vec2(1.0f, 1.0f));

	return true;
}

void Scene06::Shutdown()
{

}

void Scene06::Update()
{
	float dt = m_engine->Get<Timer>()->DeltaTime();

	if (m_engine->Get<Input>()->GetActionButton("point") == Input::eButtonState::HELD) m_lightIndex = 0;
	if (m_engine->Get<Input>()->GetActionButton("directional") == Input::eButtonState::HELD) m_lightIndex = 1;

	Model* model = this->GetObject<Model>("Model1");
	model->transform.rotation = model->transform.rotation * glm::angleAxis(glm::radians(45.0f * dt), glm::vec3(0.0f, 1.0f, 0.0f));

	Camera* camera = this->GetObject<Camera>();

	std::vector<Object*> objects = this->GetObjects<Object>();
	for (Object* object : objects)
	{
		object->Update();
	}	

	Light* light = this->GetObject<PointLight>();
	light->transform.rotation = light->transform.rotation * glm::angleAxis(glm::radians(-45.0f * dt), glm::vec3(0.0f, 1.0f, 0.0f));
	light->transform.translation = light->transform.rotation * glm::vec3(3, 3, 3);

	glm::vec4 lightPosition;


	switch (m_lightIndex)
	{
	case 0:
		light = this->GetObject<PointLight>();
		lightPosition = ((PointLight*)light)->GetPositionFromView(camera->transform.matrix);
		break;
	case 1:
		light = this->GetObject<PointLight>();
		lightPosition = ((DirectionalLight*)light)->GetDirectionFromView(camera->transform.matrix);
		break;
	default:
		break;
	}
	

	std::vector<Model*> models = this->GetObjects<Model>();
	for (Model* model : models)
	{

		model->m_shader.Use();
		model->m_shader.SetUniform("light.position", lightPosition);
		model->transform.Update();

	}
}

void Scene06::Render()
{
	m_engine->Get<Renderer>()->ClearBuffer();

	std::vector<Renderable*> renderables = this->GetObjects<Renderable>();
	for (Renderable* renderable : renderables)
	{
		renderable->Draw();
	}

	Sphere* model = this->GetObject<Sphere>();
	model->Draw();

	m_engine->Get<Renderer>()->SwapBuffer();

	

}
