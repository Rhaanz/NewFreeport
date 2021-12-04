#include "../common/features.h"

#ifdef EMBPERL_XS_CLASSES

#include "../common/global_define.h"
#include "embperl.h"

#ifdef seed
#undef seed
#endif

typedef const char Const_char;

#include "npc.h"

#ifdef THIS /* this macro seems to leak out on some systems */
#undef THIS
#endif

#define VALIDATE_THIS_IS_NPC \
	do { \
		if (sv_derived_from(ST(0), "NPC")) { \
			IV tmp = SvIV((SV*)SvRV(ST(0))); \
			THIS = INT2PTR(NPC*, tmp); \
		} else { \
			Perl_croak(aTHX_ "THIS is not of type NPC"); \
		} \
		if (THIS == nullptr) { \
			Perl_croak(aTHX_ "THIS is nullptr, avoiding crash."); \
		} \
	} while (0);

XS(XS_NPC_SignalNPC); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SignalNPC) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SignalNPC(THIS, int signal_id)"); // @categories Script Utility
	{
		NPC *THIS;
		int _signal_id = (int) SvIV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SignalNPC(_signal_id);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_CheckNPCFactionAlly); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_CheckNPCFactionAlly) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::CheckNPCFactionAlly(THIS, int32 faction_id)"); // @categories Faction
	{
		NPC           *THIS;
		FACTION_VALUE RETVAL;
		dXSTARG;
		int32         other_faction = (int32) SvIV(ST(1));
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->CheckNPCFactionAlly(other_faction);
		XSprePUSH;
		PUSHi((IV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_AddItem); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_AddItem) {
	dXSARGS;
	if (items < 2 || items > 10)
		Perl_croak(aTHX_ "Usage: NPC::AddItem(THIS, uint32 item_id, [uint16 charges = 0], [bool equip_item = true], [uint32 aug1 = 0], [uint32 aug2 = 0], [uint32 aug3 = 0], [uint32 aug4 = 0], [uint32 aug5 = 0], [uint32 aug6 = 0])"); // @categories Inventory and Items
	{
		NPC    *THIS;
		uint32 itemid    = (uint32) SvUV(ST(1));
		uint16 charges   = 0;
		bool   equipitem = true;
		uint32 aug1      = 0;
		uint32 aug2      = 0;
		uint32 aug3      = 0;
		uint32 aug4      = 0;
		uint32 aug5      = 0;
		uint32 aug6      = 0;
		VALIDATE_THIS_IS_NPC;
		if (items > 2)
			charges   = (uint16) SvUV(ST(2));
		if (items > 3)
			equipitem = (bool) SvTRUE(ST(3));
		if (items > 4)
			aug1      = (uint32) SvUV(ST(4));
		if (items > 5)
			aug2      = (uint32) SvUV(ST(5));
		if (items > 6)
			aug3      = (uint32) SvUV(ST(6));
		if (items > 7)
			aug4      = (uint32) SvUV(ST(7));
		if (items > 8)
			aug5      = (uint32) SvUV(ST(8));
		if (items > 9)
			aug6      = (uint32) SvUV(ST(9));

		THIS->AddItem(itemid, charges, equipitem, aug1, aug2, aug3, aug4, aug5, aug6);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_AddLootTable); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_AddLootTable) {
	dXSARGS;
	if (items < 1)
		Perl_croak(aTHX_ "Usage: NPC::AddLootTable(THIS, [uint32 loottable_id])"); // @categories Inventory and Items
	{
		NPC *THIS;
		VALIDATE_THIS_IS_NPC;
		uint32 loottable_id = 0;

		if (items > 1) {
			loottable_id = (uint32) SvUV(ST(1));
			THIS->AddLootTable(loottable_id);
		} else {
			THIS->AddLootTable();
		}
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_RemoveItem); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_RemoveItem) {
	dXSARGS;
	if (items < 2 || items > 4)
		Perl_croak(aTHX_ "Usage: NPC::RemoveItem(THIS, uint32 item_id, [uint16 quantity = 0], [uint16 slot_id = 0])"); // @categories Inventory and Items
	{
		NPC    *THIS;
		uint32 item_id = (uint32) SvUV(ST(1));
		uint16 quantity;
		uint16 slot;
		VALIDATE_THIS_IS_NPC;
		if (items < 3)
			quantity = 0;
		else {
			quantity = (uint16) SvUV(ST(2));
		}

		if (items < 4)
			slot = 0;
		else {
			slot = (uint16) SvUV(ST(3));
		}

		THIS->RemoveItem(item_id, quantity, slot);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_ClearItemList); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_ClearItemList) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::ClearItemList(THIS)"); // @categories Inventory and Items
	{
		NPC *THIS;
		VALIDATE_THIS_IS_NPC;
		THIS->ClearItemList();
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_AddCash); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_AddCash) {
	dXSARGS;
	if (items != 5)
		Perl_croak(aTHX_ "Usage: NPC::AddCash(THIS, uint16 copper, uint16 silver, uint16 gold, uint16 platinum)"); // @categories Currency and Points
	{
		NPC    *THIS;
		uint16 in_copper   = (uint16) SvUV(ST(1));
		uint16 in_silver   = (uint16) SvUV(ST(2));
		uint16 in_gold     = (uint16) SvUV(ST(3));
		uint16 in_platinum = (uint16) SvUV(ST(4));
		VALIDATE_THIS_IS_NPC;
		THIS->AddCash(in_copper, in_silver, in_gold, in_platinum);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_RemoveCash); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_RemoveCash) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::RemoveCash(THIS)"); // @categories Currency and Points
	{
		NPC *THIS;
		VALIDATE_THIS_IS_NPC;
		THIS->RemoveCash();
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_CountLoot); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_CountLoot) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::CountLoot(THIS)"); // @categories Inventory and Items
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->CountLoot();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetLoottableID); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetLoottableID) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetLoottableID(THIS)"); // @categories Stats and Attributes
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetLoottableID();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetCopper); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetCopper) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetCopper(THIS)"); // @categories Currency and Points
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetCopper();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetSilver); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSilver) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSilver(THIS)"); // @categories Currency and Points
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSilver();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetGold); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetGold) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetGold(THIS)"); // @categories Currency and Points
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetGold();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetPlatinum); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetPlatinum) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetPlatinum(THIS)"); // @categories Currency and Points
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetPlatinum();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_SetCopper); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetCopper) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetCopper(THIS, uint32 copper_amount)"); // @categories Currency and Points
	{
		NPC    *THIS;
		uint32 amt = (uint32) SvUV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetCopper(amt);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_SetSilver); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetSilver) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetSilver(THIS, uint32 silver_amount)"); // @categories Currency and Points
	{
		NPC    *THIS;
		uint32 amt = (uint32) SvUV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetSilver(amt);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_SetGold); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetGold) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetGold(THIS, uint32 gold_amount)"); // @categories Currency and Points
	{
		NPC    *THIS;
		uint32 amt = (uint32) SvUV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetGold(amt);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_SetPlatinum); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetPlatinum) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetPlatinum(THIS, uint32 platinum_amount)"); // @categories Currency and Points
	{
		NPC    *THIS;
		uint32 amt = (uint32) SvUV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetPlatinum(amt);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_SetGrid); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetGrid) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetGrid(THIS, int32 grid_id)"); // @categories Script Utility
	{
		NPC   *THIS;
		int32 grid_ = (int32) SvIV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetGrid(grid_);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_SetSaveWaypoint); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetSaveWaypoint) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetSaveWaypoint(THIS, uint16 waypoint)"); // @categories Script Utility
	{
		NPC    *THIS;
		uint16 waypoint = (uint16) SvUV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetSaveWaypoint(waypoint);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_SetSp2); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetSp2) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetSp2(THIS, uint32 set_spawn_group_id)"); // @categories Spawns
	{
		NPC    *THIS;
		uint32 sg2 = (uint32) SvUV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetSpawnGroupId(sg2);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_GetWaypointMax); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetWaypointMax) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetWaypointMax(THIS)"); // @categories Script Utility
	{
		NPC    *THIS;
		uint16 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetWaypointMax();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetGrid); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetGrid) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetGrid(THIS)"); // @categories Script Utility, Spawns
	{
		NPC   *THIS;
		int32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetGrid();
		XSprePUSH;
		PUSHi((IV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetSp2); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSp2) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSp2(THIS)"); // @categories Spawns
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSpawnGroupId();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetNPCFactionID); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetNPCFactionID) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetNPCFactionID(THIS)"); // @categories Faction, Stats and Attributes
	{
		NPC   *THIS;
		int32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetNPCFactionID();
		XSprePUSH;
		PUSHi((IV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetPrimaryFaction); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetPrimaryFaction) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetPrimaryFaction(THIS)"); // @categories Faction, Stats and Attributes
	{
		NPC   *THIS;
		int32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetPrimaryFaction();
		XSprePUSH;
		PUSHi((IV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetNPCHate); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetNPCHate) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::GetNPCHate(THIS, Mob* entity)"); // @categories Hate and Aggro
	{
		NPC   *THIS;
		int32 RETVAL;
		dXSTARG;
		Mob   *in_ent;
		VALIDATE_THIS_IS_NPC;
		if (sv_derived_from(ST(1), "Mob")) {
			IV tmp = SvIV((SV *) SvRV(ST(1)));
			in_ent = INT2PTR(Mob *, tmp);
		} else
			Perl_croak(aTHX_ "in_ent is not of type Mob");
		if (in_ent == nullptr)
			Perl_croak(aTHX_ "in_ent is nullptr, avoiding crash.");

		RETVAL = THIS->GetNPCHate(in_ent);
		XSprePUSH;
		PUSHi((IV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_IsOnHatelist); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_IsOnHatelist) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::IsOnHatelist(THIS, Mob* target)"); // @categories Hate and Aggro
	{
		NPC  *THIS;
		bool RETVAL;
		Mob  *p;
		VALIDATE_THIS_IS_NPC;
		if (sv_derived_from(ST(1), "Mob")) {
			IV tmp = SvIV((SV *) SvRV(ST(1)));
			p = INT2PTR(Mob *, tmp);
		} else
			Perl_croak(aTHX_ "p is not of type Mob");
		if (p == nullptr)
			Perl_croak(aTHX_ "p is nullptr, avoiding crash.");

		RETVAL = THIS->IsOnHatelist(p);
		ST(0) = boolSV(RETVAL);
		sv_2mortal(ST(0));
	}
	XSRETURN(1);
}

XS(XS_NPC_RemoveFromHateList); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_RemoveFromHateList) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::RemoveFromHateList(THIS, Mob* target)"); // @categories Hate and Aggro
	{
		NPC *THIS;
		Mob *ent;
		VALIDATE_THIS_IS_NPC;
		if (sv_derived_from(ST(1), "Mob")) {
			IV tmp = SvIV((SV *) SvRV(ST(1)));
			ent = INT2PTR(Mob *, tmp);
		} else
			Perl_croak(aTHX_ "ent  is not of type Mob");
		if (ent == nullptr)
			Perl_croak(aTHX_ "ent  is nullptr, avoiding crash.");

		THIS->RemoveFromHateList(ent);

	}
	XSRETURN_EMPTY;
}


