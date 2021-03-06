#include "../common/features.h"

#ifdef EMBPERL_XS_CLASSES

#include "../common/global_define.h"
#include "embperl.h"

#ifdef seed
#undef seed
#endif

#include "doors.h"

#ifdef THIS /* this macro seems to leak out on some systems */
#undef THIS
#endif

#define VALIDATE_THIS_IS_DOOR \
	do { \
		if (sv_derived_from(ST(0), "Doors")) { \
			IV tmp = SvIV((SV*)SvRV(ST(0))); \
			THIS = INT2PTR(Doors*, tmp); \
		} else { \
			Perl_croak(aTHX_ "THIS is not of type Doors"); \
		} \
		if (THIS == nullptr) { \
			Perl_croak(aTHX_ "THIS is nullptr, avoiding crash."); \
		} \
	} while (0);

XS(XS_Doors_GetDoorDBID); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetDoorDBID) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetDoorDBID(THIS)"); // @categories Doors
	{
		Doors *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_DOOR;
		RETVAL = THIS->GetDoorDBID();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetDoorID); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetDoorID) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetDoorID(THIS)"); // @categories Doors
	{
		Doors *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_DOOR;
		RETVAL = THIS->GetDoorID();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetID); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetID) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetID(THIS)"); // @categories Doors
	{
		Doors *THIS;
		uint16 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_DOOR;
		RETVAL = THIS->GetEntityID();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetX); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetX) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetX(THIS)"); // @categories Doors
	{
		Doors *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_DOOR;
		RETVAL = THIS->GetPosition().x;
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetY); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetY) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetY(THIS)"); // @categories Doors
	{
		Doors *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_DOOR;
		RETVAL = THIS->GetPosition().y;
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetZ); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetZ) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetZ(THIS)"); // @categories Doors
	{
		Doors *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_DOOR;
		RETVAL = THIS->GetPosition().z;
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetHeading); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetHeading) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetHeading(THIS)"); // @categories Doors
	{
		Doors *THIS;
		float RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_DOOR;
		RETVAL = THIS->GetPosition().w;
		XSprePUSH;
		PUSHn((double) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetOpenType); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetOpenType) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetOpenType(THIS)"); // @categories Doors
	{
		Doors *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_DOOR;
		RETVAL = THIS->GetOpenType();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetLockpick); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetLockpick) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetLockpick(THIS)"); // @categories Doors, Skills and Recipes
	{
		Doors *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_DOOR;
		RETVAL = THIS->GetLockpick();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetKeyItem); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetKeyItem) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetKeyItem(THIS)"); // @categories Doors
	{
		Doors *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_DOOR;
		RETVAL = THIS->GetKeyItem();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetNoKeyring); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetNoKeyring) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::GetNoKeyring(THIS, uint8 type)"); // @categories Doors
	{
		Doors *THIS;
		uint8 type = (uint8) SvUV(ST(1));
		VALIDATE_THIS_IS_DOOR;
		THIS->GetNoKeyring();
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_GetIncline); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetIncline) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetIncline(THIS)"); // @categories Doors
	{
		Doors *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_DOOR;
		RETVAL = THIS->GetIncline();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}

XS(XS_Doors_GetSize); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetSize) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetIncline(THIS)");
	{
		Doors *THIS;
		uint32 RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_DOOR;
		RETVAL = THIS->GetSize();
		XSprePUSH;
		PUSHu((UV) RETVAL);
	}
	XSRETURN(1);
}


