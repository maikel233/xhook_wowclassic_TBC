#include "GrindBot.h"

//Test bot 


bool Settings::bot::Grinding::Enabled = false;
bool Wait = false;

namespace WoW {

	float NormalizeRadian(float radian)
	{
		while (radian < 0)
		{
			radian = radian + 2 * PI;
		}
		while (radian >= 2 * PI)
		{
			radian = radian - 2 * PI;
		}
		return radian;
	}

	float CalculateNeededFacing(C3Vector start, C3Vector end)
	{
		return atan2((end.y - start.y), (end.x - start.x));
	}

	float GetSideFaceRotation(float halfShootCone, WObject* target)
	{

		float angle = NormalizeRadian(CalculateNeededFacing(LuaScript::ActivePlayer->GetUnitPosition(), target->GetUnitPosition()));
		float faceTo0 = NormalizeRadian(angle - LuaScript::ActivePlayer->GetFacing());
		float faceDiff = faceTo0;
		bool objectOnRightSide = false;
		float sideFaceDiff = 0;

		if (faceTo0 >= PI)
		{
			faceDiff = 2 * PI - faceTo0;
			objectOnRightSide = true;
		}

		if (faceDiff > halfShootCone)
		{
			sideFaceDiff = faceDiff - halfShootCone;

			if (!objectOnRightSide)
			{
				return sideFaceDiff + LuaScript::ActivePlayer->GetFacing();
			}
			else
			{
				return LuaScript::ActivePlayer->GetFacing() - sideFaceDiff;
			}
		}
		else
		{
			return LuaScript::ActivePlayer->GetFacing();
		}
	}

	float GetSideFaceAngle(WObject* target)
	{

		float angle = CalculateNeededFacing(LuaScript::ActivePlayer->GetUnitPosition(), target->GetUnitPosition());
		float faceTo0 = NormalizeRadian(angle - LuaScript::ActivePlayer->GetFacing());

		if (faceTo0 > PI)
		{
			faceTo0 = -(2 * PI - faceTo0);
		}
		return faceTo0;
	}

	bool IsFacing(float angle, WObject* target)
	{
		return LuaScript::ActivePlayer->GetFacing() == GetSideFaceRotation(angle, target);
	}

	void SetFacing(float angle)
	{
		if (angle < 0.0f)
			angle += PI * 2;
		if (angle > PI * 2)
			angle -= PI * 2;


		if (!LuaScript::ActivePlayer)
			return;

		GameMethods::FaceTo(LuaScript::ActivePlayer->Ptr(), angle);
	}

	bool Face(float angle, WObject* target)
	{
		if (!IsFacing(angle, target))
		{
			float sfr = GetSideFaceRotation(angle, target);
			sfr = sfr < PI ? sfr - angle / 100 : sfr + angle / 100;

			SetFacing(sfr);
			return true;
		}
		return false;
	}


	uint32_t spellId = 133;

