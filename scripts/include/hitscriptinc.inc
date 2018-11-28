use uo;
use os;
use util;
use math;
use cfgfile;

include "include/objtype";
include "include/attributes";
include "include/client";

function DealDamage(defender, attacker, rawdamage)

var xanse := RandomInt(5);
rawdamage := rawdamage + RandomInt( (GetEffectiveSkill(attacker, 1) ) / 20);

if((attacker.x >= 104) && (attacker.x <= 151) && (attacker.y >= 1020) && (attacker.y <= 1888))
SendSysMessage(attacker, "Nao sao permitidos ataques neste local!");
SendSysMessage(defender, "Nao sao permitidos ataques neste local!");
SendSysMessage(defender, "Nao sao permitidos ataques neste local!");
SendSysMessage(defender, "Nao sao permitidos ataques neste local!");
rawdamage := 0;
endif

if((attacker.x >= 217) && (attacker.x <= 259) && (attacker.y >= 1872) && (attacker.y <= 1908))
SendSysMessage(attacker, "Nao sao permitidos ataques neste local!");
SendSysMessage(defender, "Nao sao permitidos ataques neste local!");
SendSysMessage(defender, "Nao sao permitidos ataques neste local!");
SendSysMessage(defender, "Nao sao permitidos ataques neste local!");
rawdamage := 0;
endif

ApplyRawDamage(defender, rawdamage);
PrintTextAbove(defender, " " + rawdamage + " ", FONT_SMALL_LIGHT,38);
endfunction