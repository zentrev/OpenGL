//#include "Scene07.h"
//#include "Objects/camera.h"
//#include "Objects/sphere.h"
//#include "Objects/cube.h"
//#include "Objects/point_light.h"
//#include "Objects/plane.h"
//#include "Core/input.h"
//#include "Objects/directional_light.h"
//#include "Objects/spot_light.h"
//#include "Math/transform.h"
//#include <glm/gtc/random.hpp>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/color_space.hpp>
//
//#define NUM_LIGHTS 5
//
//bool Scene07::Initialize()
//{
//	m_engine->Get<Input>()->AddAction("point", SDL_SCANCODE_1, Input::eDevice::KEYBOARD);
//	m_engine->Get<Input>()->AddAction("directional", SDL_SCANCODE_2, Input::eDevice::KEYBOARD);
//
//
//	Camera * camera = this->CreateObject<Camera>();
//	camera->Initialize();
//	camera->SetView(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f));
//
//	for (int i = 0; i < NUM_LIGHTS; i++)
//	{
//		Light* light = this->CreateObject<Light>("light" + i);
//		light->transform.translation = glm::sphericalRand(4.0f);
//		glm::vec3 color = glm::rgbColor(glm::vec3(glm::linearRand(0.0f, 360.0f), 1.0f, 1.0f));
//		light->diffuse = color;
//		light->specular = color;
//	}
//	auto lights = GetObjects<PointLight>();
//
//	/*SpotLight* spot_light = this->CreateObject<SpotLight>("light");
//	spot_light->diffuse = glm::vec3(1.0f, 0.0f, 1.0f); 
//	spot_light->specular = glm::vec3(1.0f, 1.0f, 1.0f); 
//	spot_light->cutoff = glm::radians(45.0f); 
//	spot_light->exponent = 10.0f;
//	spot_light->transform.translation = glm::vec3(0.0f, 2.0f, 2.0f);
//	spot_light->SetDirection(spot_light->transform.translation, glm::vec3(0.0f, 0.0f, 0.0f));*/
//
//	//Model 1
//	Model* model = this->CreateObject<Model>("Model1");
//	model->Import(m_engine->Get<FileSystem>()->GetPathname() + "Meshes\\ogre.obj");
//	//((Sphere*)(model))->Initialize(1.0f, 20, 20);
//	model->transform.scale = glm::vec3(1.0f);
//	model->transform.translation = glm::vec3(0.0f, 0.0f, -1.0f);
//
//	// shader
//	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong.vs", GL_VERTEX_SHADER);
//	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_spotlight.fs", GL_FRAGMENT_SHADER);
//
//	model->m_shader.Link();
//	model->m_shader.Use();
//
//	m_engine->Get<Input>()->AddAction("left", SDL_SCANCODE_LEFT, Input::eDevice::KEYBOARD);
//	m_engine->Get<Input>()->AddAction("right", SDL_SCANCODE_RIGHT, Input::eDevice::KEYBOARD);
//
//	model->m_material.ambient = glm::vec3(0.2f);
//	model->m_material.diffuse = glm::vec3(1.0f);
//	model->m_material.specular = glm::vec3(1.0f);
//	model->m_material.shininess = 1.0f;
//	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\uvgrid.jpg", GL_TEXTURE0);
//
//	model->m_shader.SetUniform("material.ambient", model->m_material.ambient);
//	model->m_shader.SetUniform("material.diffuse", model->m_material.diffuse);
//	model->m_shader.SetUniform("material.specular", model->m_material.specular);
//	model->m_shader.SetUniform("material.shininess", model->m_material.shininess);
//
//	/*model->m_shader.SetUniform("light.cutoff", spot_light->cutoff); 
//	model->m_shader.SetUniform("light.exponent", spot_light->exponent);*/
//	for (size_t i = 0; i < lights.size(); i++) {
//		char uniformName[32];
//		sprintf_s(uniformName, "lights[%d].diffuse", (int)i);
//		model->m_shader.SetUniform(uniformName, lights[i]->diffuse);
//
//		sprintf_s(uniformName, "lights[%d].specular", (int)i);
//		model->m_shader.SetUniform(uniformName, lights[i]->specular);
//	}
//
//	//Model 2
//	model = this->CreateObject<Plane>("Model2");
//	((Plane*)(model))->Initialize(10.0f, 10.0f, 10, 10, 10.0f, 10.0f);
//	model->transform.translation = glm::vec3(0.0f, -2.0f, 0.0f);
//
//	// shader
//	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong.vs", GL_VERTEX_SHADER);
//	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_spotlight.fs", GL_FRAGMENT_SHADER);
//	model->m_shader.Link();
//	model->m_shader.Use();
//
//	m_engine->Get<Input>()->AddAction("left", SDL_SCANCODE_LEFT, Input::eDevice::KEYBOARD);
//	m_engine->Get<Input>()->AddAction("right", SDL_SCANCODE_RIGHT, Input::eDevice::KEYBOARD);
//
//	model->m_material.ambient = glm::vec3(0.2f);
//	model->m_material.diffuse = glm::vec3(1.0f);
//	model->m_material.specular = glm::vec3(1.0f);
//	model->m_material.shininess = 1.0f;
//	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\cobble-diffuse.tga", GL_TEXTURE0);
//
//	model->m_shader.SetUniform("material.ambient", model->m_material.ambient);
//	model->m_shader.SetUniform("material.diffuse", model->m_material.diffuse);
//	model->m_shader.SetUniform("material.specular", model->m_material.specular);
//	model->m_shader.SetUniform("material.shininess", model->m_material.shininess);
//
//	/*model->m_shader.SetUniform("light.cutoff", spot_light->cutoff); 
//	model->m_shader.SetUniform("light.exponent", spot_light->exponent);*/
//
//	return true;
//}
//
//void Scene07::Shutdown()
//{
//
//}
//
//void Scene07::Update()
//{
//	float dt = m_engine->Get<Timer>()->DeltaTime();
//
//	if (m_engine->Get<Input>()->GetActionButton("point") == Input::eButtonState::HELD) m_lightIndex = 0;
//	if (m_engine->Get<Input>()->GetActionButton("directional") == Input::eButtonState::HELD) m_lightIndex = 1;
//
//	Model* model = this->GetObject<Model>("Model1");
//	model->transform.rotation = model->transform.rotation * glm::angleAxis(glm::radians(45.0f * dt), glm::vec3(0.0f, 1.0f, 0.0f));
//
//	Camera* camera = this->GetObject<Camera>();
//
//	std::vector<Object*> objects = this->GetObjects<Object>();
//	for (Object* object : objects)
//	{
//		object->Update();
//	}
//
//	/*SpotLight* light = this->GetObject<SpotLight>();
//
//	glm::vec4 lightPosition = light->GetPositionFromView(camera->transform.matrix);
//	glm::vec3 lightDirection = light->GetDirectionFromView(camera->transform.matrix);
//
//	model->m_shader.SetUniform("light.diffuse", light->diffuse);
//	model->m_shader.SetUniform("light.specular", light->specular);*/
//
//	std::vector<Model*> models = this->GetObjects<Model>();
//	for (Model* model : models)
//	{
//		/*model->m_shader.Use();
//		model->m_shader.SetUniform("light.position", lightPosition);
//		model->m_shader.SetUniform("light.direction", lightDirection); 
//		model->m_shader.SetUniform("light.diffuse", light->diffuse); 
//		model->m_shader.SetUniform("light.specular", light->specular); 
//		model->m_shader.SetUniform("light.cutoff", light->cutoff); 
//		model->m_shader.SetUniform("light.exponent", light->exponent);*/
//
//	}
//
//	m_engine->Get<UI>()->Start();
//	ImGui::Begin("Window");
//	/*ImGui::ColorEdit3("Diffuse", (float*)&light->diffuse);
//	ImGui::ColorEdit3("Specular", (float*)&light->specular);*/
//	ImGui::End();
//
//	ImGui::Begin("Transform");
//	Model* _model = this->GetObject<Model>("Model1");
//	Transform::Edit(&_model->transform);
//	ImGui::End();
//
//
//}
//
//void Scene07::Render()
//{
//	m_engine->Get<Renderer>()->ClearBuffer();
//
//	std::vector<Renderable*> renderables = this->GetObjects<Renderable>();
//	for (Renderable* renderable : renderables)
//	{
//		renderable->Draw();
//	}
//	m_engine->Get<UI>()->Draw();
//
//	Model* model = this->GetObject<Model>();
//	model->Draw();
//
//	m_engine->Get<Renderer>()->SwapBuffer();
//
//}
