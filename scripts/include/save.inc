use os;
use uo;
use polsys;

function salvar()

  avisar_aux_inicio();
  sleep(3);
  syslog( "Salvando o Mundo..." );
  Broadcast( "Salvando o mundo...",0,95 );
  ///var tempo:=ReadMillisecondClock();
  var res := SaveWorldState();
  ///tempo:=Cint(ReadMillisecondClock()-tempo);
   if (res)
    syslog( "Mundo Salvo!" );
    Broadcast( "Mundo Salvo!",0,95 );
    avisar_aux_fim();
   else
    Broadcast( "Erro ao salvar o mundo!",0,33 );
    syslog( "Erro ao salvar o mundo: " + res );
   endif
endfunction

function avisar_aux_inicio()
var ev;
    ev := struct;
    ev.+type := "interno";
    ev.+command := "save";
    ev.+texto:= "inicio";
    var auxconnection := GetProcess(GetGlobalProperty("#AuxConnection"));
    auxconnection.SendEvent(ev);
endfunction 

function avisar_aux_fim()
var ev;
    ev := struct;
    ev.+type := "interno";
    ev.+command := "save";
    ev.+texto:= "fim";
    var auxconnection := GetProcess(GetGlobalProperty("#AuxConnection"));
    auxconnection.SendEvent(ev);
endfunction 

function avisar_aux_erro()
    ev := struct;
    ev.+type := "interno";
    ev.+command := "save";
    ev.+texto:= "erro";
    var auxconnection := GetProcess(GetGlobalProperty("#AuxConnection"));
    auxconnection.SendEvent(ev);
endfunction 