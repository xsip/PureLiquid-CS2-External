#pragma once
#include <CS2/Offsets/client/CSkeletonInstance.hpp>
#include <CS2/SDK/client/CGameSceneNode.hpp>
#include <GlobalData/Include.h>
namespace CS2 {
	namespace client {

		class CGameSceneNodeBonePtr {
		public:
			PROPERTY_ARRAY(m_Bones, Matrix2x4_t, 104, 0x0);

		};
		class CGameSceneNodeExtended : public CGameSceneNode {
		private:
			inline static uint32_t dwBonesOffset = 0x0;
			static uint32_t GetBonesOffset();

		public:
			RUNTIME_OFFSET_PROPERTY(pGameSceneNodeBonePtr, CGameSceneNodeBonePtr*, GetBonesOffset);
		};
	}
}