namespace WoW {

	class GrindBot {
	public:
		static vector<string> mobList;
		static std::string GetMobName();
		static void Fight();
	private:
		static void WalkToTarget(WObject* localplayer, WObject* Target);
		static bool Rest(WObject* localplayer);
		static bool DistCheck(WObject* LocalPlayer, WObject* Target, int SpellID, float DistTo);
		static bool Buff(WObject* localplayer);
		static void CleanUp();
	
		static WObject* HostileUnit_TargetingUs(/*CGGuid* NPCGUID*/);
		static WObject* GetClosestMob();
		static WObject* GetClosestDeathMob();
		static void CastSpell(WObject* Unit, int SpellID);
		static int GetSpellID(WObject* LocalPlayer, WObject* Target);

	};
}
