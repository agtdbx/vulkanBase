#include <program/loop/loop.hpp>

void	draw(
			Engine &engine,
			Mesh3D &mesh,
			UBOMesh3D &meshUBO,
			Shader &shader,
			Camera &camera)
{
	// Start drawing
	engine.window.startDraw();

	// Draw mesh
	shader.updateUBO(engine.window, &meshUBO, 0);
	engine.window.drawMesh(mesh, shader);

	// End drawing
	engine.window.endDraw(engine.context);
}
