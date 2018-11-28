const MONEY := 0xeed;

function CheckMoney (character)
   var totalmoney := 0, backpack := EnumerateItemsInContainer (character.backpack);
   foreach item in backpack
      if (item.objtype == MONEY)
        totalmoney := totalmoney + GetAmount(item);
      endif
   endforeach

   return totalmoney;
endfunction

function Takecash (character, cash)
var totalmoney := 0, backpack := EnumerateItemsInContainer (character.backpack);
   foreach item in backpack
      if (item.objtype == MONEY)
         SubtractAmount (item, cash);
      endif
   endforeach

   return totalmoney;
endfunction