XS(XS_NPC_SetNPCFactionID); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetNPCFactionID) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetNPCFactionID(THIS, int32 faction_id)"); // @categories Faction
	{
		NPC   *THIS;
		int32 in = (int32) SvIV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetNPCFactionID(in);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_GetMaxDMG); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetMaxDMG) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetMaxDMG(THIS)"); // @categories Stats and Attributes
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetMaxDMG();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetMinDMG); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetMinDMG) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetMinDMG(THIS)");
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetMinDMG();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}


XS(XS_NPC_IsAnimal); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_IsAnimal) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::IsAnimal(THIS)"); // @categories Stats and Attributes
	{
		NPC  *THIS;
		bool RETVAL;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->IsAnimal();
		ST(0) = boolSV(RETVAL);
		sv_2mortal(ST(0));
	}
	XSRETURN(1);
}

XS(XS_NPC_GetPetSpellID); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetPetSpellID) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetPetSpellID(THIS)"); // @categories Stats and Attributes, Pet
	{
		NPC    *THIS;
		uint16 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetPetSpellID();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_SetPetSpellID); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetPetSpellID) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetPetSpellID(THIS, uint16 amount)"); // @categories Pet
	{
		NPC    *THIS;
		uint16 amt = (uint16) SvUV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetPetSpellID(amt);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_GetMaxDamage); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetMaxDamage) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::GetMaxDamage(THIS, uint8 target_level)"); // @categories Stats and Attributes
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		uint8  tlevel = (uint8) SvUV(ST(1));
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetMaxDamage(tlevel);
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_SetTaunting); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetTaunting) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetTaunting(THIS, bool toggle)"); // @categories Script Utility
	{
		NPC  *THIS;
		bool toggle = (bool) SvTRUE(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetTaunting(toggle);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_IsTaunting); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_IsTaunting) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::IsTaunting(THIS)");
	{
		NPC  *THIS;
		bool RETVAL;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->IsTaunting();
		ST(0) = boolSV(RETVAL);
		sv_2mortal(ST(0));
	}
	XSRETURN(1);
}

