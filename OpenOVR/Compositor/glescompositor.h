#pragma once

#include "compositor.h"

class GLESCompositor : public Compositor {
public:
	explicit GLESCompositor();

	// Override
	void Invoke(const vr::Texture_t* texture) override;

	void Invoke(XruEye eye, const vr::Texture_t* texture, const vr::VRTextureBounds_t* bounds,
	    vr::EVRSubmitFlags submitFlags, XrCompositionLayerProjectionView& viewport) override;

	void InvokeCubemap(const vr::Texture_t* textures) override;

private:
	void CheckCreateSwapChain(GLuint image);

	GLuint fboId = 0;

	std::vector<GLuint> images;
};
