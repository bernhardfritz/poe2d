#include "lightpass.hpp"
#include <xd/xd.hpp>
#include <algorithm>

using namespace xd;
using namespace std;

LightPass::LightPass(initializer_list<RenderPass*> renderPasses, Camera& camera) : RenderPass(renderPasses), camera(camera) {
    lights.reserve(MAX_LIGHTS);
    initShaderProgram();
}

const string LightPass::getFragmentShaderCode() {
    return 
        "#version 330 core\n"
        "\n"
        "uniform sampler2D uTexture0;\n"
        "uniform vec2 uResolution;\n"
        "uniform float uSeconds;\n"
        "\n"
        "uniform int uN;\n"
        "\n"
        "struct Light {\n"
        "    int lightType;\n"
        "    vec2 lightPos;\n"
        "    vec4 color;\n"
        "    float intensity;\n"
        "};\n"
        "\n"
        "uniform Light lights[" + to_string(MAX_LIGHTS) + "];\n"
        "\n"
        "in vec2 vUV;\n"
        "out vec4 fragColor;\n"
        "\n"
        "vec4 toGamma(vec4 color) {\n"
        "    return pow(color,vec4(1.0/2.2));\n"
        "}\n"
        "\n"
        "vec4 calculateLight(Light light) {\n"
        "    vec2 res = normalize(uResolution);\n"
        "    float dist = distance(vUV.xy * res, light.lightPos * res) / light.intensity;\n"
        "    float lightness;\n"
        "    if (light.lightType == 0) {\n"
        "        lightness = 1.0 / (dist * dist); // inverse square law\n"
        "    } else {\n"
        "        lightness = max(0.0, 1.0 - dist);\n"
        "    }\n"
        "    return light.color * lightness; // or vec4(light.color.rgb * lightness, 1.0)\n"
        "}\n"
        "\n"
        "void main(void) {\n"
        "    vec4 color = vec4(0.0);\n"
        "    for (int i = 0; i < uN; i++) {\n"
        "        color += calculateLight(lights[i]);\n"
        "    }\n"
        "\n"
        "    color = toGamma(color);\n"
        "\n"
        "    fragColor = texture(uTexture0, vUV) * color;\n"
        "}\n"
    ;
}

void LightPass::createUniforms() {
    RenderPass::createUniforms();
    shaderProgram->createUniform("uN");
    for (int i = 0; i < MAX_LIGHTS; i++) {
        string s = to_string(i);
        shaderProgram->createUniform("lights[" + s + "].lightType");
        shaderProgram->createUniform("lights[" + s + "].lightPos");
        shaderProgram->createUniform("lights[" + s + "].color");
        shaderProgram->createUniform("lights[" + s + "].intensity");
    }
}

void LightPass::updateUniforms() {
    RenderPass::updateUniforms();
    int n = std::min((int) lights.size(), MAX_LIGHTS);
    shaderProgram->setUniform("uN", n);
    int i = 0;
    for (int i = 0; i < n; i++) {
        string s = to_string(i);
        auto light = lights.at(i);
        shaderProgram->setUniform("lights[" + s + "].lightType", light.lightType);
        vec2 screen = camera.worldToScreen(light.lightPos);
        vec2 convertedPosition = vec2(screen.x / width, 1.0f - screen.y / height);
        shaderProgram->setUniform("lights[" + s + "].lightPos", convertedPosition);
        shaderProgram->setUniform("lights[" + s + "].color", light.color);
        shaderProgram->setUniform("lights[" + s + "].intensity", light.intensity);
    }
}
