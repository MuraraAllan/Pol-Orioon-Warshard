use uo;
use os;


function AcharPlaca(casa)
casa :=casa.components;
foreach placa in casa
if ((placa.objtype >= 3000) && (placa.objtype <= 3086)) 
return placa;
endif
endforeach
return 0;
endfunction

function Socio(pessoa,casa)

if (pessoa.cmdlevel >= 3)
return 1;
endif

if (GetObjProperty(casa, "owneracct") == pessoa.acctname)
return 1;
endif

var socios:=GetObjProperty(casa, "socios");

foreach socioo in socios
if(socioo == pessoa.serial)
return 1;
endif
endforeach

return 0;

var amigos:=GetObjProperty(casa, "amigos");

foreach amigo in amigos
if(amigo == pessoa.serial)
return 0;
endif
endforeach


endfunction



function EAmigo(pessoa,casa)

var amigos:=GetObjProperty(casa, "amigos");

foreach amigo in amigos
if(amigo == pessoa.serial)
return 1;
endif
endforeach

return 0;
endfunction