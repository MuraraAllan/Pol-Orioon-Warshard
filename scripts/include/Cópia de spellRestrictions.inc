use uo;
use os;
use cfgfile;
use util;

include "include/fields";
include "include/attributes";
include "include/client";
include "include/objtype";
include "include/statMod";
include "include/firewall";
include "include/spellAttack";
include "include/dist";
include "include/sysEvent";

var caster;
var npccfg := ReadConfigFile("::npcdesc");
const EVID_DISCHARGE := 0x123457;


function maincast(parms, delivery, circle, noto, id);
var cast_on;
  var spellscroll := 0;
  var scroll;
  var tgtopt;
if(parms[1] == "#MOB")
    caster := parms[2];
    if(mobspellcast(caster, circle, spellscroll) == 0)
      return 0;
    endif
    cast_on := parms[3];
  elseif (parms[1] == "#scroll")
    spellscroll := 1;
    caster := parms[2];
    EraseObjProperty(caster, "IsMeditating");
    EraseObjProperty(caster, "HealTimer");
    if(spellcast(caster, circle, spellscroll, id) == 0)
      return 0;
    endif
    scroll := parms[3];
    if(!ReserveItem(scroll))
           return 0;
    endif
    if(delivery == "notarget")
      cast_on := caster;
      if(!can_cast(caster))
        cast_on := 0;
      endif
    elseif(delivery == "direct")
      if(noto == "helpful")
        cast_on := CanTargetSpell(caster, circle, TGTOPT_HELPFUL + TGTOPT_CHECK_LOS);
        if(!can_cast(caster))
          cast_on := 0;
        endif
      elseif(noto == "neutral")
        cast_on := CanTargetSpell(caster, circle, TGTOPT_CHECK_LOS);
        if(!can_cast(caster))
          cast_on := 0;
        endif
      else
        cast_on := CanTargetSpell(caster, circle, TGTOPT_HARMFUL + TGTOPT_CHECK_LOS);
        if(!can_cast(caster))
          cast_on := 0;
        endif
      endif
      if(!cast_on)
        return 0;
      endif
    elseif(delivery == "indirect")
      cast_on := CanTargetArea(caster, circle);
      if(!can_cast(caster))
        cast_on := 0;
      endif
      if (!cast_on)
        return 0;
      endif
    else
      return 0;
    endif
  else
    caster := parms;
    EraseObjProperty(caster, "IsMeditating");
    EraseObjProperty(caster, "HealTimer");
    if (spellcast(caster, circle, spellscroll, id) == 0)
      return 0;
    endif
    if (!ConsumeReagents(caster, id+100))
      SendSysMessage(caster, "Voce nao tem reagente para a magia.",9,89);
      return 0;
    endif
    if(delivery == "notarget")
      cast_on := caster;
      if(!can_cast(caster))
        cast_on := 0;
      endif
    elseif(delivery == "direct")
      if(noto == "helpful")
        cast_on := CanTargetSpell(caster, circle, TGTOPT_HELPFUL + TGTOPT_CHECK_LOS);
        if(!can_cast(caster))
          cast_on := 0;
        endif
      elseif(noto == "neutral")
        cast_on := CanTargetSpell(caster, circle, TGTOPT_CHECK_LOS);
        if(!can_cast(caster))
          cast_on := 0;
        endif
      else
        cast_on := CanTargetSpell(caster, circle, TGTOPT_HARMFUL + TGTOPT_CHECK_LOS);
        if(!can_cast(caster))
          cast_on := 0;
        endif
      endif
      if (!cast_on)
        return 0;
      endif
    elseif(delivery == "indirect")
      cast_on := CanTargetArea(caster, circle);
      if(!can_cast(caster))
        cast_on := 0;
      endif
      if (!cast_on)
        return 0;
      endif
    else
      return 0;
    endif
  endif
  if(newusemana(caster, circle, cast_on, delivery) == 0)
    PlaySoundEffect(caster,0x005d);
    PlayObjectCenteredEffect(caster, 0x3735,0x0a, 0x1e);
    return 0;
  endif
  if(spellscroll == 1)
    if(!SubtractAmount(scroll, 1))
      return 0;
    endif
  endif
  var points := getpoints(circle, spellscroll, SKILLID_MAGERY);
 
  var newparms := {};
  newparms[1] := caster;
  newparms[2] := cast_on;
  return newparms;
endfunction


function can_cast(who)
  var hand1 := (GetEquipmentByLayer(who, 1));
  var hand2 := (GetEquipmentByLayer(who, 2));
  return 1;
endfunction