	bool cast_spell = false;
	void GrindBot::Fight()
	{

		//	
		//	//TO:DO
	 //       // Fix CastSpell
		//	// Get closest target? ReUse Fishing get closestNode?
		//	// Bag Detection propper loot 
		//	// Propper FindPath CTM system.
		//	// Raytrace?
		//	__try

		//		
				if (LuaScript::Objects.empty())
					return;

				//Fix GrindBot
				for (auto target : LuaScript::Objects)
				{
		//			float Mana = LuaScript::ActivePlayer->sUnitField->Energy;
		//			float MaxMana = LuaScript::ActivePlayer->sUnitField->MaxEnergy;
		//			float HP = LuaScript::ActivePlayer->sUnitField->Health;
		//			float MaxHP = LuaScript::ActivePlayer->sUnitField->MaxHealth;

		//			/*if ((HP < MaxHP / 2 || Mana < MaxMana / 2) && !LuaScript::ActivePlayer->inCombat() && !LuaScript::ActivePlayer->sUnitField->hasTarget(*target->GetGuid()))
		//			{
		//				printf("Resting\n");
		//				return;
		//			}
		//			else
		//			{*/

					if (!target->isValid() && Utils::IsEntityAlive(target))
						return;

					// Attack target.
					if (!LuaScript::ActivePlayer->sUnitField->hasTarget(*target->GetGuid()))
						LuaScript::ActivePlayer->sUnitField->Target = *target->GetGuid();

					float_t min = 0;
					float_t max = 0;
					GameMethods::GetMinMaxSpellRange(LuaScript::ActivePlayer->Ptr(), spellId, &min, &max, target->GetGuid());

					printf("%f\n", max);

					if (LuaScript::ActivePlayer->GetUnitPosition().DistanceTo(target->GetUnitPosition()) > max)
					{
						//	Hacks::CTM(target->GetUnitPosition());
						printf("Target to far! Unit.Pos at: %f %f %f", target->GetUnitPosition().x, target->GetUnitPosition().y, target->GetUnitPosition().z);
						return;
					}


					int64_t duration = 0, startTime = 0, modRate = 1;
					GameMethods::Spell_C_GetSpellCooldown(spellId, false, false, &duration, &startTime, 0, 0, 0, &modRate);
					int CastDuration = startTime + duration - (int)LuaScript::getCurrentTime();

					printf("Cast Duration: %i\n", CastDuration);

					if (CastDuration >= 0.01)
						return;

					if (LuaScript::ActivePlayer->GetSpellCastID() != 0)
						return; 

					if (cast_spell)
					{
						cast_spell = false;

						if (!GameMethods::IsSpellKnown(spellId))
							return;

						int32_t spellSlot = GameMethods::FindSlotBySpellId(spellId);
						if (!spellSlot)
							return;

						
						//This will crash teh game once in a while the fix is calling Fight(); at the mnain thread or you can try calling it from the dx thread.
						GameMethods::CastSpell(spellSlot, target->GetGuid());
						printf("Casting spell %i \n", spellId);
					}




		//				while (target->isValid() && !Utils::IsEntityAlive(target))
		//				{
		//					//// Attack target.
		//					if (!LuaScript::ActivePlayer->sUnitField->hasTarget(*target->GetGuid()))					
		//						LuaScript::ActivePlayer->sUnitField->Target = *target->GetGuid();					
		//					else
		//					{
		//					/*	if (Utils::IsEntityAlive(target) && LuaScript::ActivePlayer->GetSpellCastID() == spellId)
		//							GameMethods::Spell_CancelChannel(spellId);*/

		//						//float_t min = 0;
		//					//	float_t max = 0;
		//						//GameMethods::GetMinMaxSpellRange(LuaScript::ActivePlayer->Ptr(), spellId, &min, &max, target->GetGuid());

		//					//	printf("%f\n", max);

		//						//if (LuaScript::ActivePlayer->GetUnitPosition().DistanceTo(target->GetUnitPosition()) > max)
		//						//{
		//						////	Hacks::CTM(target->GetUnitPosition());
		//						//	printf("Target to far! Unit.Pos at: %f %f %f", target->GetUnitPosition().x, target->GetUnitPosition().y, target->GetUnitPosition().z);
		//						//}

		//		
		///*						int64_t duration = 0, startTime = 0, modRate = 1;
		//						GameMethods::Spell_C_GetSpellCooldown(spellId, false, false, &duration, &startTime, 0, 0, 0, &modRate);
		//						int CastDuration = startTime + duration - (int)LuaScript::getCurrentTime();

		//						printf("Cast Duration: %i\n", CastDuration);

		//						if (CastDuration >= 0)*/
		//					//		return;

		//		/*				if (LuaScript::ActivePlayer->GetSpellCastID() != 0)
		//							return;*/
		//							

		//						//if (cast_spell)
		//						//{
		//						//	cast_spell = false;

		//						//	if (!GameMethods::IsSpellKnown(spellId))
		//						//		return;

		//						//	int32_t spellSlot = GameMethods::FindSlotBySpellId(spellId);
		//						//	if (!spellSlot)
		//						//		return;

		//						//	//Crashes function looks fine

		//						////	GameMethods::CastSpell(spellSlot, target->GetGuid());
		//						//	printf("Casting spell %i \n", spellId);
		//						//}



		//						//if (LuaScript::ActivePlayer->GetUnitPosition().DistanceTo(target->GetUnitPosition()))
		//						//{
		//						//	Face(Range, target); // Find a alternative...
		//						//}

		//						//if (Utils::IsEntityAlive(target))
		//						//{
		//						//	target->Interact();
		//						//	printf("Looting \n");

		//						//	Settings::bot::Refresh = true;
		//						//	Sleep(6000);
		//						//}

		//					}
		//				}
		//			}
		//		}

		//	//	}
		//		__except (Utils::filterException(GetExceptionCode(), GetExceptionInformation())) {
		//			printf("[!] GrindBot Exception Caught!\n");
		//			//Settings::bot::Refresh = true;
		//		}
			}

	}
}