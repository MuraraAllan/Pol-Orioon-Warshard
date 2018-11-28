use uo;
use os;

Function VerificarNome(who)
var erro;
foreach a in CAscZ( who.name );
if (( a  >= 49 ) && (a <= 57))
who.name:="Numeros [DELETAR]";
erro:=1;
break;

elseif (a == 45)
who.name:="Tracinhos [DELETAR]";
erro:=1;
break;

elseif (a == 46)
who.name:="Pontinhos [DELETAR]";
erro:=1;
break;

elseif (a == 44)
who.name:="Virgulas [DELETAR]";
erro:=1;
break;

elseif (a == 59)
who.name:="Ponto e Virgula [DELETAR]";
erro:=1;
break;
endif

if(IsNull(who.name))
who.name:="Char Sem Nome [DELETAR]";
erro:=1;
endif

return erro;
endforeach



endfunction

function IsNull(texto)
foreach letra in CAscZ( texto )
if (letra != 32)
return 0;
endif
endforeach
return 1;
endfunction