function CanTargetSpell(caster, circle, targopt, location := TGTOPT_CHECK_LOS)
var cast_on := Target(caster, targopt);
if((caster.x <= 4282 && caster.y <= 944 && caster.x >= 4337 && caster.y >= 1013))
SendSysMessage(caster, "Nao e permitido soltar magia neste local!",9,89);
PlayLightningBoltEffect(caster);
return 0;
endif
if(!can_cast(caster))
    return 0;



  endif
 
  var prevtime := ReadGameClock() + 7;
  if(ReadGameClock() > prevtime)
SendSysMessage(caster, "Voce demorou demais e perdeu o focus.",9,89);
return 0;
endif
if(!cast_on)
return 0;
  endif
if(cast_on.hidden)
    SendSysMessage(caster,"Voce nao consegue ver o inimigo.",9,89);
    return 0;
  endif
  if(dist(caster, cast_on) >= 18)
    SendSysMessage(caster, "Voce nao consegue ver o inimigo.",9,89);
    return 0;
  endif
  return cast_on;

endfunction



function CanTargetArea(caster, circle)
  if (!can_cast(caster))
    return 0;
  endif
  var cast_loc := TargetCoordinates(caster);
  if (!cast_loc.x)
    return 0;
  endif
  if (!CheckLosAt(caster, cast_loc.x, cast_loc.y, cast_loc.z))
    SendSysMessage(caster, "Voce nao consegue ver o inimigo.",9,89);
    return 0;
  endif
  if(coordist(caster.x, caster.y, cast_loc.x, cast_loc.y) >= 18)
    SendSysMessage(caster, "Voce nao consegue ver o inimigo.",9,89);
    return 0;
  endif
  return cast_loc;
endfunction

function Reflected(cast_on, caster)
  var mr := CInt(GetObjProperty(cast_on, "mr"));
  if(mr >= 1)
    PlaySoundEffect(cast_on, SFX_SPELL_MAGIC_REFLECTION);
    PlayObjectCenteredEffect(cast_on, FX_CURSE_EFFECT, 10,10);
    SendSysMessage(cast_on, "Seu Reflect lhe salvou!",9,89);
    if(mr == 1)
   eraseobjproperty(cast_on, "mr");
    elseif(mr == 2)
      var holder, pid;
      var eqp := GetObjProperty(cast_on, "EquipTimers");
      foreach thing in ListEquippedItems(cast_on)
        foreach entry in eqp
          if((thing.serial == entry[1]) and (entry[2] == "ref"))
            holder := GetObjProperty(thing, "pid");
            break;
          endif
        endforeach
      endforeach
      pid := getprocess(holder);
      if(pid)
        var k := struct;
        k.+type := EVID_DISCHARGE;
        pid.sendevent(k);
      else
        EraseObjProperty(cast_on, "mr");
      endif
    endif
    return 1;
  endif
  return 0;
endfunction

function Resisted(circle, caster, cast_on, amt)
  var magery := CInt(GetEffectiveSkill(caster, SKILLID_MAGERY));
  var evalint := CInt(GetEffectiveSkill(caster, SKILLID_EVALINT));
  var resist := CInt(GetEffectiveSkill(cast_on, SKILLID_MAGICRESISTANCE));
  var chk1 := (resist / 150);
  var chk2 := resist - (((magery - 30) / 4) + (circle * 6));
  if(chk1 < 1)
    chk1 := 1;
  endif
  if(chk2 < 1)
    chk2 := 1;
  endif
  var diff := 0;
  if(chk1 > chk2)
    diff := chk1;
  else
    diff := chk2;
  endif
  var points := getresistpoints(circle, cast_on, SKILLID_MAGICRESISTANCE);
  if(cast_on.dead)
    return 0;
  endif
  if((RandomInt(99) + 20) <= diff)
SetObjProperty(cast_on, "resist", 1);    
SendSysMessage(cast_on, "Voce sente seu corpo resistindo a magia!",9,89);
SendSysMessage(caster, "azarado :P",9,89);
    PlaySoundEffect(cast_on, SFX_SPELL_WEAKEN);
    PlayObjectCenteredEffect(cast_on, FX_CURSE_EFFECT, 5,5);
   AwardRawSkillPoints(cast_on, SKILLID_MAGICRESISTANCE, points);
    amt := (amt * 0.5);
    if(amt < 1)
      amt := 1;
    endif
  endif
  var modamt := 1;
  if(resist > evalint)
    modamt := (1 + ((evalint - resist) / 200.0));
  elseif(evalint > resist)
    modamt := (1 + ((evalint - resist) / 500.0));
  endif
  amt := (amt * modamt);
  return CInt(amt);
endfunction

