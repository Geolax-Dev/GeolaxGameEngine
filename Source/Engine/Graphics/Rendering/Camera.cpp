#include "Camera.h"

#include <Graphics/Rendering/RendererMaster.h>

GGE::Camera GGE::Camera::CreatePerspective(const CreationOptions& opts)
{
    Camera newInstance{};
    newInstance.SetViewport(opts.viewSize);
    newInstance.SetFovY(opts.fovY);
    newInstance.SetZParams(opts.zParams);
    newInstance.SetPerspectiveMode();
    newInstance.Update();
    return newInstance;
}

GGE::Camera GGE::Camera::CreateOrthographic(const CreationOptions& opts)
{
    Camera newInstance{};
    newInstance.SetViewport(opts.viewSize);
    newInstance.SetFovY(opts.fovY);
    newInstance.SetZParams(opts.zParams);
    newInstance.SetOrthographicMode();
    newInstance.Update();
    return newInstance;
}

void GGE::Camera::Update()
{

    if (m_dirty.proj)
    {
        m_proj = (m_isOrtho ? makeOrthographic(m_viewSize, m_zParams) : makePerspective(m_fovY, m_aspectRatio, m_zParams));
        m_dirty.proj = false;
        m_dirty.viewProj = m_dirty.invViewProj = true;
    }

    if (m_dirty.view)
    {
        float4x4 world = float4x4::identity();
        world = mul(world, float4x4::rotation_y(m_rotationEuler.y));
        world = mul(world, float4x4::rotation_x(m_rotationEuler.x));
        world = mul(world, float4x4::rotation_z(m_rotationEuler.z));
        world = mul(world, float4x4::translation(m_position));
        m_view = inverse(world);

        m_dirty.view = false;
        m_dirty.viewProj = m_dirty.invViewProj = true;
    }

    if (m_dirty.viewProj)
    {
        m_viewProj = mul(m_view, m_proj);
        m_dirty.viewProj = false;
    }

    if (m_dirty.invViewProj)
    {
        m_invViewProj = inverse(m_viewProj);
        m_dirty.invViewProj = false;
    }
}

void GGE::Camera::SetViewport(const float2& size)
{
    m_viewSize = size;
    
    if (!m_isOrtho)
        m_aspectRatio = size.x / size.y;

    m_dirty.proj = true;
}

void GGE::Camera::SetPerspectiveMode()
{
    m_isOrtho = false;
    m_dirty.proj = true;
}

void GGE::Camera::SetOrthographicMode()
{
    m_isOrtho = true;
    m_dirty.proj = true;
}

void GGE::Camera::SetPosition(const float3& pos)
{
    m_position = pos;
    m_dirty.view = true;
}

void GGE::Camera::AddPosition(const float3& deltaPos)
{
    m_position += deltaPos;
    m_dirty.view = true;
}

void GGE::Camera::SetOrientation(const float3& euler)
{
    m_rotationEuler = euler;
    m_dirty.view = true;
}

void GGE::Camera::AddOrientation(const float3& deltaEuler)
{
    m_rotationEuler += deltaEuler;
    m_dirty.view = true;
}

void GGE::Camera::SetFovY(float inDegrees)
{
    m_fovY = radians(inDegrees);
    m_dirty.proj = true;
}

void GGE::Camera::SetAspectRatio(float rat)
{
    m_aspectRatio = rat;
    m_dirty.proj = true;
}

void GGE::Camera::SetZParams(const float2& zParams)
{
    m_zParams = zParams;
    m_dirty.proj = true;
}

void GGE::Camera::LookAt(const float3& eye, const float3& target, const float3& up)
{
    m_position = eye;

    const float3 f = normalize(target - eye);
    const float3 r = normalize(cross(up, f));
    const float3 u = cross(f, r);

    // yaw (y), pitch (x), roll (z)
    const float yaw = atan2f(r.z, r.x) * -1.0f;          // derive from basis
    const float pitch = asinf(-f.y);
    const float roll = atan2f(u.x, u.y);

    m_rotationEuler = float3(pitch, yaw, roll);

    m_dirty.view = true;   // will rebuild from pos+euler
}

GGE::CameraControl::CameraControl(const Camera::CreationOptions& options, bool perspective)
{
    CreateCamera(options, perspective);
}

GGE::Camera& GGE::CameraControl::CreateCamera(const Camera::CreationOptions& options, bool perspective)
{
    m_activeCameraIndex++;
    auto& camera = m_cameras.emplace_back();
    camera = (perspective ? Camera::CreatePerspective(options) : Camera::CreateOrthographic(options));
    return camera;
}
