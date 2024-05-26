#include "Render/OpenGL/glad/glad.h"
#include "Window.h"
#include <iostream>

namespace Donut {

Window::Window(const std::string& title, const int width, const int height)
{
    SDL_version compiledVersion, linkedVersion;
    SDL_VERSION(&compiledVersion);
    SDL_GetVersion(&linkedVersion);

    std::clog << "Initializing SDL..." << std::endl;
    std::clog << "SDL Version/Compiled " << uint32_t(compiledVersion.major) << "." << uint32_t(compiledVersion.minor) << "."
              << uint32_t(compiledVersion.patch) << std::endl;
    std::clog << "SDL Version/Linked " << uint32_t(linkedVersion.major) << "." << uint32_t(linkedVersion.minor) << "."
              << uint32_t(linkedVersion.patch) << std::endl;

    // Initialize SDL
    if (SDL_WasInit(0) == 0)
    {
        SDL_SetMainReady();
        if (SDL_Init(0) != 0)
            throw std::runtime_error("Could not initialize SDL: " + std::string(SDL_GetError()));

        if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
            throw std::runtime_error("Could not initialize SDL Video Subsystem: " + std::string(SDL_GetError()));

        if (SDL_InitSubSystem(SDL_INIT_TIMER) != 0)
            throw std::runtime_error("Could not initialize SDL Timer Subsystem: " + std::string(SDL_GetError()));
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    // request a 4.1 core profile (maximum supported on macOS)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    const uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN;

    _window = std::unique_ptr<SDL_Window, SDLDestroyer>(
        SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags));
    if (_window == nullptr)
        throw std::runtime_error("Failed creating window: " + std::string(SDL_GetError()));

    // Create a OpenGL context on SDL2
    _glContext = SDL_GL_CreateContext(_window.get());
    if (_glContext == nullptr)
        throw std::runtime_error("Failed to initialize the OpenGL context: " + std::string(SDL_GetError()));

    // Make the context current
    if (SDL_GL_MakeCurrent(_window.get(), _glContext) != 0) {
        throw std::runtime_error("Failed to make the OpenGL context current: " + std::string(SDL_GetError()));
    }

    // Load GL extensions using glad
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        throw std::runtime_error("Failed to initialize the OpenGL context.");
    }

    std::cout << "GLAD initialized successfully." << std::endl;

    std::cout << "OpenGL version loaded: " << GLVersion.major << "." << GLVersion.minor << "\n"
              << "Vendor: " << glGetString(GL_VENDOR) << "\n"
              << "Renderer: " << glGetString(GL_RENDERER) << "\n"
              << "Version: " << glGetString(GL_VERSION) << "\n"
              << std::endl;

    if (!GLAD_GL_VERSION_4_1) {
        throw std::runtime_error("Your OpenGL version is too low, expected 4.1 or higher.");
    }

    SDL_ShowWindow(_window.get());

    // Optionally initialize the renderer if needed
    _renderer = std::unique_ptr<SDL_Renderer, SDLDestroyer>(
        SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED));
    if (_renderer == nullptr)
        throw std::runtime_error("SDL2 Renderer couldn't be created: " + std::string(SDL_GetError()));
}

Window::~Window() {
    // Properly destroy the context before the window
    if (_glContext) {
        SDL_GL_DeleteContext(_glContext);
        _glContext = nullptr;
    }
    _renderer.reset();
    _window.reset();
}

void Window::SetTitle(const std::string& title)
{
    SDL_SetWindowTitle(_window.get(), title.c_str());
}

const std::string Window::GetTitle() const
{
    return SDL_GetWindowTitle(_window.get());
}

void Window::Swap()
{
    SDL_GL_SwapWindow(_window.get());
}

} // namespace Donut