XS(XS_NPC_PickPocket); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_PickPocket) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::PickPocket(THIS, Client* thief)"); // @categories Skills and Recipes
	{
		NPC    *THIS;
		Client *thief;
		VALIDATE_THIS_IS_NPC;
		if (sv_derived_from(ST(1), "Client")) {
			IV tmp = SvIV((SV *) SvRV(ST(1)));
			thief = INT2PTR(Client *, tmp);
		} else
			Perl_croak(aTHX_ "thief is not of type Client");
		if (thief == nullptr)
			Perl_croak(aTHX_ "thief is nullptr, avoiding crash.");

		THIS->PickPocket(thief);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_StartSwarmTimer); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_StartSwarmTimer) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::StartSwarmTimer(THIS, uint32 duration)"); // @categories Script Utility, Pet
	{
		NPC    *THIS;
		uint32 duration = (uint32) SvUV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->StartSwarmTimer(duration);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_DoClassAttacks); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_DoClassAttacks) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::DoClassAttacks(THIS, Mob* target)"); // @categories Script Utility
	{
		NPC *THIS;
		Mob *target;
		VALIDATE_THIS_IS_NPC;
		if (sv_derived_from(ST(1), "Mob")) {
			IV tmp = SvIV((SV *) SvRV(ST(1)));
			target = INT2PTR(Mob *, tmp);
		} else
			Perl_croak(aTHX_ "target is not of type Mob");
		if (target == nullptr)
			Perl_croak(aTHX_ "target is nullptr, avoiding crash.");

		THIS->DoClassAttacks(target);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_GetMaxWp); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetMaxWp) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetMaxWp(THIS)");
	{
		NPC *THIS;
		int RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetMaxWp();
		XSprePUSH;
		PUSHi((IV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_DisplayWaypointInfo); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_DisplayWaypointInfo) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::DisplayWaypointInfo(THIS, Client* target)"); // @categories Script Utility
	{
		NPC    *THIS;
		Client *to;
		VALIDATE_THIS_IS_NPC;
		if (sv_derived_from(ST(1), "Client")) {
			IV tmp = SvIV((SV *) SvRV(ST(1)));
			to = INT2PTR(Client *, tmp);
		} else
			Perl_croak(aTHX_ "to is not of type Client");
		if (to == nullptr)
			Perl_croak(aTHX_ "to is nullptr, avoiding crash.");

		THIS->DisplayWaypointInfo(to);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_CalculateNewWaypoint); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_CalculateNewWaypoint) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::CalculateNewWaypoint(THIS)"); // @categories Script Utility
	{
		NPC *THIS;
		VALIDATE_THIS_IS_NPC;
		THIS->CalculateNewWaypoint();
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_AssignWaypoints); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_AssignWaypoints) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::AssignWaypoints(THIS, uint32 grid_id)"); // @categories Script Utility
	{
		NPC    *THIS;
		uint32 grid = (uint32) SvUV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->AssignWaypoints(grid);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_SetWaypointPause); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetWaypointPause) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::SetWaypointPause(THIS)"); // @categories Script Utility
	{
		NPC *THIS;
		VALIDATE_THIS_IS_NPC;
		THIS->SetWaypointPause();
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_UpdateWaypoint); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_UpdateWaypoint) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::UpdateWaypoint(THIS, int wp_index)"); // @categories Script Utility
	{
		NPC *THIS;
		int wp_index = (int) SvIV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->UpdateWaypoint(wp_index);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_StopWandering); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_StopWandering) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::StopWandering(THIS)"); // @categories Script Utility
	{
		NPC *THIS;
		VALIDATE_THIS_IS_NPC;
		THIS->StopWandering();
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_ResumeWandering); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_ResumeWandering) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::ResumeWandering(THIS)"); // @categories Script Utility
	{
		NPC *THIS;
		VALIDATE_THIS_IS_NPC;
		THIS->ResumeWandering();
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_PauseWandering); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_PauseWandering) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::PauseWandering(THIS, int pause_time)"); // @categories Script Utility
	{
		NPC *THIS;
		int pausetime = (int) SvIV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->PauseWandering(pausetime);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_MoveTo); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_MoveTo) {
	dXSARGS;
	if (items != 4 && items != 5 && items != 6)
		Perl_croak(aTHX_ "Usage: NPC::MoveTo(THIS, float x, float y, float z, [float heading], [bool save_guard_location = false])"); // @categories Script Utility
	{
		NPC   *THIS;
		float mtx = (float) SvNV(ST(1));
		float mty = (float) SvNV(ST(2));
		float mtz = (float) SvNV(ST(3));
		float mth = 0;
		bool  saveguard = false;
		VALIDATE_THIS_IS_NPC;
		if (items > 4)
			mth = (float) SvNV(ST(4));
		if (items > 5)
			saveguard = (bool) SvTRUE(ST(5));
		auto position = glm::vec4(mtx, mty, mtz, mth);
		THIS->MoveTo(position, saveguard);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_NextGuardPosition); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_NextGuardPosition) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::NextGuardPosition(THIS)"); // @categories Script Utility
	{
		NPC *THIS;
		VALIDATE_THIS_IS_NPC;
		THIS->NextGuardPosition();
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_SaveGuardSpot); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SaveGuardSpot) {
	dXSARGS;
	if (items != 5)
		Perl_croak(aTHX_ "Usage: NPC::SaveGuardSpot(THIS, x, y, z, heading)"); // @categories Script Utility
	{
		NPC  *THIS;
		float x = (float)SvNV(ST(1));
		float y = (float)SvNV(ST(2));
		float z = (float)SvNV(ST(3));
		float heading = (float)SvNV(ST(4));
		VALIDATE_THIS_IS_NPC;
		THIS->SaveGuardSpot(glm::vec4(x, y, z, heading));
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_IsGuarding); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_IsGuarding) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::IsGuarding(THIS)"); // @categories Script Utility
	{
		NPC  *THIS;
		bool RETVAL;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->IsGuarding();
		ST(0) = boolSV(RETVAL);
		sv_2mortal(ST(0));
	}
	XSRETURN(1);
}

