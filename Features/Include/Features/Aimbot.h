#pragma once
#include <CS2/Interfaces/CGameEntitySystem.h>
#include <Math/Vector.h>
#include <Math/QAngle.h>

class Aimbot {
private:

	struct TargetInfo
	{
		float distance;
		float fovDeg;
		CS2::Entity* entity;
	};

	inline static int iAimKey = 4;
	inline static bool bAuthoShoot = true;
	inline static int iTargetBone = 6;
	struct FOVResult
	{
		float fovDeg;
		float distance; 
	};

	static Aimbot::FOVResult GetTargetFOVAndDistance(
		const Vector3& eyePos,
		const Vector3& viewDir,
		const Vector3& targetPos);


public:
	inline static TargetInfo bestTarget{};
	inline static int bestTargetIdx = -1;
	inline static int targetBoneIdx = -1;
	inline static float flMaxFov = 360.0f;
	inline static float flMaxDist = 1000.0f;
	inline static bool m_bIgnoreTeamMembers = true;
	static void Run();
	static void ResetTarget();
	static void AimbotThread();
};