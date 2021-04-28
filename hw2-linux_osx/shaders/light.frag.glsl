# version 330 core
// Do not use any version older than 330!

/* This is the fragment shader for reading in a scene description, including 
   lighting.  Uniform lights are specified from the main program, and used in 
   the shader.  As well as the material parameters of the object.  */

// Inputs to the fragment shader are the outputs of the same name of the vertex shader.
// Note that the default output, gl_Position, is inaccessible!
in vec3 mynormal;
in vec4 myvertex; 

// You will certainly need this matrix for your lighting calculations
uniform mat4 modelview;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;

uniform vec3 color;

const int numLights = 10;
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights 
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used

// Now, set the material parameters.
// I use ambient, diffuse, specular, shininess. 
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emission;
uniform float shininess;
vec4 computeLight(const in vec3 direction, const in vec4 lightColor, const in vec3 normal, const in vec3 halfvec, const in vec4 objDiffuse, const in vec4 objSpecular, const in float objShininess) {
    float nDotL = dot(normal, direction);
    vec4 lambert = objDiffuse * max(nDotL, 0.0);

    float nDotH = dot(normal, halfvec);
    vec4 phong = objSpecular * pow(max(nDotH, 0.0), objShininess);

    vec4 retval = lightColor * (lambert + phong);
    return retval;
}
void main(void) {
    if(enablelighting) {
        vec4 finalcolor; 

        // YOUR CODE FOR HW 2 HERE
        // A key part is implementation of the fragment shader

        // Color all pixels black for now, remove this in your implementation!
        const vec3 eyepos = vec3(0, 0, 0);
        vec4 vertex = (modelview) * myvertex;

        vec3 mypos = vertex.xyz / vertex.w; // Dehomogenize current location 
        vec3 eyedirn = normalize(eyepos - mypos); 

        // Compute normal, needed for shading. 
        vec3 normal = normalize(mat3(transpose(inverse(modelview))) * mynormal);

        finalcolor = ambient + emission;
        for(int i = 0; i < numLights; i++) {
            // Directional 
            if(lightposn[i].w == 0) {
                vec4 lightPos = lightposn[i];
                vec4 lightCol = lightcolor[i];
                vec3 direction = normalize(lightPos.xyz);
                vec3 halfVec = normalize(direction + eyedirn);
                finalcolor += computeLight(direction, lightCol, normal, halfVec, diffuse, specular, shininess);
            }
            //Point
            else {
                vec4 lightPos = lightposn[i];
                vec4 lightCol = lightcolor[i];
                vec3 position = lightPos.xyz / lightPos.w;
                vec3 direction = normalize(position - mypos); // no attenuation 

                vec3 halfVec = normalize(direction + eyedirn);
                finalcolor += computeLight(direction, lightCol, normal, halfVec, diffuse, specular, shininess);
            }
        }

        fragColor = finalcolor;
    } else {
        fragColor = vec4(color, 1.0f);
    }
}
