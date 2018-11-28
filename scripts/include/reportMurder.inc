use uo;
use os;

include "include/bounty";
include "include/datafile";
include "../pkg/foundations/gumps/gumps";
include "include/yesnoreportar";
/////const LONG_COUNT_DECAY_TIME := 144000; //40 hours
const LONG_COUNT_DECAY_TIME := 72000; //20 hours
const SHORT_COUNT_DECAY_TIME := 28800; //8 hours


var reportables;
var reportdata := array;

function SendReportGump(who)

  reportables := who.reportables;

  FillInArrays(who);
  SetObjProperty(who, "ReportMenu", reportdata);
  var ret := GFSendGump(who);
  if(ret == 0)
    return;
  endif
  EraseObjProperty(who, "ReportMenu");
  EraseObjProperty(who, "LoginReport");
  var holder := array;
  foreach id in (ret.keys)
    if(id in reportdata)
	  var mob := SystemFindObjectBySerial(id, SYSFIND_SEARCH_OFFLINE_MOBILES);
	  if(!mob.ip)
	    SetObjProperty(mob.killer, "LoginNotify", who.serial);
	  else
	    AdjustNoto(mob, who);
	  endif
	  holder.append(id);
	  AdjustMurderCounts(who, mob.killer);
	endif
  endforeach
  foreach reportable in(who.reportables)
	who.removeReportable(reportable.serial, reportable.gameclock);
  endforeach
  var parms := array;
  parms.append(who);
  parms.append(holder);
  start_script(":bountyboard:bounty", parms);
endfunction

function FillInArrays(who)
////  var prev_y := 80;
 //////// var buttonret := 10;
 ///// GFPage(1);
var reportables := who.reportables;

  foreach reportable in reportables

    if(!reportable.killer.cmdlevel)

 ///	  if(buttonret == 21)
	///    prev_y := 80;
	///  endif
///	  reportdata.append(reportable.killer.serial);
	 // GFCheckBox(40, prev_y+20, 210, 211, 0, reportable.killer.serial);
	///  GFTextLine(60, prev_y+20, 0, reportable.killer.name);
   var a := yesno(who,"Reportar "+ reportable.killer.name + "?");

var killer := reportable.killer;

 foreach reportable in(reportables)
	who.removeReportable(reportable.serial, reportable.gameclock);
who.paralyzed := 1;
  endforeach
    if(!a)
sendsysmessage(who, "Cancelado");
who.paralyzed := 0;
elseif(a)
  ////var onlinetime := GetObjProperty(killer,"onlinetimer");

  var longcount := GetObjProperty(killer,"longmurders");
  if(!longcount)
	longcount := 0;
  endif
  longcount := longcount + 1;
  SetObjProperty(killer,"longmurders",longcount);

  var decaylong:=GetObjProperty(killer,"decaytime");
  if(!decaylong)
  SetObjProperty(killer,"decaytime", ReadGameClock());
  endif

  SetObjProperty(killer,"decaytime", ReadGameClock()+LONG_COUNT_DECAY_TIME);
 SendSysMessage(killer,"Voce Foi reportado pelo assasinato de " + who.name);

 if(longcount == 5)
  if(GetObjProperty(killer, "sexo") == "homem") 
   SendSysMessage(killer,"Voce agora e conhecido como O Assassino " +killer.name+ ".",9,33);
  endif

  if(GetObjProperty(killer, "sexo") == "mulher")  
   SendSysMessage(killer,"Voce agora e conhecida como A Assassina " +killer.name+ ".",9,33);
  endif  
 endif
 
 if(longcount>=5)
    if(GetObjProperty(killer, "sexo") == "homem") 
      killer.title_prefix:="O Assassino ";
    endif

    if(GetObjProperty(killer, "sexo") == "mulher")  
      killer.title_prefix:="A Assassina ";
    endif   

   killer.setMurderer(1);
   killer.alignment := "evil";
  endif

  /////SetObjProperty(killer,"decaylongcountat",onlinetime+LONG_COUNT_DECAY_TIME);
  ///////var shortcount := GetObjProperty(killer,"shortmurders");
  /////if(!shortcount)
///////	shortcount := 0;
  ////endif
  //////shortcount := shortcount + 1;
  ///////SetObjProperty(killer,"shortmurders",shortcount);
 ////// SetObjProperty(killer,"decayshortcountat",onlinetime+SHORT_COUNT_DECAY_TIME);
 who.paralyzed := 0;
endif
///	  prev_y := prev_y+20;
////	  buttonret := buttonret+1;
    endif

  endforeach
endfunction

function AdjustMurderCounts(who, killer)
  var onlinetime := GetObjProperty(killer,"onlinetimer");
  var longcount := GetObjProperty(killer,"longmurders");
  if(!longcount)
	longcount := 0;
  endif
  longcount := longcount + 1;
  SetObjProperty(killer,"longmurders",longcount);
  if(longcount>4)
	killer.setMurderer(1);
	SendSysMessage(killer,"You are now known as a murderer!");
  endif
  SetObjProperty(killer,"decaylongcountat",onlinetime+LONG_COUNT_DECAY_TIME);
  var shortcount := GetObjProperty(killer,"shortmurders");
  if(!shortcount)
	shortcount := 0;
  endif
  shortcount := shortcount + 1;
  SetObjProperty(killer,"shortmurders",shortcount);
  SetObjProperty(killer,"decayshortcountat",onlinetime+SHORT_COUNT_DECAY_TIME);
endfunction
