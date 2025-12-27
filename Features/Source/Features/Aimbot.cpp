#include <GlobalData/Include.h>
#include <Features/Aimbot.h>
#include <CS2/Interfaces/Include.h>
#include <CS2/Interfaces/CGameTraceManager.h>
#include <CS2/ExtendedSDK/client/C_CSPlayerPawn.h>
#include <Math/Vector.h>
#include <Math/QAngle.h>
#include <Math/Matrix.h>
#include <Math/Ray.h>
#include <thread>

#include <Source2/CUtlVector.h>
#include <algorithm>

QAngle oldPunch{};

Aimbot::FOVResult Aimbot::GetTargetFOVAndDistance(
    const Vector3& eyePos,
    const Vector3& viewDir,
    const Vector3& targetPos)
{
    Vector3 forward = viewDir.Normalized();
    Vector3 toTarget = targetPos - eyePos;
    float distance = toTarget.Length();
    toTarget = toTarget.Normalized();

    float dot = forward.DotProduct(toTarget);
    dot = std::clamp(dot, -1.0f, 1.0f);

    float fovDeg = acosf(dot) * 180.0f / 3.14159265f;

    return { fovDeg, distance };
}
void Aimbot::Run() {


    auto pLocalPawn = CS2::CGameEntitySystem::vEntityList[1].m_pPawn;
    
    Vector vecView = pLocalPawn->m_vecViewOffset;
    Vector vLocalPos = pLocalPawn->m_vOldOrigin + vecView;
    
    auto vViewAngles = CS2::I::pCsGoInput->vViewAngles;

    for (int i = 1; i < 65; i++) {
        auto entity = &CS2::CGameEntitySystem::vEntityList[i];

        if (!entity->m_bIsAlive || !entity->m_bIsValid) {
            if (bestTarget.entity == entity)
                ResetTarget();
            continue;
        }

        auto entityPawn = entity->m_pPawn;
        if (!entityPawn || entityPawn == pLocalPawn)
            continue;

        auto boneMatrix = entityPawn->GetBoneMatrices(iTargetBone + 1);

        if (boneMatrix.empty()) {
            if (bestTarget.entity == entity)
                ResetTarget();
            continue;
        }


        if (entity->m_pPawn->m_iTeamNum == pLocalPawn->m_iTeamNum && m_bIgnoreTeamMembers)
            continue;

        Vector vEnemyHead = boneMatrix[iTargetBone].GetOrigin();
        if (!vEnemyHead.IsValid()) {
            if (bestTarget.entity == entity)
                ResetTarget();
            continue;
        }

        Vector viewDir = vViewAngles.AngleToDirection();
        auto targetInfo = GetTargetFOVAndDistance(vLocalPos, viewDir, vEnemyHead);

        const float FOV_WEIGHT = 1.0f; 
        const float DISTANCE_WEIGHT = 0.02f;
        entity->flAimbotFov = targetInfo.fovDeg;
        if (targetInfo.fovDeg <= flMaxFov / (targetInfo.distance / 100) && targetInfo.fovDeg > 0.0f) {

            float score = targetInfo.fovDeg * FOV_WEIGHT + targetInfo.distance * DISTANCE_WEIGHT;
            float bestScore = bestTarget.fovDeg * FOV_WEIGHT + bestTarget.distance * DISTANCE_WEIGHT;

            const float DISTANCE_THRESHOLD = 50.0f;
            if (score < bestScore || targetInfo.distance + DISTANCE_THRESHOLD < bestTarget.distance) {
                bestTarget.fovDeg = targetInfo.fovDeg;
                bestTarget.distance = targetInfo.distance;
                bestTarget.entity = entity;
                bestTargetIdx = i;
                targetBoneIdx = iTargetBone;
            }
        }

        if (bestTarget.entity) {
            auto bestBoneMatrix = bestTarget.entity->m_pPawn->GetBoneMatrices(targetBoneIdx + 1);
            if (bestBoneMatrix.empty()) {
                ResetTarget();
                continue;
            }

            auto bestTargetFov = GetTargetFOVAndDistance(vLocalPos, viewDir, bestBoneMatrix.at(targetBoneIdx).GetOrigin());
            if (!bestTarget.entity->m_bIsAlive || !bestTarget.entity->m_bIsValid || bestTargetFov.fovDeg > flMaxFov / (bestTargetFov.distance / 100)) {
                ResetTarget();
            }
        }
    }

    if (GetAsyncKeyState(iAimKey) < 0) {


        if (bestTarget.entity) {

            auto boneMatrix = bestTarget.entity->m_pPawn->GetBoneMatrices(targetBoneIdx + 1);
            if (boneMatrix.empty())
                return;

            if (!CS2::I::pGameTraceManager->IsPlayerVisible(pLocalPawn, bestTarget.entity->m_pPawn))
                return;
       
            auto aimAngle = (boneMatrix.at(targetBoneIdx).GetOrigin() - vLocalPos).RelativeAngle();
            aimAngle.ClampAngle();
            CS2::I::pCsGoInput->vViewAngles = aimAngle;
            if (bAuthoShoot)
                CS2::I::pCsGoInput->Attack();

            if (!bestTarget.entity->m_bIsAlive)
                ResetTarget();
        }
    }
}


void Aimbot::ResetTarget() {
    bestTarget.distance = 100000.0f;
    bestTarget.fovDeg = 360.0f;
    bestTarget.entity = nullptr;
    bestTargetIdx = -1;
    targetBoneIdx = -1;
}

void Aimbot::AimbotThread() {
    ResetTarget();
    while (true) {
        Run();
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}