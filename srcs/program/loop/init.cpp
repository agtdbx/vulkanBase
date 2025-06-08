#include <program/loop/loop.hpp>


static void	loadTextures(Engine &engine);
static void	loadMesh(Engine &engine, Mesh3D &mesh);
static void loadShaders(
				Engine &engine,
				Shader &Shader);


bool init(
		Engine &engine,
		Mesh3D &mesh,
		Shader &shader,
		Camera &camera)
{
	camera.setPosition(gm::Vec3f(0.41f, 0.77f, 1.67f));
	camera.setRotation(-20.88f, -95.34f, 0.0f);

	try
	{
		// Init engine
		initEngine(engine);

		// Load texture
		loadTextures(engine);

		// Vulkan attributs creation
		engine.textureManager.createAllImages(engine);

		loadMesh(engine, mesh);
		loadShaders(engine, shader);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
		return (false);
	}
	return (true);
}


static void	loadTextures(Engine &engine)
{
	engine.textureManager.addTexture("duckSpaceship", "data/textures/duckSpaceship.png");
}


static void	loadMesh(Engine &engine, Mesh3D &mesh)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	vertices = {
		// Front face vertex
		{{-0.5, 0.5, 0.5}, { 0.0, 0.0, 1.0}, {0.0, 0.0}}, // LU
		{{-0.5,-0.5, 0.5}, { 0.0, 0.0, 1.0}, {0.0, 1.0}}, // LD
		{{ 0.5,-0.5, 0.5}, { 0.0, 0.0, 1.0}, {1.0, 1.0}}, // RD
		{{ 0.5, 0.5, 0.5}, { 0.0, 0.0, 1.0}, {1.0, 0.0}}, // RU
		// Right face vertex
		{{ 0.5, 0.5, 0.5}, { 1.0, 0.0, 0.0}, {0.0, 0.0}}, // LU
		{{ 0.5,-0.5, 0.5}, { 1.0, 0.0, 0.0}, {0.0, 1.0}}, // LD
		{{ 0.5,-0.5,-0.5}, { 1.0, 0.0, 0.0}, {1.0, 1.0}}, // RD
		{{ 0.5, 0.5,-0.5}, { 1.0, 0.0, 0.0}, {1.0, 0.0}}, // RU
		// Left face vertex
		{{-0.5, 0.5,-0.5}, {-1.0, 0.0, 0.0}, {0.0, 0.0}}, // LU
		{{-0.5,-0.5,-0.5}, {-1.0, 0.0, 0.0}, {0.0, 1.0}}, // LD
		{{-0.5,-0.5, 0.5}, {-1.0, 0.0, 0.0}, {1.0, 1.0}}, // RD
		{{-0.5, 0.5, 0.5}, {-1.0, 0.0, 0.0}, {1.0, 0.0}}, // RU
		// Back face vertex
		{{ 0.5, 0.5,-0.5}, { 0.0, 0.0,-1.0}, {0.0, 0.0}}, // LU
		{{ 0.5,-0.5,-0.5}, { 0.0, 0.0,-1.0}, {0.0, 1.0}}, // LD
		{{-0.5,-0.5,-0.5}, { 0.0, 0.0,-1.0}, {1.0, 1.0}}, // RD
		{{-0.5, 0.5,-0.5}, { 0.0, 0.0,-1.0}, {1.0, 0.0}}, // RU
		// Up face vertex
		{{-0.5, 0.5,-0.5}, { 0.0, 0.0,-1.0}, {0.0, 0.0}}, // LU
		{{-0.5, 0.5, 0.5}, { 0.0, 0.0,-1.0}, {0.0, 1.0}}, // LD
		{{ 0.5, 0.5, 0.5}, { 0.0, 0.0,-1.0}, {1.0, 1.0}}, // RD
		{{ 0.5, 0.5,-0.5}, { 0.0, 0.0,-1.0}, {1.0, 0.0}}, // RU
		// Down face vertex
		{{-0.5,-0.5, 0.5}, { 0.0, 0.0,-1.0}, {0.0, 0.0}}, // LU
		{{-0.5,-0.5,-0.5}, { 0.0, 0.0,-1.0}, {0.0, 1.0}}, // LD
		{{ 0.5,-0.5,-0.5}, { 0.0, 0.0,-1.0}, {1.0, 1.0}}, // RD
		{{ 0.5,-0.5, 0.5}, { 0.0, 0.0,-1.0}, {1.0, 0.0}}, // RU

	};
	indices = {
		// Front face
		 0,  1,  2,
		 0,  2,  3,
		// Right face
		 4,  5,  6,
		 4,  6,  7,
		// Left face
		 8,  9, 10,
		 8, 10, 11,
		// Back face
		12, 13, 14,
		12, 14, 15,
		// Up face
		16, 17, 18,
		16, 18, 19,
		// Down face
		20, 21, 22,
		20, 22, 23,
	};

	mesh = Mesh3D(vertices, indices);
	mesh.createBuffers(engine.commandPool);
}


static void loadShaders(
				Engine &engine,
				Shader &shader)
{
	std::vector<UBOType>	uboTypes = {{sizeof(UBOMesh3D), UBO_VERTEX}};
	shader.init<Vertex>(
					engine, FCUL_COUNTER, DRAW_POLYGON,
					"shadersbin/mesh_vert.spv", "shadersbin/mesh_frag.spv",
					uboTypes, {"duckSpaceship"});
}
