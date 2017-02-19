#include "GlobalAssetPool.h"

GlobalAssetPool* GlobalAssetPool::m_self = nullptr;

GlobalAssetPool* GlobalAssetPool::getInstance() {
	if (m_self == nullptr) {
		m_self = new GlobalAssetPool;
	}

	return m_self;
}

GlobalAssetPool::GlobalAssetPool() {
	if (!m_font.loadFromFile("Media/Fonts/font.ttf")) {
		std::cout << "Failed to load font from file, check \"Media/Fonts/font.ttf\" exists." << std::endl;
	}
}