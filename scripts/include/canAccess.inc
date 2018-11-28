
function can_access(who, item, flags := 0)
  var owner := Cint(GetObjProperty(item, "Owner"));
  if((owner) and (owner != who.serial))
    SendSysMessage(who, "Voce nao pode usar isto.",9,89);
    return 0;
  elseif(GetObjProperty(item, "Vendored"))
    SendSysMessage(who, "Voce nao pode usar isto.",9,89);
    return 0;
  elseif(!Accessible(who, item))
    SendSysMessage(who, "Voce nao pode usar isto.",9,89);
    return 0;
  elseif((!flags["distance"]) and ((Distance(who, item) > 2)))
    SendSysMessage(who, "O Item esta muito longe.",9,89);
    return 0;
  elseif((!flags["unmovable"]) and (item.movable == 0))
    SendSysMessage(who, "Voce nao pode usar items trancados ao chao.",9,89);
    return 0;
  elseif(!ReserveItem(item))
    SendSysMessage(who, "Ja estou usando este item.",9,89);
    return 0;
  else
    return 1;
  endif
endfunction