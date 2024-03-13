#include "Renderer.h"

std::unique_ptr<Renderer> g_renderer;

int main(int argc, char* argv[])
{
    g_renderer = std::make_unique<Renderer>();
    g_renderer->Initialize(argc, argv);

    // Set up function lambdas to handle the callbacks, this saves having to define them in main but allows for a renderer class
    glutReshapeFunc([](int width, int height){ g_renderer->ResizeFunction(width, height); });
    glutDisplayFunc([]() {g_renderer->RenderFunction(); });

    glutMainLoop();

    exit(EXIT_SUCCESS);
}

