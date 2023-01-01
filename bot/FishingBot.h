#pragma once
#include "DllMain.h"
#include "Hacks.h"

namespace WoW {
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
			artisan = 18248,
			master = 33095,
			GrandMaster = 51294
		};
	};
}
