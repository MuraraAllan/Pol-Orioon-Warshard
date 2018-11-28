use uo;
use os;

include "include/client";
include "include/attributes";

function summon_creature( caster, circle, npctemplate, cast_loc )
  var thecreature;
  var thecritter;
  var magery := GetEffectiveSkill(caster, SKILLID_MAGERY);
  var duration := 10 + (magery );
  var parms := {};
  parms .+ script := "tamed";
  Detach();
  

  thecritter := CreateNpcFromTemplate(npctemplate, cast_loc.x, cast_loc.y,cast_loc.z, parms);

  if(npctemplate == "summoneddaemon")
caster.SetCriminal(1);
    PlaySoundEffect(caster, 535);

   else
    if(circle == 8)
      PlaySoundEffect(caster, 536);
      PerformAction(thecritter, 12);
    else
      PlaySoundEffect(caster, 534);
    endif
  endif

var mana := GetMana(thecritter);
SetMana(thecritter, mana - mana);
var aa := getobjproperty(caster, "serial:");

var a := SystemFindObjectBySerial( aa, sysfind_flags := 0 );

if(a)
      PlaySoundEffect( a, SFX_SPELL_MANA_VAMPIRE );
  PlayStationaryEffect( a.x, a.y, a.z, FX_SMOKE, 0xa, 0xa );
MoveCharacterToLocation(a,0,0,0,MOVECHAR_FORCELOCATION);
  Damage(a, GetHp(a) + 3);
 SetObjProperty(caster, "serial:",thecritter.serial);
endif
  SetObjProperty(thecritter,"master", caster.serial);
  SetScriptController( thecritter);
  SetObjProperty(thecritter, "happiness",100);
  SetObjProperty(thecritter, "summoned",1);
  SetObjProperty(caster, "serial:",thecritter.serial);
  RestartScript(thecritter);
  SetBaseSkillBaseValue( thecritter, SKILLID_MAGICRESISTANCE,  magery * 10  );
  sleep(duration);
  PlaySoundEffect( thecritter, SFX_SPELL_MANA_VAMPIRE );
  PlayStationaryEffect( thecritter.x, thecritter.y, thecritter.z, FX_SMOKE, 0xa, 0xa );
  MoveCharacterToLocation(thecritter,0,0,0,MOVECHAR_FORCELOCATION);
  Damage(thecritter, GetHp(thecritter) + 3);
EraseObjProperty(caster, "serial:");

endfunction