XS(XS_NPC_AI_SetRoambox); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_AI_SetRoambox) {
	dXSARGS;
	if (items < 6 || items > 8)
		Perl_croak(aTHX_ "Usage: NPC::AI_SetRoambox(THIS, float distance, float max_x, float min_x, float max_y, float min_y, [uint32 max_delay = 2500], [uint32 min_delay = 2500])"); // @categories Script Utility
	{
		NPC    *THIS;
		float  iDist = (float) SvNV(ST(1));
		float  iMaxX = (float) SvNV(ST(2));
		float  iMinX = (float) SvNV(ST(3));
		float  iMaxY = (float) SvNV(ST(4));
		float  iMinY = (float) SvNV(ST(5));
		uint32 iDelay;
		uint32 iMinDelay;
		VALIDATE_THIS_IS_NPC;
		if (items < 7) {
			iMinDelay = 2500;
			iDelay    = 2500;
		} else if (items < 8) {
			iMinDelay = 2500;
			iDelay    = (uint32) SvUV(ST(6));
		} else {
			iDelay    = (uint32) SvUV(ST(6));
			iMinDelay = (uint32) SvUV(ST(7));
		}

		THIS->AI_SetRoambox(iDist, iMaxX, iMinX, iMaxY, iMinY, iDelay, iMinDelay);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_GetNPCSpellsID); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetNPCSpellsID) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetNPCSpellsID(THIS)"); // @categories Stats and Attributes
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetNPCSpellsID();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetSpawnPointID); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSpawnPointID) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSpawnPointID(THIS)"); // @categories Spawns
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSpawnPointID();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetSpawnPointX); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSpawnPointX) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSpawnPointX(THIS)"); // @categories Spawns
	{
		NPC   *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSpawnPoint().x;
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetSpawnPointY); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSpawnPointY) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSpawnPointY(THIS)"); // @categories Spawns
	{
		NPC   *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSpawnPoint().y;
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetSpawnPointZ); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSpawnPointZ) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSpawnPointZ(THIS)"); // @categories Spawns
	{
		NPC   *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSpawnPoint().z;
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetSpawnPointH); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSpawnPointH) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSpawnPointH(THIS)"); // @categories Spawns
	{
		NPC   *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSpawnPoint().w;
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetGuardPointX); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetGuardPointX) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetGuardPointX(THIS)"); // @categories Script Utility, Spawns
	{
		NPC   *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetGuardPoint().x;
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetGuardPointY); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetGuardPointY) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetGuardPointY(THIS)"); // @categories Script Utility, Spawns
	{
		NPC   *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetGuardPoint().y;
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetGuardPointZ); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetGuardPointZ) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetGuardPointZ(THIS)"); // @categories Script Utility, Spawns
	{
		NPC   *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetGuardPoint().z;
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_SetPrimSkill); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetPrimSkill) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetPrimSkill(THIS, int skill_id)"); // @categories Stats and Attributes
	{
		NPC *THIS;
		int skill_id = (int) SvIV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetPrimSkill(skill_id);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_SetSecSkill); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetSecSkill) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetSecSkill(THIS, int skill_id)"); // @categories Stats and Attributes
	{
		NPC *THIS;
		int skill_id = (int) SvIV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetSecSkill(skill_id);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_GetPrimSkill); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetPrimSkill) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetPrimSkill(THIS)"); // @categories Stats and Attributes
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetPrimSkill();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetSecSkill); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSecSkill) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSecSkill(THIS)"); // @categories Stats and Attributes
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSecSkill();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetSwarmOwner); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSwarmOwner) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSwarmOwner(THIS)"); // @categories Pet
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSwarmOwner();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetSwarmTarget); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSwarmTarget) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSwarmTarget(THIS)"); // @categories Pet
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSwarmTarget();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_SetSwarmTarget); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetSwarmTarget) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetSwarmTarget(THIS, int target_id)"); // @categories Pet
	{
		NPC *THIS;
		int target_id = (int) SvIV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetSwarmTarget(target_id);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_ModifyNPCStat); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_ModifyNPCStat) {
	dXSARGS;
	if (items != 3)
		Perl_croak(aTHX_ "Usage: NPC::ModifyNPCStat(THIS, string key, string value)"); // @categories Stats and Attributes
	{
		NPC        *THIS;
		Const_char *identifier = (Const_char *) SvPV_nolen(ST(1));
		Const_char *newValue   = (Const_char *) SvPV_nolen(ST(2));
		VALIDATE_THIS_IS_NPC;
		THIS->ModifyNPCStat(identifier, newValue);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_AddSpellToNPCList); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_AddSpellToNPCList) {
	dXSARGS;
	if (items != 7)
		Perl_croak(aTHX_ "Usage: NPC::AddAISpell(THIS, int priority, int spell_id, int type, int mana_cost, int recast_delay, int resist_adjust)"); // @categories Spells and Disciplines, Script Utility
	{
		NPC *THIS;
		int priority      = (int) SvIV(ST(1));
		int spell_id      = (int) SvIV(ST(2));
		int type          = (int) SvIV(ST(3));
		int mana_cost     = (int) SvIV(ST(4));
		int recast_delay  = (int) SvIV(ST(5));
		int resist_adjust = (int) SvIV(ST(6));
		VALIDATE_THIS_IS_NPC;
		THIS->AddSpellToNPCList(priority, spell_id, type, mana_cost, recast_delay, resist_adjust, 0, 0);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_RemoveSpellFromNPCList); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_RemoveSpellFromNPCList) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::RemoveAISpell(THIS, int spell_id)"); // @categories Spells and Disciplines
	{
		NPC *THIS;
		int spell_id = (int) SvIV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->RemoveSpellFromNPCList(spell_id);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_SetSpellFocusDMG); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetSpellFocusDMG) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetSpellFocusDMG(THIS, int new_spell_focus_dmg)"); // @categories Stats and Attributes
	{
		NPC   *THIS;
		int32 NewSpellFocusDMG = (int32) SvIV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetSpellFocusDMG(NewSpellFocusDMG);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_GetSpellFocusDMG); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSpellFocusDMG) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSpellFocusDMG(THIS)"); // @categories Spells and Disciplines
	{
		NPC   *THIS;
		int32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSpellFocusDMG();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_SetSpellFocusHeal); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetSpellFocusHeal) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::SetSpellFocusHeal(THIS, int32 new_spell_focus_heal)"); // @categories Stats and Attributes
	{
		NPC   *THIS;
		int32 NewSpellFocusHeal = (int32) SvIV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->SetSpellFocusHeal(NewSpellFocusHeal);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_GetSpellFocusHeal); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSpellFocusHeal) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSpellFocusHeal(THIS)"); // @categories Spells and Disciplines
	{
		NPC   *THIS;
		int32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSpellFocusHeal();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetSlowMitigation); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSlowMitigation) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSlowMitigation(THIS)"); // @categories Stats and Attributes
	{
		NPC   *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSlowMitigation();
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetAttackSpeed); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetAttackSpeed) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetAttackSpeed(THIS)"); // @categories Stats and Attributes
	{
		NPC   *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetAttackSpeed();
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetAttackDelay); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetAttackDelay) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetAttackDelay(THIS)"); // @categories Stats and Attributes
	{
		NPC   *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetAttackDelay();
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetAccuracyRating); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetAccuracyRating) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetAccuracyRating(THIS)"); // @categories Stats and Attributes
	{
		NPC   *THIS;
		int32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetAccuracyRating();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetAvoidanceRating); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetAvoidanceRating) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetAvoidanceRating(THIS)"); // @categories Stats and Attributes
	{
		NPC   *THIS;
		int32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetAvoidanceRating();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetSpawnKillCount); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetSpawnKillCount) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSpawnKillCount(THIS)"); // @categories Spawns
	{
		NPC    *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetSpawnKillCount();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetScore); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetScore) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetScore(THIS)"); // @categories Script Utility
	{
		NPC *THIS;
		int RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetScore();
		XSprePUSH;
		PUSHi((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_NPC_MerchantOpenShop);
XS(XS_NPC_MerchantOpenShop) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::MerchantOpenShop(THIS)"); // @categories Script Utility
	{
		NPC *THIS;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		THIS->MerchantOpenShop();
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_MerchantCloseShop);
XS(XS_NPC_MerchantCloseShop) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::MerchantCloseShop(THIS)"); // @categories Script Utility
	{
		NPC *THIS;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		THIS->MerchantCloseShop();
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_AddMeleeProc);
XS(XS_NPC_AddMeleeProc) {
	dXSARGS;
	if (items != 3)
		Perl_croak(aTHX_ "Usage: NPC::AddMeleeProc(THIS, int spell_id, int chance)"); // @categories Script Utility
	{
		NPC *THIS;
		int spell_id = (int) SvIV(ST(1));
		int chance   = (int) SvIV(ST(2));
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		THIS->AddProcToWeapon(spell_id, true, chance);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_AddRangedProc);
XS(XS_NPC_AddRangedProc) {
	dXSARGS;
	if (items != 3)
		Perl_croak(aTHX_ "Usage: NPC::AddRangedProc(THIS, int spell_id, int chance)"); // @categories Script Utility
	{
		NPC *THIS;
		int spell_id = (int) SvIV(ST(1));
		int chance   = (int) SvIV(ST(2));
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		THIS->AddRangedProc(spell_id, chance);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_AddDefensiveProc);
XS(XS_NPC_AddDefensiveProc) {
	dXSARGS;
	if (items != 3)
		Perl_croak(aTHX_ "Usage: NPC::AddDefensiveProc(THIS, int spell_id, int chance)"); // @categories Script Utility
	{
		NPC *THIS;
		int spell_id = (int) SvIV(ST(1));
		int chance   = (int) SvIV(ST(2));
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		THIS->AddDefensiveProc(spell_id, chance);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_RemoveMeleeProc);
XS(XS_NPC_RemoveMeleeProc) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::RemoveMeleeProc(THIS, int spell_id)"); // @categories Script Utility
	{
		NPC *THIS;
		int spell_id = (int) SvIV(ST(1));
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		THIS->RemoveProcFromWeapon(spell_id, false);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_RemoveRangedProc);
XS(XS_NPC_RemoveRangedProc) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::RemoveRangedProc(THIS, int spell_id)"); // @categories Script Utility
	{
		NPC *THIS;
		int spell_id = (int) SvIV(ST(1));
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		THIS->RemoveRangedProc(spell_id, false);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_RemoveDefensiveProc);
XS(XS_NPC_RemoveDefensiveProc) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::RemoveDefensiveProc(THIS, int spell_id)"); // @categories Script Utility
	{
		NPC *THIS;
		int spell_id = (int) SvIV(ST(1));
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		THIS->RemoveDefensiveProc(spell_id, false);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_ChangeLastName); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_ChangeLastName) {
	dXSARGS;
	if (items < 1 || items > 2)
		Perl_croak(aTHX_ "Usage: NPC::ChangeLastName(THIS, string name)"); // @categories Script Utility
	{
		NPC  *THIS;
		char *name = nullptr;
		VALIDATE_THIS_IS_NPC;
		if (items > 1) { name = (char *) SvPV_nolen(ST(1)); }

		THIS->ChangeLastName(name);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_ClearLastName); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_ClearLastName) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::ClearLastName(THIS)"); // @categories Script Utility
	{
		NPC *THIS;
		VALIDATE_THIS_IS_NPC;
		THIS->ClearLastName();
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_GetCombatState); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_GetCombatState) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetCombatState(THIS)"); // @categories Script Utility
	{
		NPC  *THIS;
		bool RETVAL;
		VALIDATE_THIS_IS_NPC;
		RETVAL = THIS->GetCombatEvent();
		ST(0) = boolSV(RETVAL);
		sv_2mortal(ST(0));
	}
	XSRETURN(1);
}

XS(XS_NPC_SetSimpleRoamBox); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_SetSimpleRoamBox) {
	dXSARGS;
	if (items < 2)
		Perl_croak(aTHX_ "Usage: NPC::SetSimpleRoamBox(THIS, box_size, move_distance, move_delay)"); // @categories Script Utility
	{
		NPC *THIS;

		auto  box_size      = (float) SvNV(ST(1));
		float move_distance = 0;
		int   move_delay    = 0;

		if (items >= 3) {
			move_distance = (float) SvNV(ST(2));
		}

		if (items >= 4) {
			move_delay = (int) SvIV(ST(3));
		}
		VALIDATE_THIS_IS_NPC;
		THIS->SetSimpleRoamBox(box_size, move_distance, move_delay);
	}
	XSRETURN_EMPTY;
}


XS(XS_NPC_RecalculateSkills); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_RecalculateSkills) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::RecalculateSkills(THIS)"); // @categories Skills and Recipes
	{
		NPC    *THIS;
		VALIDATE_THIS_IS_NPC;
		THIS->RecalculateSkills();
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_ScaleNPC); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_ScaleNPC) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::ScaleNPC(THIS, uint8 npc_level)");
	{
		NPC *THIS;
		uint8 npc_level = (uint8) SvUV(ST(1));
		VALIDATE_THIS_IS_NPC;
		THIS->ScaleNPC(npc_level);
	}
	XSRETURN_EMPTY;
}

