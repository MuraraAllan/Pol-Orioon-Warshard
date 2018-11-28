use uo;
use util;
include "include/attributes";

function GetModAmount(magery)
  var mod_amount := CInt(RandomInt(3) +(magery/10));
  if(mod_amount > 10)
    mod_amount := 10;
  endif
  return mod_amount;
endfunction

function GetModDuration(magery)
  var duration := CInt(60 +((magery / 30) * 60));
  return(duration);
endfunction

function CanMod(who, stat)
  var modd;
  case(stat)
    "str": modd := "#ss";
    "dex": modd := "#dd";
    "int": modd := "#ii";
    "p"  : modd := "#pp";
    "ar" : modd := "#ar";
  endcase
  if(GetObjProperty(who, modd))
    return 0;
  else
    return 1;
  endif
endfunction

function DoTempMod(who, stat, amt, duration)
  var modd;
  case(stat)
    "str":  modd := "#ss";  SetStrengthMod(who, GetStrengthMod(who) + amt);
    "dex":  modd := "#dd";  SetDexterityMod(who, GetDexterityMod(who) + amt);
    "int":  modd := "#ii";  SetIntelligenceMod(who, GetIntelligenceMod(who) + amt);
    "ar" :  modd := "#ar";  who.ar_mod           := who.ar_mod + amt;
	"p"  :  modd := "#pp";  who.setParalyzed(1);
  endcase
  SetObjProperty(who,modd,1);
  var parms := {};
  parms[2] := who;
  parms[1] := stat;
  parms[3] := amt;
  parms[4] := duration;
  parms[5] := who.serial;
  start_script("::/misc/unmod", parms);
endfunction