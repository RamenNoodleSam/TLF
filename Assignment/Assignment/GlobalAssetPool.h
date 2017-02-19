#ifndef GLOBALASSETPOOL_H
#define GLOBALASSETPOOL_H

#include <iostream>
#include <SFML/Graphics.hpp>

class GlobalAssetPool {
public:
	sf::Font m_font;

	static GlobalAssetPool* getInstance();
private:
	GlobalAssetPool();
	GlobalAssetPool(const GlobalAssetPool&);
	GlobalAssetPool(GlobalAssetPool&&);

	static GlobalAssetPool* m_self;
};

#endif