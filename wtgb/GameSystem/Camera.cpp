#include "pch\pch.h"
#include "Camera.h"
#include "GameSystem/GameWindow.h"

wtgb::Camera::Camera() :
	position_{ Vector3::Zero() },
	targetPosition_{ Vector3::Forward() }
{
}

wtgb::Camera::~Camera()
{
}

wtgb::Result wtgb::Camera::Init(const ViewerInit& _viewer)
{
	using DirectX::XMMatrixPerspectiveFovLH;
	using DirectX::XM_PIDIV4;

	const Vector2Int SCREEN_SIZE{ _viewer.Get<GameWindow>().GetMainWindowSize() };

	projectionMatrix_ = XMMatrixPerspectiveFovLH(
		XM_PIDIV4,
		static_cast<float>(SCREEN_SIZE.x) / static_cast<float>(SCREEN_SIZE.y),
		0.1f,
		100.0f);

	return Result::Code::Ok;
}

void wtgb::Camera::Update(const ViewerUpdate& _system)
{
	using DirectX::XMMatrixLookAtLH;

	viewMatrix_ = XMMatrixLookAtLH(
		position_,
		targetPosition_,
		{ 0, 1, 0, 0 });
}

void wtgb::Camera::End()
{
}

wtgb::Matrix4x4 wtgb::Camera::GetProjectionMatrix() const
{
	return projectionMatrix_;
}

wtgb::Matrix4x4 wtgb::Camera::GetViewMatrix() const
{
	return viewMatrix_;
}
