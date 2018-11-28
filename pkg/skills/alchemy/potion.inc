use uo;
use os;

var cfg := ReadConfigFile("alchemy");

include "include/attributes";
var cfgg := ReadConfigFile("alchemy");
function is_reagent(what)
  case(what.objtype)
    0xf7a: return 1;
    3965: return 1;
    0xf84: return 1;
    0xf85: return 1;
    0xf86: return 1;
    0xf88: return 1;
    0xf8c: return 1;
    0xf8d: return 1;
    0xf8f: return 1;

endcase
  return 0;
endfunction

function PourPotion(user,mortar)
  try_to_make_potion(user, "spacefill", 1, mortar, 0);
endfunction

function make_the_potion(user, mortar)
  var use_on := Target( user );
  if(!use_on)
    SendSysMessage(user, "Targetting Cancelled");
    return;
  endif
  if(!can_access(user, use_on))
    return;
  endif
  if(is_reagent(use_on))
    var cfg := ReadConfigFile("alchemy");
    if(!cfg)
      return;
    endif
    var elem := cfg[use_on.objtype];
    if(!cfg)
      return;
    endif
    var possible := array;
    var tmenu := CreateMenu("Selecione a pocao");
    var num_possibilities := 0;
    var selections := array;
    possible := GetConfigStringArray( elem, "potion");
    foreach thingie in possible
      if(can_make(user, thingie, use_on))
        var titem := cfg[thingie].objtype;
          sendsysmessage(user, "aa" + titem );
        if(titem)
          thingie["_"] := " ";
           
          AddMenuItem( tmenu, titem, thingie );
          num_possibilities := num_possibilities + 1;
        endif
      endif
    endforeach
    if(num_possibilities == 0)
      SendSysMessage(user, "Voce nao tem habilidade para fazer esta porcao!",9,89);
      return;
    endif
    var citem := SelectMenuItem2(user, tmenu);
    if(!citem.objtype)
      SendSysMessage(user, "Alvo Cancelado",9,89);
      return -1;
    endif
    try_to_make_potion(user, possible[citem.index], 0, mortar, use_on);
  elseif(use_on == mortar)
    var last := GetObjProperty(mortar, "LastMade");
    if(last)
  	  try_to_make_last(user, last, mortar);
  	else
  	  SendSysMessage(user, "Voce nao pode misturar isto.",9,89);
  	  return;
  	endif
  else
    SendSysMessage(user, "Isto nao e um reagente!",9,89);
  endif
endfunction

function can_make(user, potion, reg)
  var skillneeded:= CInt(cfg[potion].skill);
  if(skillneeded > 20)
    skillneeded := skillneeded - 20;
  else
    skillneeded := 0;
  endif
  if(GetEffectiveSkill(user, SKILLID_ALCHEMY) >= skillneeded)
    return 1;
  else
    return 0;
  endif
endfunction

function take_regs(user, potion, reg)
  var amount_needed:= cfg[potion].reagent_amount;
  set_critical(1);
  if(CInt(amount_needed) <= reg.amount)
    SubtractAmount(reg, amount_needed);
    set_critical(0);
    return 1;
  else
    SendSysMessage(user, "Voce nao possui reagentes!",9,89);
    set_critical(0);
    return 0;
  endif
endfunction

function try_to_make_potion(user, potion, in_mortar, mortar, reg)
  if(!in_mortar)
    potion[" "] := "_";
    var difficulty := cfg[potion].skill;
    var points := cfg[potion].points;
    var product := cfg[potion].objtype;
    var cntr;
    SetObjProperty(mortar, "LastMade", potion);
    var loop := 0;
    while(loop < 3)
      PlaySoundEffect(user, SOUND_EFFECT_GRIND);
      PrintTextAbovePrivate(user, "Voce mistura os reagentes...",user);
      sleep(1);
      loop := loop + 1;
    endwhile
    if(!take_regs(user, potion, reg))
      return;
    endif
    if(CheckSkill(user, SKILLID_ALCHEMY, difficulty, points))
      var hasbottle:= 0;
      set_critical(1);
      foreach item in EnumerateItemsInContainer(user.backpack)
        if((item.objtype == UOBJECT_EMPTY_BOTTLE) && (item.container.objtype != 0x1940))
          if(SubtractAmount(item, 1))
            hasbottle := 1;
            break;
          endif
        endif
      endforeach
      set_critical(0);
      if(RandomInt(10) > 6)
        var skill := GetEffectiveSkill(user, SKILLID_ALCHEMY);
        ExceptionalFameMod(user, skill, difficulty, Cint(points / 4));
      endif
      if(hasbottle)
        var thing := CreateItemInBackpack(user, product, 1);
        PlaySoundEffect(user, SOUND_EFFECT_POUR);
        PrintTextAbovePrivate(user, "Voce fez a porcao e coloca em sua mochila", user);
        return;
      else
        PrintTextAbovePrivate(user, "Voce nao possui garrafas vazias.", user);
        SetObjProperty(mortar, "contents", product);
        return;
      endif
    else
      PlaySoundEffect(user, SOUND_EFFECT_POUR);
      PrintTextAbovePrivate(user, "Voce se contamina com o material.", user);
      return;
    endif
  else
    var hasbottle:= 0;
    set_critical(1);
    foreach item in EnumerateItemsInContainer(user.backpack)
      if(item.objtype == UOBJECT_EMPTY_BOTTLE)
        SubtractAmount(item, 1);
        hasbottle := 1;
        break;
      endif
    endforeach
    set_critical(0);
    if(hasbottle)
      var product := GetObjProperty(mortar, "contents");
      var thing := CreateItemInBackpack(user, product, 1);
      PlaySoundEffect(user, SOUND_EFFECT_POUR);
      PrintTextAbovePrivate(user, "Voce fez o item e colocou em sua mochila", user);
      EraseObjProperty( mortar, "contents" );
      return;
    else
      PrintTextAbovePrivate(user, "Voce nao possui garrafas vazias.", user);
      return;
    endif
  endif
