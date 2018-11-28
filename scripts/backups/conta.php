<?php
$passwd = "12345678";
$acctName = $_GET['acctName'];
$sourceIP;

$qtm = Chr(34);
for ($i=0; $i<8; $i++) {
   $newStr = Chr( (mt_rand(65, 90)) );
   $passwd = substr_replace($passwd, $newStr, $i, 1);
}

$file = fopen("http://sysco.servegame.com:27015/conta.ecl?acctname=$acctName&passwd=$passwd", "r");
sleep(3);
if (!$file) {
   echo "<title>Conexão não estabelecida!</title><body bgcolor=#000000>";
   echo "<font color=#FF0000><p>Servidor provavelmente OFF-Line.\n</font>";
   exit;
}
$returnline = fgets($file, 1024);
$statusline = fgets($file, 1024);

echo "<html>";
if ( RTrim($returnline)=="ERR") {
   echo "<title>Erro ao criar a conta $qtm$acctName$qtm</title><body bgcolor=#000000>";
   echo "<font color=#FF0000>$statusline<p>";
   echo "Criação da conta falhou!</font><p><hr>";
   echo "<form><input type=button value=Close Window onClick=window.close()></form>";
   exit;
} else {
	 echo "<title>Conta $qtm$acctName$qtm criada!</title><body bgcolor=#000000>";
	 echo "<font color=#FF0000><b>$statusline</b><hr>";
	 echo "A conta foi criada usando o IP <i><b>$sourceIP</b></i>, sua senha é: <i><b>$passwd</b></i>.<p>";
	 echo "Diferencie minusculas de maiusculas. Para trocar sua senha use "<i><b>.password</i></b>"!</font>";
	 echo "<form><input type=button value=Close Window onClick=window.close()></form>";
	 exit;
}
exit;