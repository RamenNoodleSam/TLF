#ifndef GLOBALASSETPOOL_H
#define GLOBALASSETPOOL_H

/* Filename: GlobalAssetPool.h
 * Description: Placeholder for a more in-depth management system of certain objects.
 *			    Implements a simple Singleton pattern to prevent multiple copies of global assets
 *				and to achieve a tied-in global state.
 */

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