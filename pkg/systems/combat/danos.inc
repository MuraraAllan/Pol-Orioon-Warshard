use uo;
use os;


function dmg(attacker, weapon)
var dano;
var armalumber:=0;

case(weapon.graphic)
 //error:	dano:=RandomInt(3); 	  		///wrestling
 3936:	dano:=RandomInt(19) + 18;  		///Espada Longa
 5039:	dano:=RandomInt(18) + 6; armalumber:=1; ///MACHADO DE GUERRA
 5042:	dano:=RandomInt(13) + 15;		///ARCO
 3919:	dano:=RandomInt(15) + 17;		///BESTA
 5117:	dano:=RandomInt(14) + 16;		///BESTA PESADA
 3913:  dano:=RandomInt(22) + 8; armalumber:=1;	///MACHADO
 3911:	dano:=RandomInt(25) + 5; armalumber:=1;	///MACHADINHO
 3915:  dano:=RandomInt(25) - RandomInt(10) + randomint(10) - randomint(10) + 3; armalumber:=1; ///MACHADO DUPLO
 3909:  dano:=RandomInt(20) + 4; armalumber:=1;	 ///MACHADO DO CARRASCO
 5114:  dano:=RandomInt(25) + 5; armalumber:=1;  ///MACHADO DE BATALHA
 5186:  dano:=RandomInt(20) + 6; armalumber:=1;  ///MACHADO DE DUAS MAOS
 5180:  dano:=RandomInt(15) + 7;		 ///MARRETA
 3932:	dano:=RandomInt(15) + 5;		 ///MACA
 5178:  dano:=RandomInt(22) + 11;		 ///MACA LONGA
 5176:  dano:=RandomInt(23) + 14;		 ///MARTELO DE GUERRA
 5126:  dano:=RandomInt(25) + 4;		 ///MACA DE GUERRA
 3918:  dano:=RandomInt(25) + 18;		 ///BARDICHE
 5182:  dano:=RandomInt(26) + 20;		 ///ALABARDA
 5122:  dano:=RandomInt(18) + 8;		 ///LANÇA PEQUENA
 3939:  dano:=RandomInt(20) + 3;		 ///LANÇA GRANDE
 5124:  dano:=RandomInt(22) + 16;		 ///GARFO DE GUERRA
 3934:  dano:=RandomInt(18) + 3;		 ///ESPADA LARGA
 5184:  dano:=RandomInt(17) + 7;		 ///CUTELO (ARMA MENOR Q KATANA)
 3921:  dano:=RandomInt(4)+3;			 ///ADAGA
 5118:  dano:=RandomInt(20)+3;			 ///KATANA
 5121:  dano:=RandomInt(20)+3;			 ///KOPESH
 5045:  dano:=RandomInt(17)+11;			 ///CIMITARRA
 5049:  dano:=RandomInt(20)+16;			 ///BASTARDA
 3717:  dano:=RandomInt(6)+2;			 ///PICARETA
 5110:  dano:=RandomInt(4)+2;			 ///PUNHAL
 3778:  dano:=RandomInt(8)+2;			 ///FACA AÇOUGUEIRO
 5043:  dano:=RandomInt(8)+14;			 ///PORRETE
 3719:  dano:=RandomInt(26)+6;			 ///TRIDENTE
 3568:  dano:=RandomInt(25)+5;			 ///CAJADO NEGRO
 5113:  dano:=RandomInt(16)+8;			 ///CAJADO TORCIDO
 3722:  dano:=RandomInt(15)+8;			 ///BASTAO
 3713:  dano:=RandomInt(10)+1;			 ///CAJADO DO PASTOR
 default: dano:=RandomInt(3);
endcase


if(armalumber == 1)

dano := dano - randomdiceroll("1d5") + cint(GetEffectiveSkill(attacker, SKILLID_TACTICS) / 15) + cint(GetEffectiveSkill(attacker, SKILLID_ANATOMY) / 25) + randomint(cint(GetEffectiveSkill(attacker, SKILLID_LUMBERJACKING) / 20) )+cint(GetEffectiveSkill(attacker, SKILLID_LUMBERJACKING) / 50) + 3;
else

dano := dano - randomdiceroll("1d5") + cint(GetEffectiveSkill(attacker, SKILLID_TACTICS) / 15) + cint(GetEffectiveSkill(attacker, SKILLID_ANATOMY) / 25);
endif

return dano;

endfunction