XS(XS_NPC_IsRaidTarget); /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_IsRaidTarget) {	
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::IsRaidTarget(THIS)"); // @categories Stats and Attributes
	{
		NPC  *THIS;
		bool is_raid_target;
		VALIDATE_THIS_IS_NPC;
		is_raid_target = THIS->IsRaidTarget();
		ST(0) = boolSV(is_raid_target);
		sv_2mortal(ST(0));
	}
	XSRETURN(1);
}

XS(XS_NPC_HasItem);  /* prototype to pass -Wmissing-prototypes */
XS(XS_NPC_HasItem) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::HasItem(THIS, uint32 item_id)"); // @categories Script Utility
	{
		NPC *THIS;
		bool has_item = false;
		uint32 item_id = (uint32) SvUV(ST(1));
		VALIDATE_THIS_IS_NPC;
		has_item = THIS->HasItem(item_id);
		ST(0) = boolSV(has_item);
		sv_2mortal(ST(0));
	}
	XSRETURN(1);
}

XS(XS_NPC_CountItem);
XS(XS_NPC_CountItem) {	
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::CountItem(THIS, uint32 item_id)"); // @categories Script Utility
	{
		NPC *THIS;
		uint16 item_count = 0;
		uint32 item_id = (uint32) SvUV(ST(1));
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		item_count = THIS->CountItem(item_id);
		XSprePUSH;
		PUSHu((UV) item_count);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetItemIDBySlot);
XS(XS_NPC_GetItemIDBySlot) {	
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::GetItemIDBySlot(THIS, uint16 loot_slot)"); // @categories Script Utility
	{
		NPC *THIS;
		uint32 item_id = 0;
		uint16 loot_slot = (uint16) SvUV(ST(1));
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		item_id = THIS->GetItemIDBySlot(loot_slot);
		XSprePUSH;
		PUSHu((UV) item_id);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetFirstSlotByItemID);
XS(XS_NPC_GetFirstSlotByItemID) {	
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: NPC::GetFirstSlotByItemID(THIS, uint32 item_id)"); // @categories Script Utility
	{
		NPC *THIS;
		uint16 loot_slot = 0;
		uint32 item_id = (uint32) SvUV(ST(1));
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		loot_slot = THIS->GetFirstSlotByItemID(item_id);
		XSprePUSH;
		PUSHu((UV) loot_slot);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetHealScale);
XS(XS_NPC_GetHealScale) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetHealScale(THIS)");  // @categories Stats and Attributes
	{
		NPC *THIS;
		float healscale;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		healscale = THIS->GetHealScale();
		XSprePUSH;
		PUSHn((double) healscale);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetSpellScale);
XS(XS_NPC_GetSpellScale) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetSpellScale(THIS)");  // @categories Stats and Attributes
	{
		NPC *THIS;
		float spellscale;
		dXSTARG;
		VALIDATE_THIS_IS_NPC;
		spellscale = THIS->GetSpellScale();
		XSprePUSH;
		PUSHn((double) spellscale);
	}
	XSRETURN(1);
}

XS(XS_NPC_GetLootList);
XS(XS_NPC_GetLootList) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: NPC::GetLootList(THIS)"); // @categories Script Utility
	{
		NPC *THIS;
		VALIDATE_THIS_IS_NPC;
		auto npc_items = THIS->GetLootList();
		auto item_count = npc_items.size();
		if (item_count > 0) {
			EXTEND(sp, item_count);
			for (int index = 0; index < item_count; ++index) {
				ST(index) = sv_2mortal(newSVuv(npc_items[index]));
			}
			XSRETURN(item_count);
		}
		SV* return_value = &PL_sv_undef;
		ST(0) = return_value;
		XSRETURN(1);
	}
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_NPC); /* prototype to pass -Wmissing-prototypes */
XS(boot_NPC) {
	dXSARGS;
	char file[256];
	strncpy(file, __FILE__, 256);
	file[255] = 0;

	if (items != 1)
		fprintf(stderr, "boot_quest does not take any arguments.");
	char buf[128];

	//add the strcpy stuff to get rid of const warnings....

	XS_VERSION_BOOTCHECK;
	newXSproto(strcpy(buf, "AI_SetRoambox"), XS_NPC_AI_SetRoambox, file, "$$$$$$;$$");
	newXSproto(strcpy(buf, "AddAISpell"), XS_NPC_AddSpellToNPCList, file, "$$$$$$$");
	newXSproto(strcpy(buf, "AddCash"), XS_NPC_AddCash, file, "$$$$$");
	newXSproto(strcpy(buf, "AddDefensiveProc"), XS_NPC_AddDefensiveProc, file, "$$$");
	newXSproto(strcpy(buf, "AddItem"), XS_NPC_AddItem, file, "$$;$$$$$$$$");
	newXSproto(strcpy(buf, "AddLootTable"), XS_NPC_AddLootTable, file, "$");
	newXSproto(strcpy(buf, "AddMeleeProc"), XS_NPC_AddMeleeProc, file, "$$$");
	newXSproto(strcpy(buf, "AddRangedProc"), XS_NPC_AddRangedProc, file, "$$$");
	newXSproto(strcpy(buf, "AssignWaypoints"), XS_NPC_AssignWaypoints, file, "$$");
	newXSproto(strcpy(buf, "CalculateNewWaypoint"), XS_NPC_CalculateNewWaypoint, file, "$");
	newXSproto(strcpy(buf, "ChangeLastName"), XS_NPC_ChangeLastName, file, "$:$");
	newXSproto(strcpy(buf, "CheckNPCFactionAlly"), XS_NPC_CheckNPCFactionAlly, file, "$$");
	newXSproto(strcpy(buf, "ClearItemList"), XS_NPC_ClearItemList, file, "$");
	newXSproto(strcpy(buf, "ClearLastName"), XS_NPC_ClearLastName, file, "$");
	newXSproto(strcpy(buf, "CountItem"), XS_NPC_CountItem, file, "$$");
	newXSproto(strcpy(buf, "CountLoot"), XS_NPC_CountLoot, file, "$");
	newXSproto(strcpy(buf, "DisplayWaypointInfo"), XS_NPC_DisplayWaypointInfo, file, "$$");
	newXSproto(strcpy(buf, "DoClassAttacks"), XS_NPC_DoClassAttacks, file, "$$");
	newXSproto(strcpy(buf, "GetAccuracyRating"), XS_NPC_GetAccuracyRating, file, "$");
	newXSproto(strcpy(buf, "GetAttackDelay"), XS_NPC_GetAttackDelay, file, "$");
	newXSproto(strcpy(buf, "GetAttackSpeed"), XS_NPC_GetAttackSpeed, file, "$");
	newXSproto(strcpy(buf, "GetAvoidanceRating"), XS_NPC_GetAvoidanceRating, file, "$");
	newXSproto(strcpy(buf, "GetCombatState"), XS_NPC_GetCombatState, file, "$");
	newXSproto(strcpy(buf, "GetCopper"), XS_NPC_GetCopper, file, "$");
	newXSproto(strcpy(buf, "GetFirstSlotByItemID"), XS_NPC_GetFirstSlotByItemID, file, "$$");
	newXSproto(strcpy(buf, "GetGold"), XS_NPC_GetGold, file, "$");
	newXSproto(strcpy(buf, "GetGrid"), XS_NPC_GetGrid, file, "$");
	newXSproto(strcpy(buf, "GetGuardPointX"), XS_NPC_GetGuardPointX, file, "$");
	newXSproto(strcpy(buf, "GetGuardPointY"), XS_NPC_GetGuardPointY, file, "$");
	newXSproto(strcpy(buf, "GetGuardPointZ"), XS_NPC_GetGuardPointZ, file, "$");
	newXSproto(strcpy(buf, "GetHealScale"), XS_NPC_GetHealScale, file, "$");
	newXSproto(strcpy(buf, "GetItemIDBySlot"), XS_NPC_GetItemIDBySlot, file, "$$");
	newXSproto(strcpy(buf, "GetLootList"), XS_NPC_GetLootList, file, "$");
	newXSproto(strcpy(buf, "GetLoottableID"), XS_NPC_GetLoottableID, file, "$");
	newXSproto(strcpy(buf, "GetMaxDMG"), XS_NPC_GetMaxDMG, file, "$");
	newXSproto(strcpy(buf, "GetMaxDamage"), XS_NPC_GetMaxDamage, file, "$$");
	newXSproto(strcpy(buf, "GetMaxWp"), XS_NPC_GetMaxWp, file, "$");
	newXSproto(strcpy(buf, "GetMinDMG"), XS_NPC_GetMinDMG, file, "$");
	newXSproto(strcpy(buf, "GetNPCFactionID"), XS_NPC_GetNPCFactionID, file, "$");
	newXSproto(strcpy(buf, "GetNPCHate"), XS_NPC_GetNPCHate, file, "$$");
	newXSproto(strcpy(buf, "GetNPCSpellsID"), XS_NPC_GetNPCSpellsID, file, "$");
	newXSproto(strcpy(buf, "GetPetSpellID"), XS_NPC_GetPetSpellID, file, "$");
	newXSproto(strcpy(buf, "GetPlatinum"), XS_NPC_GetPlatinum, file, "$");
	newXSproto(strcpy(buf, "GetPrimSkill"), XS_NPC_GetPrimSkill, file, "$");
	newXSproto(strcpy(buf, "GetPrimaryFaction"), XS_NPC_GetPrimaryFaction, file, "$");
	newXSproto(strcpy(buf, "GetScore"), XS_NPC_GetScore, file, "$");
	newXSproto(strcpy(buf, "GetSecSkill"), XS_NPC_GetSecSkill, file, "$");
	newXSproto(strcpy(buf, "GetSilver"), XS_NPC_GetSilver, file, "$");
	newXSproto(strcpy(buf, "GetSlowMitigation"), XS_NPC_GetSlowMitigation, file, "$");
	newXSproto(strcpy(buf, "GetSp2"), XS_NPC_GetSp2, file, "$");
	newXSproto(strcpy(buf, "GetSpawnKillCount"), XS_NPC_GetSpawnKillCount, file, "$");
	newXSproto(strcpy(buf, "GetSpawnPointH"), XS_NPC_GetSpawnPointH, file, "$");
	newXSproto(strcpy(buf, "GetSpawnPointID"), XS_NPC_GetSpawnPointID, file, "$");
	newXSproto(strcpy(buf, "GetSpawnPointX"), XS_NPC_GetSpawnPointX, file, "$");
	newXSproto(strcpy(buf, "GetSpawnPointY"), XS_NPC_GetSpawnPointY, file, "$");
	newXSproto(strcpy(buf, "GetSpawnPointZ"), XS_NPC_GetSpawnPointZ, file, "$");
	newXSproto(strcpy(buf, "GetSpellFocusDMG"), XS_NPC_GetSpellFocusDMG, file, "$");
	newXSproto(strcpy(buf, "GetSpellFocusHeal"), XS_NPC_GetSpellFocusHeal, file, "$");
	newXSproto(strcpy(buf, "GetSpellScale"), XS_NPC_GetSpellScale, file, "$");
	newXSproto(strcpy(buf, "GetSwarmOwner"), XS_NPC_GetSwarmOwner, file, "$");
	newXSproto(strcpy(buf, "GetSwarmTarget"), XS_NPC_GetSwarmTarget, file, "$");
	newXSproto(strcpy(buf, "GetWaypointMax"), XS_NPC_GetWaypointMax, file, "$");
	newXSproto(strcpy(buf, "HasItem"), XS_NPC_HasItem, file, "$$");
	newXSproto(strcpy(buf, "IsAnimal"), XS_NPC_IsAnimal, file, "$");
	newXSproto(strcpy(buf, "IsGuarding"), XS_NPC_IsGuarding, file, "$");
	newXSproto(strcpy(buf, "IsOnHatelist"), XS_NPC_IsOnHatelist, file, "$$");
	newXSproto(strcpy(buf, "IsRaidTarget"), XS_NPC_IsRaidTarget, file, "$");
	newXSproto(strcpy(buf, "IsTaunting"), XS_NPC_IsTaunting, file, "$");
	newXSproto(strcpy(buf, "MerchantCloseShop"), XS_NPC_MerchantCloseShop, file, "$");
	newXSproto(strcpy(buf, "MerchantOpenShop"), XS_NPC_MerchantOpenShop, file, "$");
	newXSproto(strcpy(buf, "ModifyNPCStat"), XS_NPC_ModifyNPCStat, file, "$$$");
	newXSproto(strcpy(buf, "MoveTo"), XS_NPC_MoveTo, file, "$$$$");
	newXSproto(strcpy(buf, "NextGuardPosition"), XS_NPC_NextGuardPosition, file, "$");
	newXSproto(strcpy(buf, "PauseWandering"), XS_NPC_PauseWandering, file, "$$");
	newXSproto(strcpy(buf, "PickPocket"), XS_NPC_PickPocket, file, "$$");
	newXSproto(strcpy(buf, "RecalculateSkills"), XS_NPC_RecalculateSkills, file, "$");
	newXSproto(strcpy(buf, "RemoveAISpell"), XS_NPC_RemoveSpellFromNPCList, file, "$$");
	newXSproto(strcpy(buf, "RemoveCash"), XS_NPC_RemoveCash, file, "$");
	newXSproto(strcpy(buf, "RemoveDefensiveProc"), XS_NPC_RemoveDefensiveProc, file, "$$");
	newXSproto(strcpy(buf, "RemoveFromHateList"), XS_NPC_RemoveFromHateList, file, "$$");
	newXSproto(strcpy(buf, "RemoveItem"), XS_NPC_RemoveItem, file, "$$;$$");
	newXSproto(strcpy(buf, "RemoveMeleeProc"), XS_NPC_RemoveMeleeProc, file, "$$");
	newXSproto(strcpy(buf, "RemoveRangedProc"), XS_NPC_RemoveRangedProc, file, "$$");
	newXSproto(strcpy(buf, "ResumeWandering"), XS_NPC_ResumeWandering, file, "$");
	newXSproto(strcpy(buf, "SaveGuardSpot"), XS_NPC_SaveGuardSpot, file, "$$$$$");
	newXSproto(strcpy(buf, "ScaleNPC"), XS_NPC_ScaleNPC, file, "$$");
	newXSproto(strcpy(buf, "SetCopper"), XS_NPC_SetCopper, file, "$$");
	newXSproto(strcpy(buf, "SetGold"), XS_NPC_SetGold, file, "$$");
	newXSproto(strcpy(buf, "SetGrid"), XS_NPC_SetGrid, file, "$$");
	newXSproto(strcpy(buf, "SetNPCFactionID"), XS_NPC_SetNPCFactionID, file, "$$");
	newXSproto(strcpy(buf, "SetPetSpellID"), XS_NPC_SetPetSpellID, file, "$$");
	newXSproto(strcpy(buf, "SetPlatinum"), XS_NPC_SetPlatinum, file, "$$");
	newXSproto(strcpy(buf, "SetPrimSkill"), XS_NPC_SetPrimSkill, file, "$$");
	newXSproto(strcpy(buf, "SetSaveWaypoint"), XS_NPC_SetSaveWaypoint, file, "$$");
	newXSproto(strcpy(buf, "SetSecSkill"), XS_NPC_SetSecSkill, file, "$$");
	newXSproto(strcpy(buf, "SetSilver"), XS_NPC_SetSilver, file, "$$");
	newXSproto(strcpy(buf, "SetSimpleRoamBox"), XS_NPC_SetSimpleRoamBox, file, "$$;$$");
	newXSproto(strcpy(buf, "SetSp2"), XS_NPC_SetSp2, file, "$$");
	newXSproto(strcpy(buf, "SetSpellFocusDMG"), XS_NPC_SetSpellFocusDMG, file, "$$");
	newXSproto(strcpy(buf, "SetSpellFocusHeal"), XS_NPC_SetSpellFocusHeal, file, "$$");
	newXSproto(strcpy(buf, "SetSwarmTarget"), XS_NPC_SetSwarmTarget, file, "$$");
	newXSproto(strcpy(buf, "SetTaunting"), XS_NPC_SetTaunting, file, "$$");
	newXSproto(strcpy(buf, "SetWaypointPause"), XS_NPC_SetWaypointPause, file, "$");
	newXSproto(strcpy(buf, "SignalNPC"), XS_NPC_SignalNPC, file, "$$");
	newXSproto(strcpy(buf, "StartSwarmTimer"), XS_NPC_StartSwarmTimer, file, "$$");
	newXSproto(strcpy(buf, "StopWandering"), XS_NPC_StopWandering, file, "$");
	newXSproto(strcpy(buf, "UpdateWaypoint"), XS_NPC_UpdateWaypoint, file, "$$");
	XSRETURN_YES;
}

#endif //EMBPERL_XS_CLASSES

