#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Joshua Austria", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    std::string path = "3D/bunny.obj";
    std::vector <tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    tinyobj::attrib_t attributes;

    bool success = tinyobj::LoadObj(&attributes, &shapes, &material, &warning, &error, path.c_str());

    std::vector<GLuint> mesh_indices;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++)
    {
        mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
    }


    GLfloat vertices[]
    {
        0.f, 0.5f, 0.f, //0
        -0.5f, -0.5f, 0.f, //1
        0.5f, -0.5f, 0.f //2
    };

    GLuint indices[]{
        0,1,2
    };

    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Currently editing VAO = null
    glBindVertexArray(VAO);
    //Currently editing VAO = VAO

    //Currently editing VBO = null
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Currently editing VBO = VBO
    //VAO <- VBO

    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*attributes.vertices.size(), //size in bytes
        &attributes.vertices[0], //array
        GL_STATIC_DRAW);

    glVertexAttribPointer
    (0,//0 pos, 1 = norm, 2 = texture
        3, //X Y Z
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    //Currently editing VBO = VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //Currently editing VBO = EBO

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*mesh_indices.size(), &mesh_indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

       /* glBegin(GL_POLYGON);
            glVertex2f (0.0f, 0.5f);
            glVertex2f(-0.4741f, 0.15552f);
            glVertex2f(-0.294f, -0.4045f);
            glVertex2f(0.294f, -0.4045f);
            glVertex2f(0.4741f, 0.15552f);
            glEnd();
        */

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, mesh_indices.size(), GL_UNSIGNED_INT, 0);
            

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}