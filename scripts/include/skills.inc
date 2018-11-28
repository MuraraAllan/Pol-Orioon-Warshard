
function upparalchemy(player,dificuldade,skilll,skill,locked)
var quantidadeupar;


var rate := GetAttributeBaseValue(player,skilll);
if(getobjproperty(player,locked))
return;
endif



if((dificuldade + 80 < rate))
return;
endif
if(rate >= 1000)
SetAttributeBaseValue(player,skilll,1000);
return;
else



if(!getobjproperty(player,skilll))
setobjproperty(player,skilll,1);
else
setobjproperty(player,skilll,GetobjProperty(player,skilll) + 1);
endif
endif
 

if((getobjproperty(player,skilll) >= cint(rate / 15)))
eraseobjproperty(player,skilll);

var aaa := SetAttributeBaseValue(player,skilll, rate + 1);

endif


endfunction

function upparskill(player,dificuldade,skilll,skill)
var quantidadeupar;


var rate := GetAttributeBaseValue(player,skilll);




if((dificuldade + 80 < rate))
return;
endif
if(rate >= 1000)
SetAttributeBaseValue(player,skilll,1000);
return;
else



if(!getobjproperty(player,skilll))
setobjproperty(player,skilll,1);
else
setobjproperty(player,skilll,GetobjProperty(player,skilll) + 1);
endif
endif


if(getobjproperty(player,skilll) >= cint(rate / 40))
eraseobjproperty(player,skilll);

var aaa := SetAttributeBaseValue(player,skilll, rate + 1);

endif


endfunction


//funcao do rs////

function upparrs(player,dificuldade,skilll,evalprauppar,eval)

var quantidadeupar;


var rate := GetAttributeBaseValue(player,skilll);




if((dificuldade + 30 < rate))

return;
endif
if(rate >= 1000)
SetAttributeBaseValue(player,skilll,1000);
return;
endif
if(eval < evalprauppar)
return;
else



if(!getobjproperty(player,skilll))
setobjproperty(player,skilll,1);
else
setobjproperty(player,skilll,GetobjProperty(player,skilll) + 1);
endif
endif


if(getobjproperty(player,skilll) >= cint(rate / 25))
eraseobjproperty(player,skilll);

var aaa := SetAttributeBaseValue(player,skilll, rate + 1);

endif


endfunction

//funcao do mining////

function upparmining(player,dificuldade,skilll)

var quantidadeupar;


var rate :=GetAttributeBaseValue(player,skilll);



if(rate >= 1000)
SetAttributeBaseValue(player,skilll,1000);
return;
endif




if(!getobjproperty(player,skilll))
setobjproperty(player,skilll,1);
else
setobjproperty(player,skilll,GetobjProperty(player,skilll) + 1);
endif
 


if(dificuldade + 50 >= rate)
setobjproperty(player,skilll,GetobjProperty(player,skilll) + 2);
endif

if(getobjproperty(player,skilll) >= cint(rate / 20))
eraseobjproperty(player,skilll);

var aaa := SetAttributeBaseValue(player,skilll, rate + 1);

endif

endfunction

//funcao do mining////

function upparstats(player,dificuldade,skill,skilll)

var quantidadeupar;


var rate := GetAttributeBaseValue( player,skilll );






if(rate >= 1000)
SetAttributeBaseValue(player,skilll,1000);
return;
endif




if(!getobjproperty(player,skill))
setobjproperty(player,skill,1);
else
setobjproperty(player,skill,GetobjProperty(player,skill) + 1);
endif
 


if(getobjproperty(player,skill) >= cint(rate / 35))
eraseobjproperty(player,skill);

var aaa := SetAttributeBaseValue( player, skilll, rate + 1);

endif

endfunction


//////////////////funcao herding///////

function upparherd(player,dificuldade,skilll,skill)
var quantidadeupar;


var rate := GetAttributeBaseValue(player,skilll);




if((dificuldade + 80 < rate))
return;
endif
if(rate >= 1000)
SetAttributeBaseValue(player,skilll,1000);
return;
else



if(!getobjproperty(player,skilll))
setobjproperty(player,skilll,1);
else
setobjproperty(player,skilll,GetobjProperty(player,skilll) + 1);
endif
endif


if(getobjproperty(player,skilll) >= cint(rate / 30))
eraseobjproperty(player,skilll);

var aaa := SetAttributeBaseValue(player,skilll, rate + 1);

endif


endfunction

function upparmage(player,dificuldade,skilll,skill)
var quantidadeupar;


var rate := GetAttributeBaseValue(player,skilll);



if((dificuldade + 100 < rate))
return;
endif
if(rate >= 1000)
SetAttributeBaseValue(player,skilll,1000);
return;
else



if(!getobjproperty(player,skilll))
setobjproperty(player,skilll,1);
else
setobjproperty(player,skilll,GetobjProperty(player,skilll) + 1);
endif
endif


if(getobjproperty(player,skilll) >= cint(rate / 20))
eraseobjproperty(player,skilll);

var aaa := SetAttributeBaseValue(player,skilll, rate + 1);

endif


endfunction

function uppart(player,dificuldade,skilll,skill)
var quantidadeupar;


var rate := GetAttributeBaseValue(player,skilll);



if((dificuldade + 100 < rate))
return;
endif
if(rate >= 1000)
SetAttributeBaseValue(player,skilll,1000);
return;
else



if(!getobjproperty(player,skilll))
setobjproperty(player,skilll,1);
else
setobjproperty(player,skilll,GetobjProperty(player,skilll) + 1);
endif
endif


if(getobjproperty(player,skilll) >= cint(rate / 50))
eraseobjproperty(player,skilll);

var aaa := SetAttributeBaseValue(player,skilll, rate + 1);

endif


endfunction