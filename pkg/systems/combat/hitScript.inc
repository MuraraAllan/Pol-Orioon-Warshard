use uo;
use os;
use util;
use math;
use cfgfile;

include "include/objtype";
include "include/attributes";
include "include/client";

function DealDamage(defender, attacker, rawdamage)
var escudo := GetEquipmentByLayer(defender, 2);
var dm := RandomDiceRoll("1d4+3");
var xanse := RandomInt(5);
rawdamage := rawdamage + RandomInt( (GetEffectiveSkill(attacker, 1) ) / 20);
var hand := (GetEquipmentByLayer(attacker, 1));
var handa := (GetEquipmentByLayer(attacker, 2));
Sendsysmessage(defender,"Lallala");

rawdamage := 5;

if((defender.x >= 2400) && (defender.y >= 60) && (defender.x <= 2500) && (defender.y <= 115))
Sendsysmessage(attacker, "Nao sao permitidos ataques nesse local!", 0,36);
rawdamage := 0;
endif 


if(escudo)
if(GetEffectiveSkill(defender, SKILLID_PARRY) > 99)
if(xanse >= 4)
SendSysMessage(defender, "Voce defendeu o ataque!",9,89);
SendSysMessage(attacker, "Seu ataque foi bloqueado!",9,89);
rawdamage := 0;
endif
endif
endif
ApplyRawDamage(defender, rawdamage);
PrintTextAbove(defender, " " + rawdamage + " ", FONT_SMALL_LIGHT,38);
endfunction


function AdjustNoto(attacker, defender)
  
endfunction


function ndamage(defender, attacker, rawdamage)
if( defender.1700 >= 3000 && defender.190 >= 1080 && defender.2350 <= 3403 && defender.401 <= 1004 )
return;
else
  rawdamage := rawdamage + RandomInt( (GetEffectiveSkill(attacker, 1) ) / 20);
PrintTextAbove(defender, " " + rawdamage + " ", FONT_SMALL_LIGHT, 38);
  ApplyRawDamage(defender, rawdamage);
endif
endfunction