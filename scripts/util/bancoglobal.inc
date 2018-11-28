//
// bank.inc: global bankbox functions
//
// public functions:
//      FindBankBox( character)      returns World Bank bankbox for a character
//      WipeBankBox( character )     does what you might think.
//      OpenWorldBank()              returns handle to World Bank.
//

use os;

include "include/objtype";

function ProcurarBancoGlobal( who )
  var banco := AbrirBancoGlobal();
   if(!banco)
   return;
   endif

  var banconame := "Banco da acc " + who.acct.name;
  var bankbox := FindRootItemInStorageArea( banco, banconame );
  if (!bankbox)
    bankbox := CreateRootItemInStorageArea( banco, banconame, UOBJ_BANKBOX );
  endif
  if(!bankbox)
    syslog( "Nao foi possivel criar um banco global para " + who.acct.name );
  endif
  return bankbox;
endfunction

///Para uso no gmtools
function ProcurarBancoGlobalGM( conta )
  var banco := AbrirBancoGlobal();
   if(!banco)
   return;
   endif

  var banconame := "Banco da acc " + conta.name;
  var bankbox := FindRootItemInStorageArea( banco, banconame );
  if (!bankbox)
    bankbox := CreateRootItemInStorageArea( banco, banconame, UOBJ_BANKBOX );
  endif
  if(!bankbox)
    syslog( "Nao foi possivel criar um banco global para " + conta.name );
  endif
  return bankbox;
endfunction

function WipeBancoGlobal( character )
  var banco := AbrirBancoGlobal();
  var bancochar := "Banco da acc " + character.acct.name;
  return DestroyRootItemInStorageArea( banco, bancochar );
endfunction

function AbrirBancoGlobal()
  var banco := FindStorageArea( "Banco Global" );
  if (!banco)
    banco := CreateStorageArea( "Banco Global" );
  endif
  if (!banco)
    syslog( "Nao foi possivel criar os Bancos Globais." );
  endif
  return banco;
endfunction