#version 430 core
        layout (location = 0) in vec3 aPos;
        layout (location = 2) in vec3 aFragColor;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        out vec3 color;
        void main()
        {
                color = aFragColor;
                gl_Position = projection * view * model * vec4(aPos,1.0);
        };