function CalcSpellDamage(circle, caster, cast_on)
  var die_string := circle+"d2";
  var dmg := RandomDiceRoll(die_string);
  dmg := dmg + CInt(GetEffectiveSkill(caster, SKILLID_MAGERY)/10);
  if(dmg > (circle * 2))
    dmg := circle * 2;
  endif
  return dmg;
endfunction

function CanTargetThing(caster, circle, targopt := TGTOPT_CHECK_LOS)
  if (!can_cast(caster))
    return 0;
  endif
  var cast_on := Target(caster, targopt);
  if(!cast_on)
    return;
  endif
  return cast_on;
endfunction

function spellcast(me, circle, scroll, id)

var malha := {5051, 5054, 5055};
var loriga := {5100, 5102, 5104, 5099,5107};
var couro := {5061,5062,5063,5067,5068,7609};
var plate := {5128,5129,5130,5131,5132,5133,5134,5135,5136,5137,5138,5139,5140,5141,5142,5143,5144,5145,5146};

foreach couro in ListEquippedItems(me) 
if(circle > 8 and ((couro.graphic == 5061) or (couro.graphic == 5062) or (couro.graphic == 5063) or (couro.graphic == 5067) or (couro.graphic == 5068) or (couro.graphic == 7609)))
sendsysmessage(me, "Sua armadura o inpede de invocar a magia",9,89); 
return 0; 
endif 
endforeach

foreach plate in ListEquippedItems(me) 
if(circle > 3 and ((plate.graphic == 5128) or (plate.graphic == 5129) or (plate.graphic == 5130) or (plate.graphic == 5131) or (plate.graphic == 5132) or (plate.graphic == 5133) or (plate.graphic == 5134) or (plate.graphic == 5135) or (plate.graphic == 5136) or (plate.graphic == 5137) or (plate.graphic == 5138) or (plate.graphic == 5139) or (plate.graphic == 5140) or (plate.graphic == 5141) or (plate.graphic == 5142) or (plate.graphic == 5143) or (plate.graphic == 5144) or (plate.graphic == 5145) or (plate.graphic == 5136)))
sendsysmessage(me, "Sua armadura o inpede de invocar a magia",9,89); 
return 0; 
endif 
endforeach

foreach loriga in ListEquippedItems(me) 
if(circle > 7 and ((loriga.graphic == 5100) or (loriga.graphic == 5102) or (loriga.graphic == 5104) or (loriga.graphic == 5099) or (loriga.graphic == 5107)))
sendsysmessage(me, "Sua armadura o inpede de invocar a magia",9,89); 
return 0; 
endif 
endforeach

foreach malha in ListEquippedItems(me) 
if(circle > 6 and ((malha.graphic == 5051) or (malha.graphic == 5054) or (malha.graphic == 5055))) 
sendsysmessage(me, "Sua armadura o inpede de invocar a magia",9,89); 
return 0; 
endif 
endforeach

var spellcfg := ReadConfigFile(":spells:spells");
  var val := SplitWords(spellcfg[id].val);
  var times := CInt(val[1]);
  var slp   := CInt(val[2]);
  var mhp := GetHp(me);
  var umana, diff, points, delay;
  var n := 1;
if(scroll == 0)
    case (circle)
      1:   umana :=   4;     diff :=  10; delay := Readgameclock() + 5;
      2:   umana :=   6;     diff :=  20; delay := Readgameclock() + 7;
      3:   umana :=   9;     diff :=  30; delay := Readgameclock() + 9;
      4:   umana :=  11;     diff :=  50; delay := Readgameclock() + 11;
      5:   umana :=  14;     diff :=  60; delay := Readgameclock() + 13;
      6:   umana :=  23;     diff :=  70; delay := Readgameclock() + 15;
      7:   umana :=  40;     diff :=  80; delay := Readgameclock() + 17;
      8:   umana :=  50;     diff :=  90; delay := Readgameclock() + 20;
      9:   umana :=  75;     diff :=  80; delay := Readgameclock() + 5;
     10:   umana := 100;     diff :=  80; delay := Readgameclock() + 5;
    endcase
  elseif(scroll == 1)
    case (circle)
      1:   umana :=   4;     diff := 10;
      2:   umana :=   6;     diff := 10;
      3:   umana :=   9;     diff := 10;
      4:   umana :=  11;     diff := 20;
      5:   umana :=  14;     diff := 30;
      6:   umana :=  20;     diff := 50;
      7:   umana :=  40;     diff := 50;
      8:   umana :=  50;     diff := 60;
      9:   umana :=  75;     diff := 60;
     10:   umana := 100;     diff := 60;
    endcase
  else
    return 0;
  endif

 
