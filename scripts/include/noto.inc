use uo;
use util;
use math;
include "include/attributes";

var nototitles :=
{
    {"Funesto",     "Fascinora",   "Abominavel",       "Terrivel",         "Terrivel"},
    {"Pernicioso",  "Covarde",     "Depravado",        "Cruel",            "Cruel"},
    {"Nocivo",      "Perverso",    "Vil",              "Maligno",          "Maligno"},
    {"Noturno",     "Malicioso",   "Ignobil",          "Sinistro",         "Sinistro"},
    {"Rude",        "Desonesto",   "Estupido",         "Infame",           "Infame"},
    {"None",        "Conhecido",   "Renomado",         "Damoso",           "None"},
    {"Correto",     "Honesto",     "Justo",            "Pobro",            "Pobro"},
    {"Gentil",      "Qualificado", "Nobre",            "Ilustre",          "Ilustre"},
    {"Confiavel",   "Respeitado",  "Veneravel",        "Eminente",         "Eminente"},
    {"Bom",         "Estimado",    "Estraordinario",   "Grandioso",        "Grandioso"},
    {"Digno",       "Honrado",     "Admiravel",        "Glorioso",         "Glorioso"}
};




 


function AdjustNoto(attacker, defender)
  if(attacker.isA(POLCLASS_NPC))
    return;
  endif
  var karma   := CInt(GetObjProperty(attacker, "Karma"));
  var fame    := CInt(GetObjProperty(attacker, "Fama"));
  var dkarma  := CInt(GetObjProperty(defender, "Karma"));
  var dfame   := CInt(GetObjProperty(defender, "Fama"));
  var dfchk, dkchk;
  if(defender.isA(POLCLASS_MOBILE))
    dkarma := dkarma / 100.0;
    dkchk := dkarma * 10;
  elseif(!GetStrength(defender))
    dkarma := dkarma * 10;
    dkchk := dkarma * 10;
    dkchk := 0 - dkchk;
  endif
  if(defender.isA(POLCLASS_MOBILE))
    dfame := dfame / 100.0;
    dfchk := dfame * 10;
  elseif(!GetStrength(defender))
    dfchk := dfame * 100;
    dfame := dfame * 10;
  endif
  var kmod      := GetKarmaLevel(karma) - 6;
  var fmod      := GetFameLevel(fame);
  var dkmod     := GetKarmaLevel(dkchk) - 6;
  var dfmod     := GetFameLevel(dfchk);
  var famegain  := dfame;
  var karmagain := (0 - dkarma);
  var chk := 0;
  if(karmagain >= 0)
    chk := 1;
  endif
  if(Abs(kmod) > Abs(dkmod))
    karmagain := 0;
  elseif(Abs(kmod) == Abs(dkmod))
    karmagain := Abs(karmagain) / 4;
    if(chk == 0)
      karmagain := (0 - karmagain);
    endif
  else
    karmagain := Abs(karmagain) / 2;
    var holder := 0;
    case(dkmod - kmod)
      1: holder := 0.15;
      2: holder := 0.30;
      3: holder := 0.45;
      4: holder := 0.60;
      5: holder := 0.75;
      6: holder := 0.90;
    endcase
    karmagain := karmagain + CInt(karmagain * holder);
    if(chk == 0)
      karmagain := (0 - karmagain);
    endif
  endif
  if(fmod == dfmod)
    famegain := famegain / 4;
  elseif(fmod > dfmod)
    famegain := 0;
  else
    famegain := famegain / 2;
  endif
  if(defender.isA(POLCLASS_MOBILE))
    famegain := famegain / 100;
    karmagain := karmagain / 100;
  endif
  karma := karma + karmagain;
  fame := fame + famegain;
  var online := 0;
  if(!attacker.isA(POLCLASS_NPC))
    foreach char in EnumerateOnlineCharacters()
      if(char == attacker)
        online := 1;
        break;
      endif
    endforeach
  
  endif
endfunction

function GetFameLevel(fame)
  var fmod := 0;
  if((fame <= 1249) && (fame >= 0))
    fmod := 1;
  elseif((fame <= 2499) && (fame >= 1250))
    fmod := 2;
  elseif((fame <= 4999) && (fame >= 2500))
    fmod := 3;
  elseif((fame <= 9999) && (fame >= 5000))
    fmod := 4;
  elseif(fame >= 10000)
    fmod := 5;
  endif
  return fmod;
endfunction

function GetKarmaLevel(karma)
  var kmod := 0;
  if(karma <= -10000)
    kmod := 1;
  elseif((karma <= -5000) && (karma >= -9999))
    kmod := 2;
  elseif((karma <= -2500) && (karma >= -4999))
    kmod := 3;
  elseif((karma <= -1250) && (karma >= -2499))
    kmod := 4;
  elseif((karma <=  -625) && (karma >= -1249))
    kmod := 5;
  elseif((karma <=   624) && (karma >=  -624))
    kmod := 6;
  elseif((karma <=  1249) && (karma >=   625))
    kmod := 7;
  elseif((karma <=  2499) && (karma >=  1250))
    kmod := 8;
  elseif((karma <=  4999) && (karma >=  2500))
    kmod := 9;
  elseif((karma <=  9999) && (karma >=  5000))
    kmod := 10;
  elseif(karma >= 10000)
    kmod := 11;
  endif
  return kmod;
endfunction

function SetNotoTitle(who, karma, fame)

endfunction

function SendGainMessage(who, type, amount)
  var msgtext := "voce ";
  if(amount < 0)
    msgtext := msgtext + "perdeu ";
    amount := Abs(amount);
  else
    msgtext := msgtext + "ganhou ";
  endif
  if(amount > 150)
    msgtext := msgtext + "um bocado ";
  elseif(amount > 125)
    msgtext := msgtext + "bastante ";
  elseif(amount > 75)
    msgtext := msgtext + "uma boa quantidade ";
  elseif(amount > 30)
    msgtext := msgtext + "um pouco ";
  elseif(amount > 0)
    msgtext := msgtext + "quase nada";
  else
    return 0;
  endif
  msgtext := msgtext + type + ".";
  SendSysMessage(who, msgtext,9,90);
endfunction