add_rules("mode.debug", "mode.release")

add_requires("glfw", "opengl", "glad", "glm", "luajit")
add_requires("imgui", {configs={opengl3 = true, glfw = true}})

set_languages("cxx23")
target("opengl-test")
    set_kind("binary")
    add_files("src/**.cpp")
    add_includedirs("extern/vendor/stb")
    add_packages("glfw", "opengl", "glm", "glad", "imgui", "luajit")
