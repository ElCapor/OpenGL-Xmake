add_rules("mode.debug", "mode.release")

add_requires("glfw", "opengl", "glad", "glm", "luajit")
add_requires("imgui", {configs={opengl3 = true, glfw = true}})

set_languages("cxx23")
target("opengl-test")
    -- Settings
    set_kind("binary")

    -- Source Files
    add_files("src/**.cpp")

    -- Include Directories
    add_includedirs("extern/vendor/stb")

    -- Packages
    add_packages("glfw", "opengl", "glm", "glad", "imgui", "luajit")

    -- Post-build events
    after_build(function (target)
        local binary_dir = path.directory(target:targetfile())
        os.cp("resources", binary_dir)
    end)