XS(XS_Doors_SetOpenType); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetOpenType) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetOpenType(THIS, uint32 open_type)"); // @categories Doors
	{
		Doors *THIS;
		uint32 type = (uint32) SvUV(ST(1));
		VALIDATE_THIS_IS_DOOR;
		THIS->SetOpenType(type);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetLockpick); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetLockpick) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetLockpick(THIS, uint32 lockpick_type)"); // @categories Doors
	{
		Doors *THIS;
		uint32 type = (uint32) SvUV(ST(1));
		VALIDATE_THIS_IS_DOOR;
		THIS->SetLockpick(type);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetKeyItem); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetKeyItem) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetKeyItem(THIS, uint32 key_item_id)"); // @categories Doors
	{
		Doors *THIS;
		uint32 type = (uint32) SvUV(ST(1));
		VALIDATE_THIS_IS_DOOR;
		THIS->SetKeyItem(type);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetNoKeyring); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetNoKeyring) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetNoKeyring(THIS, uint8 no_key_ring)"); // @categories Doors
	{
		Doors *THIS;
		uint8 type = (uint8) SvUV(ST(1));
		VALIDATE_THIS_IS_DOOR;
		THIS->SetNoKeyring(type);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetIncline); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetIncline) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetIncline(THIS, uint32 incline)"); // @categories Doors
	{
		Doors *THIS;
		uint32 type = (uint32) SvUV(ST(1));
		VALIDATE_THIS_IS_DOOR;
		THIS->SetIncline(type);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetSize); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetSize) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetSize(THIS, uint32 size)"); // @categories Doors
	{
		Doors *THIS;
		uint32 type = (uint32) SvUV(ST(1));
		VALIDATE_THIS_IS_DOOR;
		THIS->SetSize(type);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetLocation); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetLocation) {
	dXSARGS;
	if (items != 4)
		Perl_croak(aTHX_ "Usage: Doors::SetLocation(THIS, float x, float y, float z)"); // @categories Doors
	{
		Doors *THIS;
		float x = (float) SvNV(ST(1));
		float y = (float) SvNV(ST(2));
		float z = (float) SvNV(ST(3));
		VALIDATE_THIS_IS_DOOR;
		THIS->SetLocation(x, y, z);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetX); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetX) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetX(THIS, float x)"); // @categories Doors
	{
		Doors *THIS;
		float x = (float) SvNV(ST(1));
		VALIDATE_THIS_IS_DOOR;
		auto position = THIS->GetPosition();
		position.x = x;
		THIS->SetPosition(position);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetY); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetY) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetY(THIS, float y)"); // @categories Doors
	{
		Doors *THIS;
		float y = (float) SvNV(ST(1));
		VALIDATE_THIS_IS_DOOR;
		auto position = THIS->GetPosition();
		position.y = y;
		THIS->SetPosition(position);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetZ); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetZ) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetZ(THIS, float z)"); // @categories Doors
	{
		Doors *THIS;
		float z = (float) SvNV(ST(1));
		VALIDATE_THIS_IS_DOOR;
		auto position = THIS->GetPosition();
		position.z = z;
		THIS->SetPosition(position);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetHeading); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetHeading) {
	dXSARGS;
	if (items != 2)
		Perl_croak(aTHX_ "Usage: Doors::SetHeading(THIS, float heading)"); // @categories Doors
	{
		Doors *THIS;
		float heading = (float) SvNV(ST(1));
		VALIDATE_THIS_IS_DOOR;
		auto position = THIS->GetPosition();
		position.w = heading;
		THIS->SetPosition(position);
	}
	XSRETURN_EMPTY;
}

XS(XS_Doors_SetModelName); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_SetModelName) {
	dXSARGS;
	if (items < 1 || items > 2)
		Perl_croak(aTHX_ "Usage: Doors::SetModelName(THIS, string name)"); // @categories Doors
	{
		Doors *THIS;
		char  *name = nullptr;
		VALIDATE_THIS_IS_DOOR;
		if (items > 1) { name = (char *) SvPV_nolen(ST(1)); }

		THIS->SetDoorName(name);
	}
	XSRETURN_EMPTY;
}
XS(XS_Doors_GetModelName); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_GetModelName) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::GetModelName(THIS)"); // @categories Doors
	{
		Doors      *THIS;
		Const_char *RETVAL;
		dXSTARG;
		VALIDATE_THIS_IS_DOOR;
		RETVAL = THIS->GetDoorName();
		sv_setpv(TARG, RETVAL);
		XSprePUSH;
		PUSHTARG;
	}
	XSRETURN(1);
}

