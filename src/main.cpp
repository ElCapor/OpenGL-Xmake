#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <iostream>
#include <stdexcept>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <vector>
#include <functional>
#include "Shaders.hpp"
#include "utils/ResourceManager.hpp"
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

ResourceManager* rsrc = new ResourceManager();
class Widget
{
public:
    virtual void Init() = 0;
    virtual void Render(double dt) = 0;

    bool &IsInit() { return isInit; }

private:
    bool isInit = false;
};

class UiMgr
{
public:
    bool Init(GLFWwindow *window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO &io = ImGui::GetIO();
        (void)io;

        // setup platform/renderer bindings
        if (!ImGui_ImplGlfw_InitForOpenGL(window, true))
        {
            return false;
        }
        if (!ImGui_ImplOpenGL3_Init())
        {
            return false;
        }
    }

    void Update()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        for (auto &widget : m_Widgets)
        {
            if (!widget->IsInit())
            {
                widget->Init();
                widget->IsInit() = true;
            }
            widget->Render(ImGui::GetIO().DeltaTime);
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void AddWidget(Widget *w)
    {
        m_Widgets.push_back(w);
    }

    ~UiMgr()
    {
        m_Widgets.clear();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

private:
    std::vector<Widget *> m_Widgets;
};

class Wiglet{
public:
    virtual void wig() = 0;
    bool isInit = false;
};

class TriangleWiglet : public Wiglet{
    void wig() override
    {
        if (!isInit)
        {
            // set up vertex data (and buffer(s)) and configure vertex attributes
            // ------------------------------------------------------------------
            float vertices[] = {
                -0.5f, -0.5f, 0.0f, // left  
                0.5f, -0.5f, 0.0f, // right 
                0.0f,  0.5f, 0.0f  // top   
            }; 
        }
        

    }
};

class GLFWApp
{
public:
    GLFWApp()
    {
        ui_mgr = new UiMgr();
    }
    void Init(int width, int height, const char *name)
    {
        if (!glfwInit())
        {
            throw std::runtime_error("failed to initialize GLFW");
        }

        window = glfwCreateWindow(width, height, name, NULL, NULL);
        if (window == NULL)
        {
            throw std::runtime_error("failed to initialize window");
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialized to glad" << std::endl;
            return;
        }
        
        glViewport(0, 0, 800, 600);
        ui()->Init(window);
    }

    void Update()
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void Render()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        for (auto &wiglet : m_wiglets)
        {
            wiglet(this);
        }
        ui()->Update();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void Shutdown()
    {
        delete ui_mgr;
        glfwTerminate();
    }

    UiMgr *ui()
    {
        return ui_mgr;
    }

    GLFWwindow *w()
    {
        return window;
    }

    void Run()
    {
        Init(800, 640, "Example");
        while (!glfwWindowShouldClose(window))
        {
            Update();
            Render();
        }
        Shutdown();
    }

    void AddWiglet(std::function<void(GLFWApp *)> wiglet)
    {
        m_wiglets.push_back(wiglet);
    }

private:
    glm::ivec2 dimensions;
    GLFWwindow *window = nullptr;
    UiMgr *ui_mgr;
    std::vector<std::function<void(GLFWApp *)>> m_wiglets;
};

class FunnyWidget : public Widget
{
    void Init() override
    {
    }

    void Render(double dt) override
    {
        ImGui::ShowDemoWindow();
        if (ImGui::Button("Load Shaders"))
        {
            Shader sh(fsutils::loadFile(rsrc->ShadersPath().concat("\\vertex.vs").string()).c_str(), fsutils::loadFile(rsrc->ShadersPath().concat("\\frag.fs").string()).c_str());
        }
    }
};

void funny_wiglet(GLFWApp *app)
{
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(64.0f);
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
}

int main(int argc, char *argv[])
{
    GLFWApp app;
    app.ui()->AddWidget(new FunnyWidget());
    app.AddWiglet(funny_wiglet);
    app.Run();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}