#include "Scene09.h"
#include "Objects/camera.h"
#include "Objects/sphere.h"
#include "Objects/cube.h"
#include "Objects/point_light.h"
#include "Objects/plane.h"
#include "Core/input.h"
#include "Objects/directional_light.h"
#include "Objects/spot_light.h"
#include "Math/transform.h"

bool Scene09::Initialize()
{
	m_engine->Get<Input>()->AddAction("point", SDL_SCANCODE_1, Input::eDevice::KEYBOARD);
	m_engine->Get<Input>()->AddAction("directional", SDL_SCANCODE_2, Input::eDevice::KEYBOARD);

	//Cameras
	Camera * camera = this->CreateObject<Camera>("camera_edditor"); 
	camera->Initialize();
	camera->SetView(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	camera = this->CreateObject<Camera>("camera_rtt");
	camera->type = Camera::eType::LOOK_AT;
	camera->Initialize();
	camera->SetView(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//Lights
	Light* light = this->CreateObject<PointLight>("light1"); 
	light->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	light->specular = glm::vec3(1.0f, 1.0f, 1.0f);
	light->transform.translation = glm::vec3(0.0f, 10.0f, 10.0f);

	//Model 1
	Model* model = this->CreateObject<Model>("Model1");
	model->Import(m_engine->Get<FileSystem>()->GetPathname() + "Meshes\\suzanne.obj");
	model->transform.scale = glm::vec3(1.0f);
	model->transform.translation = glm::vec3(0.0f, 0.0f, 0.0f);
	model->m_cameraName = "camera_rtt";

	//Shader
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong.fs", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();

	//Material
	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\uvgrid.jpg", GL_TEXTURE0);

	model->m_material.ambient = glm::vec3(0.2f);
	model->m_material.diffuse = glm::vec3(1.0f);
	model->m_material.specular = glm::vec3(1.0f);
	model->m_material.shininess = 1.0f;

	model->m_shader.SetUniform("material.ambient", model->m_material.ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.shininess);

	model->m_shader.SetUniform("light.specular", light->specular);
	model->m_shader.SetUniform("light.diffuse", light->diffuse);

	//Model 2
	model = this->CreateObject<Model>("Model2");
	model->Import(m_engine->Get<FileSystem>()->GetPathname() + "Meshes\\cube.obj");
	model->transform.scale = glm::vec3(1.0f);
	model->transform.translation = glm::vec3(0.0f, 0.0f, 4.0f);

	//Shader
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong.vs", GL_VERTEX_SHADER);
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong.fs", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();

	//Material
	GLuint textureID = Material::CreateTexture(512, 512);
	model->m_material.AddTexture(textureID, GL_TEXTURE0);

	model->m_material.ambient = glm::vec3(0.2f);
	model->m_material.diffuse = glm::vec3(1.0f);
	model->m_material.specular = glm::vec3(1.0f);
	model->m_material.shininess = 1.0f;

	model->m_shader.SetUniform("material.ambient", model->m_material.ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.shininess);

	model->m_shader.SetUniform("light.specular", light->specular);
	model->m_shader.SetUniform("light.diffuse", light->diffuse);

	//FrameBuffer
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);

	//DepthBuffer
	GLuint depthBufferID;
	glGenRenderbuffers(1, &depthBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferID);

	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	assert(result == GL_FRAMEBUFFER_COMPLETE);

	return true;
}

void Scene09::Shutdown()
{

}

void Scene09::Update()
{
	float dt = m_engine->Get<Timer>()->DeltaTime();

	std::vector<Object*> objects = this->GetObjects<Object>();
	for (Object* object : objects)
	{
		object->Update();
	}


	PointLight* light = this->GetObject<PointLight>();
	glm::vec4 lightPosition;

	std::vector<Model*> models = this->GetObjects<Model>();
	for (Model* model : models)
	{
		if (model->name == "Model1")
		{
			Camera* camera = GetObject<Camera>("camera_rtt");
			lightPosition = light->GetPositionFromView(camera->transform.matrix);
			model->m_shader.Use();
			model->m_shader.SetUniform("light.position", lightPosition);
			model->transform.rotation = model->transform.rotation * glm::quat(glm::vec3(0.0f, glm::radians(25.0f * dt), 0.0f));


		}
		else if (model->name == "Model2")
		{
			Camera* camera = GetObject<Camera>();
			lightPosition = light->GetPositionFromView(camera->transform.matrix);
			model->m_shader.Use();
			model->m_shader.SetUniform("light.position", lightPosition);
			model->transform.rotation = model->transform.rotation * glm::quat(glm::vec3(glm::radians(15.0f * dt), glm::radians(15.0f * dt), 0.0f));


		}
		else
		{
			Camera* camera = this->GetObject<Camera>();
			model->m_shader.Use();
			model->m_shader.SetUniform("light.position", lightPosition);
			model->transform.rotation = model->transform.rotation * glm::angleAxis(glm::radians(45.0f * dt), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		model->transform.Update();


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

void Scene09::Render()
{
	glViewport(0, 0, 512, 512);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Model* model = this->GetObject<Model>("Model1");
	model->Draw();

	glFlush();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, m_engine->Get<Renderer>()->GetWidth(), m_engine->Get<Renderer>()->GetHeight());
	m_engine->Get<Renderer>()->ClearBuffer();

	model = this->GetObject<Model>("Model2");
	model->Draw();

	m_engine->Get<UI>()->Draw();
	m_engine->Get<Renderer>()->SwapBuffer();

}
