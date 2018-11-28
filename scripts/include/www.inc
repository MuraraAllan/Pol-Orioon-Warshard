use uo;
use os;

function DesativarBotaoDireito()
WriteHTML ("<SCRIPT language="+CChr(34)+"JavaScript"+CChr(34)+" type="+CChr(34)+"text/javascript"+CChr(34)+">");
WriteHTML ("<!--");
WriteHTML ("function NoRightClick(e) ");
WriteHTML ("{ ");
WriteHTML ("   if(navigator.appName=="+CChr(34)+"Netscape"+CChr(34)+") ");
WriteHTML ("   {");
WriteHTML ("      if(e.which==3||e.which==2) ");
WriteHTML ("      { ");
WriteHTML ("         return false; ");
WriteHTML ("      }");
WriteHTML ("   }");
WriteHTML ("   else ");
WriteHTML ("   { ");
WriteHTML ("      event.cancelBubble=true; ");
WriteHTML ("      event.returnValue=false;");
WriteHTML ("   }");
WriteHTML ("}");
WriteHTML ("if(navigator.appName=="+CChr(34)+"Netscape"+CChr(34)+") ");
WriteHTML ("   window.captureEvents(Event.MOUSEDOWN)");
WriteHTML ("document.oncontextmenu=NoRightClick; ");
WriteHTML ("window.onmousedown=NoRightClick;");
WriteHTML ("// -->");
WriteHTML ("</SCRIPT>");
endfunction

