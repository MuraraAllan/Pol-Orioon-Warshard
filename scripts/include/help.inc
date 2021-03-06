var onlinecounselors;
var onlinestaff;

onlinecounselors := staffcheck("coun");
onlinestaff := staffcheck("gm");

function Icanpage(thechar)
  foreach person in EnumerateOnlineCharacters()
    if ((GetObjProperty(person,"canpage")) && (person.serial != thechar.serial))
      return 0;
    endif
  endforeach
  SetObjProperty(thechar, "canpage", 1);
  return 1;
endfunction

function staffcheck(type)
  var stafflist := GetProcess(GetGlobalProperty("#stafflist"));
  var k := struct;
  case(type)
    "coun": k.+type := EVID_FIND_COUN;
    "gm":   k.+type := EVID_FIND_GM;
  endcase
  k.+pid := getpid();
  stafflist.sendevent(k);
  var ev := wait_for_event(10);
  var data := ev.data;
  return data;
endfunction

function pagecheck(serial, type)
  var cserial := CInt(serial);
  var retval := 0;
  var i;
  case(CInt(type))
    1: var maxi := gmpages.size();
	   for(i := 0; i < maxi; i := i + 1)
		 if (cserial == CInt(gmpages[i]))
		   retval := i;
		   break;
		 endif
	   endfor
    2: var maxi := counpages.size();
	   for(i := 0; i < maxi; i := i + 1)
		 if (cserial == CInt(counpages[i]))
		   retval := i;
		   break;
		 endif
	   endfor
  endcase
  return retval;
endfunction

function pagewarning(type, thepage, who,stafftipo)
  case(type)
    1: foreach char in onlinestaff
		 SendSysMessage( char, "Chegou page para " + stafftipo +" !",0,221);
    PlaySoundEffect( char, 0x1D3 );
sleepms(650);
  PlaySoundEffect( char, 0x1D3 );
sleepms(650);
    PlaySoundEffect( char, 0x1D3 );
sleepms(650);
  PlaySoundEffect( char, 0x1D3 );
sleepms(650);
    PlaySoundEffect( char, 0x1D3 );
sleepms(650);
  PlaySoundEffect( char, 0x1D3 );
sleepms(650);
		
	   endforeach
    2: foreach char in onlinecounselors
		  SendSysMessage( char, "Chegou page para " + stafftipo +" !",0,221);
        PlaySoundEffect( char, 0x1D3 );
sleepms(650);
  PlaySoundEffect( char, 0x1D3 );
sleepms(650);
    PlaySoundEffect( char, 0x1D3 );
sleepms(650);
  PlaySoundEffect( char, 0x1D3 );
sleepms(650);
    PlaySoundEffect( char, 0x1D3 );
sleepms(650);
  PlaySoundEffect( char, 0x1D3 );
sleepms(650);
	   endforeach
  endcase
endfunction
