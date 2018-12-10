#include "Scene11.h"
#include "Objects/camera.h"
#include "Objects/sphere.h"
#include "Objects/cube.h"
#include "Objects/point_light.h"
#include "Objects/plane.h"
#include "Core/input.h"
#include "Objects/directional_light.h"
#include "Objects/spot_light.h"
#include "Math/transform.h"

#define SHADOW_BUFFER_WIDTH	1024
#define SHADOW_BUFFER_HEIGHT 1024


bool Scene11::Initialize()
{

	m_depthShader = new Shader();
	m_depthShader->CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_shader.vs", GL_VERTEX_SHADER);
	m_depthShader->CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_shader.fs", GL_FRAGMENT_SHADER);
	m_depthShader->Link();

	Camera* camera = this->CreateObject<Camera>("camera_edditor");
	camera->Initialize();
	camera->SetView(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	PointLight* light = this->CreateObject<PointLight>("point_light");
	light->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	light->specular = glm::vec3(1.0f, 1.0f, 1.0f);
	light->transform.translation = glm::vec3(1.0f, 0.0f, 2.0f);

	Model* model = this->CreateObject<Model>("model1");
	model->Import(m_engine->Get<FileSystem>()->GetPathname() + "meshes\\suzanne.obj");
	model->transform.translation = glm::vec3(0.0f, 0.25f, 0.0f);

	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_shader.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_shader.fs", GL_FRAGMENT_SHADER);

	model->m_shader.Link();
	model->m_shader.Use();

	model->m_material.ambient = glm::vec3(0.0f);
	model->m_material.diffuse = glm::vec3(1.0f);
	model->m_material.specular = glm::vec3(1.0f);
	model->m_material.shininess = 100.0f;

	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\ogre_diffuse.bmp", GL_TEXTURE0);
	//model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\ogre_diffuse.bmp", GL_TEXTURE0);

	model->m_shader.SetUniform("material.ambient", model->m_material.ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.shininess);

	//model
	model = this->CreateObject<Model>("floor");
	model->Import(m_engine->Get<FileSystem>()->GetPathname() + "meshes\\quad.obj");
	model->transform.scale = glm::vec3(8);

	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_shader.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_shader.fs", GL_FRAGMENT_SHADER);

	model->m_shader.Link();
	model->m_shader.Use();

	model->m_material.ambient = glm::vec3(0.0f);
	model->m_material.diffuse = glm::vec3(1.0f);
	model->m_material.specular = glm::vec3(1.0f);
	model->m_material.shininess = 100.0f;

	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\rocks.jpg", GL_TEXTURE0);
	//model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\ogre_normal.bmp", GL_TEXTURE1);

	model->m_shader.SetUniform("material.ambient", model->m_material.ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.shininess);

	model = this->CreateObject<Model>("debug");
	model->Import(m_engine->Get<FileSystem>()->GetPathname() + "meshes\\quad.obj");
	model->transform.scale = glm::vec3(8);

	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_shader_debug.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_shader_debug.fs", GL_FRAGMENT_SHADER);

	model->m_shader.Link();
	model->m_shader.Use();

	model->m_material.ambient = glm::vec3(0.0f);
	model->m_material.diffuse = glm::vec3(1.0f);
	model->m_material.specular = glm::vec3(1.0f);
	model->m_material.shininess = 100.0f;

	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\rocks.jpg", GL_TEXTURE0);
	//model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\ogre_normal.bmp", GL_TEXTURE1);

	model->m_shader.SetUniform("material.ambient", model->m_material.ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.shininess);

	return true;
}

void Scene11::Shutdown()
{
	//Shutdown
	//this->RemoveAllObjects();
}

void Scene11::Update()
{
	float dt = m_engine->Get<Timer>()->DeltaTime();

	PointLight* light = this->GetObject<PointLight>("point_light");

	glm::mat4 mxProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
	glm::mat4 mxLightView = glm::lookAt(light->transform.translation, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mxLVP = mxProjection * mxLightView;

	m_depthShader->Use();
	m_depthShader->SetUniform("light_view_projection_matrix", mxLVP);


	Model* model = this->GetObjectA<Model>("model1");
	m_time = m_time + dt * .25f;
	model->transform.rotation = glm::quat(glm::vec3(0.0f, glm::radians(glm::sin(m_time) * 25.0f), 0.0f));

	std::vector<Object*> objects = this->GetObjects<Object>();
	for (Object* object : objects)
	{
		object->Update();
	}

	Camera* camera = this->GetObject<Camera>();
	glm::vec4 lightPosition = light->GetPositionFromView(camera->transform.matrix);


	glm::mat4 mxBias(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f
	);

	std::vector<Model*> models = this->GetObjects<Model>();
	for (Model* model : models)
	{
		model->m_shader.Use();

		model->m_shader.SetUniform("light.position", lightPosition);
		model->m_shader.SetUniform("light_position", lightPosition);

		model->m_shader.SetUniform("light.diffuse", light->diffuse);
		model->m_shader.SetUniform("light.specular", light->specular);

		model->m_shader.SetUniform("material.ambient", model->m_material.ambient);
		model->m_shader.SetUniform("material.diffuse", model->m_material.diffuse);
		model->m_shader.SetUniform("material.specular", model->m_material.specular);
		model->m_shader.SetUniform("material.shininess", model->m_material.shininess);

		glm::mat4 mxMLVP = mxBias * mxLVP * model->transform.matrix;
		model->m_shader.SetUniform("light_view_projection_matrix", mxMLVP);
	}

	m_engine->Get<UI>()->Start();
}
void Scene11::Render()
{
	m_engine->Get<Renderer>()->ClearBuffer();

	std::vector<Renderable*> renderables = this->GetObjects<Renderable>();
	for (Renderable* renderable : renderables)
	{
		renderable->Draw();
	}
	m_engine->Get<UI>()->Draw();

	m_engine->Get<Renderer>()->SwapBuffer();
}

