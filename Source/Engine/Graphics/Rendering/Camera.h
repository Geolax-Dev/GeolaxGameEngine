#pragma once

#include <Graphics/Utils.h>
#include <Core/Singleton.h>

namespace GGE
{
    class Camera
    {
    public:
        struct CreationOptions
        {
            float2 viewSize{ 1280u, 720u };
            float fovY = GetDefaultFOV();
            float2 zParams{ GetDefaultZParams() };
        };
        static Camera CreatePerspective(const CreationOptions& opts);
        static Camera CreateOrthographic(const CreationOptions& opts);

        void Update();

        void SetViewport(const float2& size);
        void SetPerspectiveMode();
        void SetOrthographicMode();
        void SetPosition(const float3& pos);
        void AddPosition(const float3& deltaPos);
        void SetOrientation(const float3& euler);
        void AddOrientation(const float3& deltaEuler);
        void SetFovY(float inDegrees);
        void SetAspectRatio(float); // you don't need this method, really.
        void SetZParams(const float2& zParams);

        static float GetDefaultFOV() { return 60.f; }
        static float2 GetDefaultZParams() { return { 0.1f, 10000.f }; }

        void LookAt(const float3& eye, const float3& target, const float3& up = { 0, 1, 0 });

        float3 const& GetPosition() const { return m_position; }
        float3 const& GetOrientation() const { return m_rotationEuler; }
        float2 const& GetViewportSize() const { return m_viewSize; }
        float GetFovY() const { return m_fovY; }
        float GetAspectRatio() const { return m_aspectRatio; }
        float GetZNear() const { return m_zParams.x; }
        float GetZFar() const { return m_zParams.y; }
        float2 const& GetZParams() const { return m_zParams; }
        bool IsPerspective() const { return !m_isOrtho; }
        bool IsOrthographic() const { return m_isOrtho; }

        float4x4 GetView() const { return m_view; }
        float4x4 GetProj() const { return m_proj; }
        float4x4 GetViewProj() const { return m_viewProj; }
        float4x4 GetInvViewProj() const { return m_invViewProj; }
        const float* GetViewP() const { return (const float*)&m_view; }
        const float* GetProjP() const { return (const float*)&m_proj; }
        float3 GetForward() const { return getForward(); }
        float3 GetRight() const { return getRight(); }
        float3 GetUp() const { return getUp(); }

        frustum GetFrustum() const { return frustum(m_viewSize.x, m_viewSize.y, m_zParams.x, m_zParams.y); }
    private:
        float4x4 m_view{ float4x4::identity() };
        float4x4 m_proj{ float4x4::identity() };
        float4x4 m_viewProj{ float4x4::identity() };
        float4x4 m_invViewProj{ float4x4::identity() };

        float3 m_position{};
        float3 m_rotationEuler{};

        float2 m_viewSize{ 1280, 720 };
        float m_fovY{ radians(60.f) };
        float m_aspectRatio{ 16.f / 9.f };
        float2 m_zParams{ 0.1f, 10000.f };
        bool m_isOrtho{ false };

        struct
        {
            bool view{};
            bool proj{};
            bool viewProj{};
            bool invViewProj{};
        } m_dirty;


        static float4x4 makeOrthographic(const float2& size, const float2& zParams)
        {
            return float4x4::orthographic(
                projection(
                    frustum(size.x, size.y, zParams.x, zParams.y),
                    bgfx::getCaps()->homogeneousDepth ? zclip::minus_one : zclip::zero,
                    zdirection::forward,
                    zplane::finite)
            );
        }

        static float4x4 makePerspective(float fovYrad, float aspectRatio, const float2& zParams)
        {
            return float4x4::perspective(
                projection(
                    frustum::field_of_view_y(fovYrad, aspectRatio, zParams.x, zParams.y),
                    bgfx::getCaps()->homogeneousDepth ? zclip::minus_one : zclip::zero,
                    zdirection::forward,
                    zplane::finite
                )
            );
        }

        static void basisFromEulerXYZ(const float3& e, float3* r, float3* u, float3* f)
        {
            const float cx = cosf(e.x), sx = sinf(e.x);
            const float cy = cosf(e.y), sy = sinf(e.y);
            const float cz = cosf(e.z), sz = sinf(e.z);

            // Rotation order: Rx * Ry * Rz (matches checkView)
            // Derived basis columns of world matrix (before translation)
            if (r) *r = normalize(float3(cz * cy, sz * cy, -sy));
            if (u) *u = normalize(float3(cz * sy * sx - sz * cx, sz * sy * sx + cz * cx, cy * sx));
            if (f) *f = normalize(float3(cz * sy * cx + sz * sx, sz * sy * cx - cz * sx, cy * cx));
        }

        float3 getForward() const { float3 v; basisFromEulerXYZ(m_rotationEuler, nullptr, nullptr, &v); return v; }
        float3 getRight()   const { float3 v; basisFromEulerXYZ(m_rotationEuler, &v, nullptr, nullptr); return v; }
        float3 getUp()      const { float3 v; basisFromEulerXYZ(m_rotationEuler, nullptr, &v, nullptr); return v; }
    };

    // TODO: add capabilities for smooth transition (in-space-fly) between cameras via 'virtual camera'

    class CameraControl
    {
    public:
        CameraControl(const Camera::CreationOptions& options, bool perspective = true);
        ~CameraControl() = default;

        Camera& CreateCamera(const Camera::CreationOptions& options, bool perspective = true);

        size_t GetCount() const { return m_cameras.size(); }

        void SetActiveIndex(size_t index) { m_activeCameraIndex = std::clamp<size_t>(index, 0, m_cameras.size() - 1); }
        size_t GetActiveIndex() const { return m_activeCameraIndex; }

        Camera& GetActive() { return m_cameras[m_activeCameraIndex]; }
        const Camera& GetActive() const { return m_cameras[m_activeCameraIndex]; }

        Camera& GetCamera(size_t index) { return m_cameras[index % m_cameras.size()]; }
        const Camera& GetCamera(size_t index) const { return m_cameras[index % m_cameras.size()]; }
    private:
        std::vector<Camera> m_cameras{};
        size_t m_activeCameraIndex{ ~0ull };
    };
}
