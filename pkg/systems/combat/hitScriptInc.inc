use uo;
use os;
use util;
use math;
use cfgfile;

include "include/objtype";
include "include/attributes";
include "include/client";

function DealDamage(defender, attacker, rawdamage)
///var escudo := GetEquipmentByLayer(defender, 2);
///var dm := RandomDiceRoll("1d4+4");
///var xanse := RandomInt(5);
///rawdamage := rawdamage + RandomInt( (GetEffectiveSkill(attacker, 1) ) / 20);
var hand := (GetEquipmentByLayer(attacker, 1));
var handa := (GetEquipmentByLayer(attacker, 2));

ApplyRawDamage(defender, rawdamage);
PrintTextAbove(defender, " " + rawdamage + " ", FONT_SMALL_LIGHT,38);
endfunction


function AdjustNoto(attacker, defender)
  if!(defender.dead)
	return 0;
  endif
  var karma := CInt(GetObjProperty(attacker, "Karma") );
  var fame := CInt(GetObjProperty(attacker, "Fame") );
  var vkarma := CInt(GetObjProperty(defender, "Karma") );
  var vfame := CInt(GetObjProperty(defender, "Fame") );
  var kmod := 1;
  fame := fame + CInt( (vfame / 10) / ( CInt(Log10(fame)) + 1 ) );
  if !(defender.npctemplate)
	vfame := CInt(vfame * 0.9);
  endif
  if((karma < -15) && (vkarma < -15))
	return;
  endif
  if(vkarma > 15)
	kmod := -1;
	karma := Abs(karma);
  else
	vkarma := Abs(vkarma);
  endif
  kmod := kmod * CInt( (vkarma / 10) / ( CInt(Log10(karma)) + 1 ) );
  karma := karma + kmod;
endfunction