if((mhp > GetHp(me)) && ((RandomInt(99)+1) > (GetEffectiveSkill(me, SKILLID_WRESTLING)/2)))
if(GetObjProperty(me, "resist"))
EraseObjProperty(me, "resist"); 
return 1;
endif
EnableEvents(SYSEVENT_DAMAGED);    
PlayStationaryEffect( me.x, me.y, me.z, FX_SMOKE, 0xa, 0xa );     
PlaySoundEffect(me,0x005d);
return 0;
    endif
if (umana > GetMana(me))
PerformAction(me,ANIM_CAST_DIR);
sleepms(1200);
    me.frozen :=0;
    SendSysMessage(me,"Voce nao tem mana suficiente para a magia.",9,89);
    PlaySoundEffect(me,0x005d);
    PlayObjectCenteredEffect(me, 0x3735,0x0a, 0x1e);
    return 0;
  endif
  if(can_cast(me))
for (n:=1; n<=times; n:=n+1)
if((mhp > GetHp(me)) && ((RandomInt(99)+1) > (GetEffectiveSkill(me, SKILLID_WRESTLING)/2)))
if(GetObjProperty(me, "resist"))
EraseObjProperty(me, "resist");   
return 1;
endif
EnableEvents(SYSEVENT_DAMAGED);        
PlayStationaryEffect( me.x, me.y, me.z, FX_SMOKE, 0xa, 0xa );     
PlaySoundEffect(me,0x005d);        
PlayObjectCenteredEffect(me, 0x3735,0x0a, 0x1e);
me.frozen :=0;
        return 0;
      endif
PerformAction(me,ANIM_CAST_DIR);
      sleepms(900);
    endfor
    if(slp)
      sleepms(slp * 100);
    endif
    me.frozen :=0;
if (CheckSkill(me,SKILLID_MAGERY, diff, 0))
if((mhp > GetHp(me)) && ((RandomInt(99)+1) > (GetEffectiveSkill(me, SKILLID_WRESTLING)/2)))
if(GetObjProperty(me, "resist"))
EraseObjProperty(me, "resist");
return 1;
endif
EnableEvents(SYSEVENT_DAMAGED);        
PlayStationaryEffect( me.x, me.y, me.z, FX_SMOKE, 0xa, 0xa );     
PlaySoundEffect(me,0x005d);
return 0;
      endif
return 1;
    else
      PlaySoundEffect(me,0x005d);
      PlayStationaryEffect( me.x, me.y, me.z, FX_SMOKE, 0xa, 0xa ); 
      return 0;
    endif
else
PlaySoundEffect(me,0x005d);
      PlayStationaryEffect( me.x, me.y, me.z, FX_SMOKE, 0xa, 0xa ); 
      return 0;
    endif

 

endfunction

function newusemana(who, circle, cast_on, delivery)
  if(delivery == "direct")
    if(!CheckLineOfSight(who, cast_on))
      SendSysMessage(who, "Voce nao consegue ver o inimigo.",9,89);
      return 0;
    endif
  elseif(delivery == "indirect")
    if(!CheckLosAt(who, cast_on.x, cast_on.y, cast_on.z))
      SendSysMessage(who, "Voce nao consegue ver o inimigo.",9,89);
      return 0;
    endif
  endif
  if(cdist(who.x, who.y, cast_on.x, cast_on.y) > 18)
    var check := 0;
    foreach thing in EnumerateItemsInContainer(who.backpack)
      if(thing == cast_on)
        check := 1;
        break;
      endif
    endforeach
    if(!check)
      SendSysMessage(who,"Voce deve selecionar algo.",9,89);
      return 0;
    endif
  endif

  var umana;
    case (circle)
    1: umana :=  4;
    2: umana :=  6;
    3: umana :=  9;
    4: umana := 11;
    5: umana := 14;
    6: umana := 20;
    7: umana := 40;
    8: umana := 50;
  endcase
  var mana := GetMana(who);
  if(mana >= umana)
    SetMana(who, Cint(mana - umana));
    return 1;
  else
    SendSysMessage(who,"Voce nao tem mana suficiente para a magia.",9,89);
    return 0;
  endif
var delays;
  case (circle)
      1:   delays := 1;
      2:   delays := 7;
      3:   delays := 9;
      4:   delays := 11;
      5:   delays := 13;
      6:   delays :=  15;
      7:   delays := 17;
      8:   delays :=  20;
      9:   delays :=  5;
     10:   delays :=  5;
    endcase
if(Readgameclock()+delays >= Readgameclock())  
else 
Sendsysmessage(caster, "Voce demorou Demais e perdeu o focus da magia");
return 1;
endif
endfunction

