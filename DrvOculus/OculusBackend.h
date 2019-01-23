#pragma once
#include "../OpenOVR/Drivers/Backend.h"
#include "../OpenOVR/Compositor/compositor.h"

class OculusBackend : public IBackend {
public:

	OculusBackend();
	virtual ~OculusBackend() override;

	virtual void GetSinglePose(
		vr::ETrackingUniverseOrigin origin,
		vr::TrackedDeviceIndex_t index,
		vr::TrackedDevicePose_t* pose,
		ETrackingStateType trackingState) override;

	virtual void GetDeviceToAbsoluteTrackingPose(
		vr::ETrackingUniverseOrigin toOrigin,
		float predictedSecondsToPhotonsFromNow,
		vr::TrackedDevicePose_t * poseArray,
		uint32_t poseArrayCount) override;

	// submitting
	virtual void WaitForTrackingData(
	) override;

	virtual void StoreEyeTexture(
		vr::EVREye eye,
		const vr::Texture_t * texture,
		const vr::VRTextureBounds_t * bounds,
		vr::EVRSubmitFlags submitFlags,
		bool isFirstEye
	) override;

	virtual void SubmitFrames(
		bool showSkybox
	) override;

	virtual openvr_enum_t SetSkyboxOverride(
		const vr::Texture_t * pTextures,
		uint32_t unTextureCount
	) override;

	virtual void ClearSkyboxOverride(
	) override;

private:

	// Rendering stuff
	enum RenderState {
		RS_NOT_STARTED,
		RS_WAIT_BEGIN,
		RS_RENDERING,
	};

	void SubmitSkyboxFrames();

	RenderState state = RS_NOT_STARTED;
	long long frameIndex = 0;

	ovrLayerEyeFov layer;
	ovrLayerCube skyboxLayer;
	OVR::Sizei size;

	ovrTrackingState trackingState;
	double sensorSampleTime;

	ovrSessionStatus sessionStatus;

	Compositor * compositors[2] = { NULL, NULL };
	std::unique_ptr<Compositor> skyboxCompositor;

};