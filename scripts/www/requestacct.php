<?php
$passwd = "12345678";
$acctName = $_GET['acctName'];
$mailAddy = $_GET['mailAddy'];
$sourceIP;

if (getenv("HTTP_CLIENT_IP")) {
   $sourceIP = getenv("HTTP_CLIENT_IP");
} else if(getenv("HTTP_X_FORWARDED_FOR")) {
   $sourceIP = getenv("HTTP_X_FORWARDED_FOR");
} else if(getenv("REMOTE_ADDR")) {
   $sourceIP = getenv("REMOTE_ADDR");
} else {
   echo "<title>Erro ao criar a conta $qtm$acctName$qtm</title><body bgcolor=#000000>";
   echo "<font color=#FF0000>Erro: Nao foi possivel resolver seu endereço de IP.  Criação Cancelada!<p>";
   echo "Criação da conta falhou!  Contate um Administrador para maiores informações.</font><p><hr>";
   echo "<form><input type=button value=Close Window onClick=window.close()></form>";
   exit;
}

$retVal = validate_email($mailAddy);
if ($retVal != "valid") {
   echo "<title>Erro ao criar a conta $qtm$acctName$qtm</title><body bgcolor=#000000>";
   echo "<font color=#FF0000>$retVal Criação Cancelada!<p>";
   echo "Criação da conta falhou!  Por favor verifique seu endereço de email e tente novamente.</font><p><hr>";
   echo "<form><input type=button value=Close Window onClick=window.close()></form>";
   exit;
}

$qtm = Chr(34);
for ($i=0; $i<8; $i++) {
   $newStr = Chr( (mt_rand(65, 90)) );
   $passwd = substr_replace($passwd, $newStr, $i, 1);
}

$file = fopen("http://localhost:27015/requestacct.ecl?acctName=$acctName&mailAddy=$mailAddy&passwd=$passwd&IP=$sourceIP", "r");
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
echo "A conta foi criada usando o IP <i><b>$sourceIP</b></i>, e as informações sobre a conta foram enviadas para <i><b>$mailAddy</b></i>.<p>";
echo "Seu IP e endereço de email estão sendo logados. Para caso ocorra futuros problemas.</font><p><hr>";
echo "<form><input type=button value=Close Window onClick=window.close()></form>";

//
// This is the confirmation email.
// Make sure you change this information to fit your shard.
//
$recipient = $mailAddy;
$subject = "Welcome to the Server";
$headers  = "MIME-Version: 1.0\r\n";
$headers .= "Content-type: text/html; charset=iso-8859-1\r\n";
$headers .= "From: The Admin<me@mycomputer.com>\r\n";
$headers .= "X-Mailer: PHP/" . phpversion();

$message = "Bem Vindo ao Sysco War Shard!<p>\r\n\r\n";
$message .= "Estes são os dados de sua conta.<p>\r\n\r\n";
$message .= "Login: <b>$acctName</b><br>\r\n";
$message .= "Senha: <b>$passwd</b><p>\r\n\r\n";
$message .= "Ao logar, caso queira mudar sua senha use o comando $qtm<b>.changepass</b>$qtm.<p>\r\n\r\n";
$message .= "Administração Sysco War Shard!<p>\r\n";
ini_set("sendmail_from", "admin@sysco.cjb.net");
mail($recipient, $subject, $message, $headers);
}

exit;

function validate_email($email_raw)
// Copied (i.e., "stolen") directly from the php doc site.
   {
   // replace any ' ' and \n in the email
   $email_nr = eregi_replace("\n", "", $email_raw);
   $email = eregi_replace(" +", "", $email_nr);
   $email = strtolower( $email );
   // do the eregi to look for bad characters
   if( !eregi("^[a-z0-9]+([_\\.-][a-z0-9]+)*". "@([a-z0-9]+([\.-][a-z0-9]+))*$",$email) ){
     // okay not a good email
     $feedback = '<font color=#FF0000>Erro: "' . $email . '" não é um email valido.</font>';
     return $feedback;
     } else {
     // okay now check the domain
     // split the email at the @ and check what's left
     $item = explode("@", $email);
     $domain = $item["1"];
     if ( ( gethostbyname($domain) == $domain ) )
       {
         if ( gethostbyname("www." . $domain) == "www." . $domain )
            {
              $feedback = '<font color=#FF0000>Erro: O dominio "' . $domain . '" nao esta correto.</font>';
              return $feedback;
            }
       // ?
          $feedback = "valid";
          return $feedback;
      } else {
       $feedback = "valid";
       return $feedback;
       }
     }
   }
?> 