function mobspellcast(me, circle, scroll)
  var diff, points, umana;
  case(circle)
    1:   diff := 10;     points :=  20;    umana :=   4;
    2:   diff := 20;     points :=  40;    umana :=   6;
    3:   diff := 30;     points :=  80;    umana :=   9;
    4:   diff := 40;     points := 100;    umana :=  11;
    5:   diff := 50;     points := 130;    umana :=  14;
    6:   diff := 60;     points := 160;    umana :=  20;
    7:   diff := 70;     points := 190;    umana :=  40;
    8:   diff := 80;     points := 210;    umana :=  50;
  endcase

  if(umana > GetMana(me))
    return 0;
  endif
  if(can_cast(me))
    if(CheckSkill(me, SKILLID_MAGERY, (diff - 10), points))
      return 1;
    else
      return 0;
    endif
  endif

 
endfunction

function getpoints(c, scroll, skillid)
  var points;
  var diff;
  if(scroll == 1)
    case(c)
      1:   points :=  10; diff :=  0;
      2:   points :=  20; diff := 10;
      3:   points :=  20; diff := 10;
      4:   points :=  40; diff := 20;
      5:   points :=  60; diff := 35;
      6:   points := 100; diff := 50;
      7:   points := 120; diff := 60;
      8:   points := 140; diff := 70;
    endcase
  else
    case(c)
      1:   points :=  20; diff := 10;
      2:   points :=  40; diff := 20;
      3:   points :=  80; diff := 30;
      4:   points := 100; diff := 40;
      5:   points := 120; diff := 50;
      6:   points := 140; diff := 60;
      7:   points := 160; diff := 70;
      8:   points := 180; diff := 80;
    endcase
  endif
  var skill := GetEffectiveSkill(caster, skillid);
  if(skill > (diff - 20))
    if((skill - diff) <= 5)
      points := points;
    elseif((skill - diff) <= 10)
      points := (points * 3) / 4;
    elseif((skill - diff) <= 15)
      points := points / 2;
    elseif((skill - diff) <= 15)
      points := points / 4;
    else
      points := 0;
    endif
  endif
  return points;
endfunction

function getresistpoints(c, victim, skillid)
  var points;
  var diff;
  case(c)
    1:   points :=  20; diff := 20;
    2:   points :=  40; diff := 30;
    3:   points :=  80; diff := 40;
    4:   points := 100; diff := 50;
    5:   points := 120; diff := 60;
    6:   points := 140; diff := 70;
    7:   points := 160; diff := 86;
    8:   points := 180; diff := 100;
  endcase
  var skill := GetEffectiveSkill(victim, skillid);
  if(skill > (diff - 20))
    if((skill - diff) <= 5)
      points := points;
    elseif((skill - diff) <= 10)
      points := (points * 3) / 4;
    elseif((skill - diff) <= 15)
      points := points / 2;
    elseif((skill - diff) <= 15)
      points := points / 4;
    else
      points := 0;
    endif
  endif
  return points;
endfunction

function cdist(x1, y1, x2, y2)
  var xd := x1 - x2;
  var yd := y1 - y2;
  if (xd < 0)
    xd := -xd;
  endif
  if (yd < 0)
    yd := -yd;
  endif
  if (xd > yd)
    return xd;
  else
    return yd;
  endif
endfunction

function usemana(who, circle, cast_on)
  if(cast_on.mobile)
    if(!CheckLineOfSight(who, cast_on))
      SendSysMessage(who, "Voce nao consegue ver o inimigo.",9,89);
      return 0;
    endif
  else
    if(!CheckLosAt(who, cast_on.x, cast_on.y, cast_on.z))
      SendSysMessage(who, "Voce nao consegue ver o inimigo.",9,89);
      return 0;
    endif
  endif
  if(cdist(who.x, who.y, cast_on.x, cast_on.y) > 12)
    SendSysMessage(who,"Voce nao consegue ver o inimigo.",9,89);
    return 0;
  endif
  var umana;
  case (circle)
    1: umana :=   4;
    2: umana :=   6;
    3: umana :=   9;
    4: umana :=  11;
    5: umana :=  14;
    6: umana :=  20;
    7: umana :=  40;
    8: umana :=  50;
    9: umana :=  75;
   10: umana := 100;
  endcase
  var mana := GetMana(who);
  if(mana >= umana)
    var ms := SetMana(who, Cint(mana - umana));
    return 1;
  else
    SendSysMessage(who,"Voce nao tem mana suficiente para a magia.",9,89);
    return 0;
  endif
endfunction

