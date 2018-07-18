#ifndef LIGHTPASS_HPP
#define LIGHTPASS_HPP

#include <xd/passthrough.hpp>
#include "camera.hpp"

struct Light {
    enum LightType { POINT, SPOT };
    LightType lightType;
	glm::vec2 lightPos;
	glm::vec4 color;
	float intensity;
};

const int MAX_LIGHTS = 16;

class LightPass : public xd::Passthrough {
public:
    Camera& camera;
    std::vector<Light> lights;
    LightPass(std::initializer_list<RenderPass*> renderPasses, Camera& camera);
protected:
    virtual const std::string getFragmentShaderCode();
    virtual void createUniforms();
    virtual void updateUniforms();
};

#endif
