#include "ofxChromaKey.h"

ofxChromaKey::ofxChromaKey(){
    keyColor = ofColor(0.0, 1.0, 0.0);
    threshold = 0.1;
    string vertex;
    string fragment;
    
    if(ofIsGLProgrammableRenderer()){
        vertex = R"END(
        #version 150
        uniform mat4 modelViewProjectionMatrix;
        in vec4 position;
        in vec2 texcoord;
        out vec2 texCoordVarying;
        void main()
        {
            texCoordVarying = texcoord;
            gl_Position = modelViewProjectionMatrix * position;
        }
        )END";
        
        fragment = R"END(
        #version 150
        uniform sampler2DRect tex0;
        uniform float threshold;
        uniform vec3 chromaKeyColor;
        in vec2 texCoordVarying;
        out vec4 outputColor;
        void main()
        {
            vec4 texel0 = texture(tex0, texCoordVarying);
            float diff = length(chromaKeyColor - texel0.rgb);
            if(diff < threshold){
                discard;
            }else{
                outputColor = texel0;
            }
        }
        )END";
    }else{
        vertex = R"END(
        #version 120
        varying vec2 texCoordVarying;
        void main()
        {
            texCoordVarying = gl_MultiTexCoord0.xy;
            gl_Position = ftransform();
        }
        )END";
        
        fragment = R"END(
        #version 120
        uniform sampler2DRect tex0;
        uniform float threshold;
        uniform vec3 chromaKeyColor;
        varying vec2 texCoordVarying;
        void main()
        {
            vec4 texel0 = texture2DRect(tex0, texCoordVarying);
            float diff = length(chromaKeyColor - texel0.rgb);
            if(diff < threshold){
                discard;
            }else{
                gl_FragColor = texel0;
            }
        }
        )END";
    }
    
    shader.setupShaderFromSource(GL_VERTEX_SHADER, vertex);
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragment);
    shader.bindDefaults();
    shader.linkProgram();
}

void ofxChromaKey::begin(){
    shader.begin();
    shader.setUniform3f("chromaKeyColor", ofVec3f(keyColor.r, keyColor.g, keyColor.b));
    shader.setUniform1f("threshold", threshold);
}

void ofxChromaKey::end(){
    shader.end();
}
