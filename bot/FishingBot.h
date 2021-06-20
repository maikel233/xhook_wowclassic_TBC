#pragma once
#include "DllMain.h"
#include "Hacks.h"


namespace WoW {
	// (apprentice, journeyman, expert, artisan)
	//fishing_spell_ids = { 7620, 7731, 7732, 18248 };
	class FishBot{
	public:
	static void Fish();

	private:
		static int GetFishingLevel();
		enum FishingLevels
		{
			apprentice = 7620,
			journeyman = 7731,
			expert = 7732,
			artisan = 18248
		};
	};
}