endfunction

function try_to_make_last(user, potion, mortar)
  var reg;
var regalternativo;
  case(potion)
    "Refresh":            reg := FindRegs(user, 0xf7a);
    "Total_Refresh":      reg := FindRegs(user, 0xf7a);
    "Agility":            reg := FindRegs(user, 0xf7b);
    "Greater_Agility":    reg := FindRegs(user, 0xf7b); regalternativo := Findregs(user, 3975);
    "Lesser_Cure":        reg := FindRegs(user, 0xf84);
    "Cure":               reg := FindRegs(user, 0xf84);
    "Greater_Cure":       reg := FindRegs(user, 0xf84);
    "Lesser_Heal":        reg := FindRegs(user, 0xf85);
    "Heal":               reg := FindRegs(user, 0xf85);
    "Greater_Heal":       reg := FindRegs(user, 0xf85);
    "Strength":           reg := FindRegs(user, 0xf86);
    "Greater_Strength":   reg := FindRegs(user, 0xf86);
    "Lesser_Poison":      reg := FindRegs(user, 0xf88);
    "Poison":             reg := FindRegs(user, 0xf88);
    "Greater_Poison":     reg := FindRegs(user, 0xf88);
    "Deadly_Poison":      reg := FindRegs(user, 0xf88);
    "Lesser_Explosion":   reg := FindRegs(user, 0xf8c);
    "Explosion":          reg := FindRegs(user, 0xf8c);
    "Greater_Explosion":  reg := FindRegs(user, 0xf8c);
    "Porcao_Mana":        reg := FindRegs(user, 3965);
    "Porcao_Mana_Maior":  reg := FindRegs(user, 3965);
endcase
  if((reg == "none") || (regalternativo == "none"))
    SendSysMessage(user, "Voce 	 possui os reagentes para fazer a porcao.",9,89);
    return;
  endif
  potion[" "] := "_";
  var difficulty := cfg[potion].skill;
  var points := cfg[potion].points;
  var product := cfg[potion].objtype;
  var cntr;
    if(!take_regs(user, potion, reg))
    SendSysMessage(user, "Voce nao possui os reagentes para fazer a porcao.",9,89);
    return;
  endif
  PlaySoundEffect(user, SOUND_EFFECT_GRIND);
  PrintTextAbovePrivate(user, "Voce mistura os reagentes...",user);
  sleep(2);
  PlaySoundEffect(user, SOUND_EFFECT_GRIND);
  PrintTextAbovePrivate(user, "Voce mistura os reagentes...",user);
  sleep(2);
  PlaySoundEffect(user, SOUND_EFFECT_GRIND);
  PrintTextAbovePrivate(user, "Voce mistura os reagentes...",user);
  sleep(2);
  if(CheckSkill(user, SKILLID_ALCHEMY, difficulty, points))
    var hasbottle:= 0;
    set_critical(1);
    foreach item in EnumerateItemsInContainer(user.backpack)
      if(item.objtype == UOBJECT_EMPTY_BOTTLE)
        if(SubtractAmount(item, 1))
          hasbottle := 1;
          break;
        endif
      endif
    endforeach
    set_critical(0);
    if(hasbottle)
      var thing := CreateItemInBackpack(user, product, 1);
      PlaySoundEffect(user, SOUND_EFFECT_POUR);
      SetObjProperty(mortar, "LastMade", potion);
      PrintTextAbovePrivate(user, "Voce fez a porcao e colocou em sua mochila.", user);
      return;
    else
      PrintTextAbovePrivate(user, "Voce nao possui garrafas vazias.", user);
      SetObjProperty(mortar, "contents", product);
      return;
    endif
  else
    PlaySoundEffect(user, SOUND_EFFECT_POUR);
    PrintTextAbovePrivate(user, "Voce se contamina com a mistura.", user);
    return;
  endif
endfunction

function FindRegs(who, type)
  var holder := "none";
  foreach thing in EnumerateItemsInContainer(who.backpack)
    if(thing.objtype == type)
      holder := thing;
      break;
    endif
  endforeach
  return holder;
endfunction