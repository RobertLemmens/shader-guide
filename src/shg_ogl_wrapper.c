#include "shg_ogl_wrapper.h"

GLuint ogl_generate_vertex_array() {
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  return vao;
}

GLuint ogl_generate_buffer(uint32_t size, void *data) {
  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  return buffer;
}

GLuint ogl_generate_element_buffer(uint32_t size, void *data) {
  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  return buffer;
}

void ogl_bind_shape(GLuint vao, GLuint vbo) {
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);

  // For the positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

  // For the normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

  // For the UVs
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uv));
}

void ogl_draw_triangles(uint32_t size) {
  glDrawArrays(GL_TRIANGLES, 0, size);
}

bool read_file_to_string(const char *file, char **buffer) {
  char *source = NULL;
  FILE *fp = fopen(file, "r");
  if (fp != NULL) {
    /* Go to the end of the file. */
    if (fseek(fp, 0L, SEEK_END) == 0) {
      /* Get the size of the file. */
      long bufsize = ftell(fp);
      if (bufsize == -1) { /* Error */ }

      /* Allocate our buffer to that size. */
      source = malloc(sizeof(char) * (bufsize + 1));

      /* Go back to the start of the file. */
      if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }

      /* Read the entire file into memory. */
      size_t newLen = fread(source, sizeof(char), bufsize, fp);
      if ( ferror( fp ) != 0 ) {
        return false;
      } else {
        source[newLen++] = '\0'; /* Just to be safe. */
      }
    }
    fclose(fp);
  } else {
    printf("Could not find %s\n", file);
    return false;
  }

  *buffer = source;

  return true;
}

GLuint ogl_compile_shader(const char *fragment_path, const char *vertex_path, const char *geometry_path) {

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint geometry_shader_id = glCreateShader(GL_GEOMETRY_SHADER);

    char *vertex_shader_buffer;
    if (read_file_to_string(vertex_path, &vertex_shader_buffer) == false) {
      printf("Error reading vertex shader %s\n", vertex_path);
    }
    char *fragment_shader_buffer;
    if (read_file_to_string(fragment_path, &fragment_shader_buffer) == false) {
      printf("Error reading fragment shader %s\n", fragment_path);
    }
    char *geometry_shader_buffer = NULL;
    if (geometry_path) {
      if (read_file_to_string(geometry_path, &geometry_shader_buffer) == false) {
        printf("Error reading geometry shader %s\n", geometry_path);
      }
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    char const *VertexSourcePointer = vertex_shader_buffer;
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
      char error_message[256];
      glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &error_message[0]);
      printf("%s\n", &error_message[0]);
      printf("Error compiling vertex shader\n", NULL);
    }

    char const *FragmentSourcePointer = fragment_shader_buffer;
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
      char error_message[256];
      glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &error_message[0]);
      printf("%s\n", &error_message[0]);
      printf("Error compiling fragment shader %s\n", fragment_path);
    }


    if (geometry_shader_buffer) {
      char const *geometry_source_pointer = geometry_shader_buffer;
      glShaderSource(geometry_shader_id, 1, &geometry_source_pointer, NULL);
      glCompileShader(geometry_shader_id);

      // Check Geometry Shader
      glGetShaderiv(geometry_shader_id, GL_COMPILE_STATUS, &Result);
      glGetShaderiv(geometry_shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
      if (InfoLogLength > 0) {
        char error_message[256];
        glGetShaderInfoLog(geometry_shader_id, InfoLogLength, NULL, &error_message[0]);
        printf("%s\n", &error_message[0]);
        printf("Error compiling geometry shader %s\n", geometry_path);
      }
    }

    // Link the program
    printf("Linking program\n", NULL);
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    if (geometry_path) {
      glAttachShader(ProgramID, geometry_shader_id);
    }
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
      char error_message[512];
      glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &error_message[0]);
      printf("%s\n", &error_message[0]);
      printf("Shader program error\n", NULL);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    if (geometry_path) {
      glDetachShader(ProgramID, geometry_shader_id);
    }

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    if (geometry_path) {
      glDeleteShader(geometry_shader_id);
    }

    // Free our shaders
    free(vertex_shader_buffer);
    free(fragment_shader_buffer);
    free(geometry_shader_buffer);

  return ProgramID;
}

void ogl_clear(float r, float g, float b) {
  glClearColor(r, g, b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void ogl_bind_shader(GLuint shader_id) {
  glUseProgram(shader_id);
}

GLint ogl_get_uniform_location(GLuint shader_id, const char *location_name) {
  return glGetUniformLocation(shader_id, location_name);
}

void ogl_upload_mat4(GLint location_id, mat4 uniform) {
  glUniformMatrix4fv(location_id, 1, GL_FALSE, &uniform[0][0]);
}