XS(XS_Doors_CreateDatabaseEntry); /* prototype to pass -Wmissing-prototypes */
XS(XS_Doors_CreateDatabaseEntry) {
	dXSARGS;
	if (items != 1)
		Perl_croak(aTHX_ "Usage: Doors::InsertDoor(THIS)"); // @categories Doors
	{
		Doors *THIS;
		VALIDATE_THIS_IS_DOOR;
		THIS->CreateDatabaseEntry();
	}
	XSRETURN_EMPTY;
}


#ifdef __cplusplus
extern "C"
#endif
XS(boot_Doors); /* prototype to pass -Wmissing-prototypes */
XS(boot_Doors) {
	dXSARGS;
	char file[256];
	strncpy(file, __FILE__, 256);
	file[255] = 0;

	if (items != 1)
		fprintf(stderr, "boot_quest does not take any arguments.");
	char buf[128];

	//add the strcpy stuff to get rid of const warnings....

	XS_VERSION_BOOTCHECK;
	newXSproto(strcpy(buf, "CreateDatabaseEntry"), XS_Doors_CreateDatabaseEntry, file, "$");
	newXSproto(strcpy(buf, "GetDoorDBID"), XS_Doors_GetDoorDBID, file, "$");
	newXSproto(strcpy(buf, "GetDoorID"), XS_Doors_GetDoorID, file, "$");
	newXSproto(strcpy(buf, "GetHeading"), XS_Doors_GetHeading, file, "$");
	newXSproto(strcpy(buf, "GetID"), XS_Doors_GetID, file, "$");
	newXSproto(strcpy(buf, "GetIncline"), XS_Doors_GetIncline, file, "$");
	newXSproto(strcpy(buf, "GetKeyItem"), XS_Doors_GetKeyItem, file, "$");
	newXSproto(strcpy(buf, "GetLockPick"), XS_Doors_GetLockpick, file, "$");
	newXSproto(strcpy(buf, "GetModelName"), XS_Doors_GetModelName, file, "$");
	newXSproto(strcpy(buf, "GetNoKeyring"), XS_Doors_GetNoKeyring, file, "$");
	newXSproto(strcpy(buf, "GetOpenType"), XS_Doors_GetOpenType, file, "$");
	newXSproto(strcpy(buf, "GetSize"), XS_Doors_GetSize, file, "$");
	newXSproto(strcpy(buf, "GetX"), XS_Doors_GetX, file, "$");
	newXSproto(strcpy(buf, "GetY"), XS_Doors_GetY, file, "$");
	newXSproto(strcpy(buf, "GetZ"), XS_Doors_GetZ, file, "$");
	newXSproto(strcpy(buf, "SetHeading"), XS_Doors_SetHeading, file, "$$");
	newXSproto(strcpy(buf, "SetIncline"), XS_Doors_SetIncline, file, "$$");
	newXSproto(strcpy(buf, "SetKeyItem"), XS_Doors_SetKeyItem, file, "$$");
	newXSproto(strcpy(buf, "SetLocation"), XS_Doors_SetLocation, file, "$$$$");
	newXSproto(strcpy(buf, "SetLockPick"), XS_Doors_SetLockpick, file, "$$");
	newXSproto(strcpy(buf, "SetModelName"), XS_Doors_SetModelName, file, "$$");
	newXSproto(strcpy(buf, "SetNoKeyring"), XS_Doors_SetNoKeyring, file, "$$");
	newXSproto(strcpy(buf, "SetOpenType"), XS_Doors_SetOpenType, file, "$$");
	newXSproto(strcpy(buf, "SetSize"), XS_Doors_SetSize, file, "$$");
	newXSproto(strcpy(buf, "SetX"), XS_Doors_SetX, file, "$$");
	newXSproto(strcpy(buf, "SetY"), XS_Doors_SetY, file, "$$");
	newXSproto(strcpy(buf, "SetZ"), XS_Doors_SetZ, file, "$$");
	XSRETURN_YES;
}
#endif //EMBPERL_XS_CLASSES
