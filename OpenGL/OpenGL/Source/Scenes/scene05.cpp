#include "Scene05.h"
#include "Objects/camera.h"
#include "Objects/sphere.h"
#include "Objects/cube.h"
#include "Objects/point_light.h"

//#define MULTI_TEXTURE
//#define SPECULAR_MAP
#define FOG

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


bool Scene05::Initialize()
{
	Camera * camera = this->CreateObject<Camera>();
	camera->Initialize();
	camera->SetView(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f));

	PointLight * light = this->CreateObject<PointLight>();
	light->transform.translation = glm::vec3(10.0f, 10.0f, 10.0f);
	light->diffuse = glm::vec3(0.0f, 1.0f, 0.0f);
	light->specular = glm::vec3(1.0f);
	
	//Model 1
	Model* model = this->CreateObject<Sphere>();
	((Sphere*)(model))->Initialize(1.0f, 20, 20);
	model->transform.scale = glm::vec3(5.0f);

	// shader
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_fog.vs", GL_VERTEX_SHADER);
#ifdef SPECULAR_MAP
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_specular_map.fs", GL_FRAGMENT_SHADER);
#elif defined MULTI_TEXTURE
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_multi_texture.fs", GL_FRAGMENT_SHADER);
#elif defined FOG
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_fog.fs", GL_FRAGMENT_SHADER);
#endif
	model->m_shader.Link();
	model->m_shader.Use();
	
	m_engine->Get<Input>()->AddAction("left", SDL_SCANCODE_LEFT, Input::eDevice::KEYBOARD);
	m_engine->Get<Input>()->AddAction("right", SDL_SCANCODE_RIGHT, Input::eDevice::KEYBOARD);
	
	model->m_material.ambient = glm::vec3(0.2f);
	model->m_material.diffuse = glm::vec3(1.0f);
	model->m_material.specular = glm::vec3(1.0f);
	model->m_material.shininess = 1.0f;
	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\metal-diffuse.png", GL_TEXTURE0);
#ifdef SPECULAR_MAP
	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\metal-specular.png", GL_TEXTURE1);
#elif defined MULTI_TEXTURE
	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\moss.png", GL_TEXTURE1);
#endif

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
	model = this->CreateObject<Cube>();
	((Cube*)(model))->Initialize(10.0f);
	model->transform.scale = glm::vec3(15.0f);
	model->transform.translation = glm::vec3(100.0f, 0.0f, 0.0f);

	// shader
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_fog.vs", GL_VERTEX_SHADER);
#ifdef SPECULAR_MAP
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_specular_map.fs", GL_FRAGMENT_SHADER);
#elif defined MULTI_TEXTURE
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_multi_texture.fs", GL_FRAGMENT_SHADER);
#elif defined FOG
	model->m_shader.CompileShader(m_engine->Get<FileSystem>()->GetPathname() + "shaders\\phong_fog.fs", GL_FRAGMENT_SHADER);
#endif
	model->m_shader.Link();
	model->m_shader.Use();

	m_engine->Get<Input>()->AddAction("left", SDL_SCANCODE_LEFT, Input::eDevice::KEYBOARD);
	m_engine->Get<Input>()->AddAction("right", SDL_SCANCODE_RIGHT, Input::eDevice::KEYBOARD);

	model->m_material.ambient = glm::vec3(0.2f);
	model->m_material.diffuse = glm::vec3(1.0f);
	model->m_material.specular = glm::vec3(1.0f);
	model->m_material.shininess = 1.0f;
	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\metal-diffuse.png", GL_TEXTURE0);
#ifdef SPECULAR_MAP
	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\metal-specular.png", GL_TEXTURE1);
#elif defined MULTI_TEXTURE
	model->m_material.AddTexture(m_engine->Get<FileSystem>()->GetPathname() + "textures\\moss.png", GL_TEXTURE1);
#endif

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

	return true;
}

void Scene05::Shutdown()
{

}

void Scene05::Update()
{
	float dt = m_engine->Get<Timer>()->DeltaTime();

	Sphere* model = this->GetObject<Sphere>();

	if (m_engine->Get<Input>()->GetActionButton("left") == Input::eButtonState::HELD)  model->transform.translation.x -= 10.0f * dt;
	if (m_engine->Get<Input>()->GetActionButton("right") == Input::eButtonState::HELD) model->transform.translation.x += 10.0f * dt;
	model->transform.rotation = model->transform.rotation * glm::angleAxis(glm::radians(45.0f * dt), glm::vec3(0.0f, 1.0f, 0.0f));
	
	model->transform.Update();

	Camera* camera = this->GetObject<Camera>();
	camera->Update();

	PointLight* light = this->GetObjectA<PointLight>();
	light->Update();

	std::vector<Model*> models = this->GetObjects<Model>();
	for (Model* model : models)
	{
		model->m_shader.Use();

		// update light
		glm::vec4 lightPosition = light->GetPositionFromView(camera->transform.matrix);
		model->m_shader.SetUniform("light.position", lightPosition);

		// update normals
		glm::mat3 mxNormal = glm::mat3(camera->transform.matrix * model->transform.matrix);
		mxNormal = glm::inverse(mxNormal);
		mxNormal = glm::transpose(mxNormal);
		model->m_shader.SetUniform("normal_matrix", mxNormal);

		// update model view
		glm::mat4 mxMV = camera->transform.matrix * model->transform.matrix;
		model->m_shader.SetUniform("model_view_matrix", mxMV);

		// update mvp
		glm::mat4 mxMVP = camera->projection * camera->transform.matrix * model->transform.matrix;
		model->m_shader.SetUniform("model_view_projection_matrix", mxMVP);

		m_uvOffset.y = m_uvOffset.y + (0.1f * dt);
		m_uvOffset.x = m_uvOffset.x + (0.1f * dt);

		model->m_shader.SetUniform("uv_offset", m_uvOffset);
	}

}

void Scene05::Render()
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
