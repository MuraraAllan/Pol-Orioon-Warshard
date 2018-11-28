var mrcspawn_cfg := ReadConfigFile("::mrcspawn");
var itemconfig := ReadConfigFile(":*:itemdesc");

function RestockInventory (merchanttype, byref inventory)
	UnloadConfigFile ("::mrcspawn");
	var mrcspawn_cfg := ReadConfigFile("::mrcspawn");

	foreach item in ListRootItemsInContainer (inventory)
		DestroyItem (item);
	endforeach

	foreach productgroup in ProductGroups (mrcspawn_cfg, merchanttype)
		Restock (mrcspawn_cfg, inventory, productgroup);
	endforeach

	foreach item in ListRootItemsInContainer ( inventory )
		if ( item.quality )
			item.quality := randomint (50) + 50;
			item.hp := item.maxhp;
		endif
	endforeach
endfunction

function ProductGroups (byref mrcspawn_cfg, mtype)
	var mtype_elem := FindConfigElem ( mrcspawn_cfg, mtype );
	if (!mtype_elem)
		return 0;
	endif

	return GetConfigStringArray (mtype_elem, "Sells");
endfunction

function Restock (byref mrcspawn_cfg, byref inventory, byref productgroup)

	var pg_elem := FindConfigElem (mrcspawn_cfg, productgroup);
	foreach itemstr in GetConfigStringArray (pg_elem, "Item")
		sleepms(100);
		SpawnItem (inventory, itemstr);
	endforeach

	foreach itemstr in GetConfigStringArray( pg_elem, "Multibag" )
		sleepms(100);
		var baglist := splitwords(itemstr);
		var spawnelem := FindConfigElem(mrcspawn_cfg, baglist[1] );
		var desc := spawnelem.desc;
		var stuffarray := GetConfigStringArray( spawnelem, "Item" );
		SpawnMultiBag( inventory, desc, stuffarray, cint(baglist[2]) );
	endforeach

endfunction

function SpawnItem (byref inventory, itemstr)

	var ii := SplitWords( itemstr );
	var objtype := ii[1];
	if (cint(objtype))
		objtype := cint(objtype);
	else
		objtype := GetObjtypeByName (objtype);
	endif

	var count := CInt(ii[2]);
	CreateItemInInventory (inventory, objtype, count);

endfunction

function SpawnMultiBag (byref inventory, desc, stuffarray, number)

        
	if (!itemconfig)
		return;
	endif

	for i := 1 to number
                var UOBJ_BAG;
		var regbag := CreateItemInContainer (inventory,	UOBJ_BAG, 1);
		if (!regbag)
			return;
		endif

		regbag.name := desc;
		regbag.sellprice := 10;

		foreach item in stuffarray
			var parms := splitwords(item);

			var elem := FindConfigElem(itemconfig,cint(parms[1]));
			if (!elem)
				return;
			endif
			var itemprice := GetConfigInt(elem,"vendorsellsfor");
			if (!itemprice)
				return;
			endif

			var it := CreateItemInContainer(regbag,cint(parms[1]),cint(parms[2]));
			if (!it)
				return;
			endif
			regbag.sellprice := regbag.sellprice + ( itemprice * it.amount );
		endforeach
	endfor
endfunction

function ModifyPCSellList(merchanttype, backpack)
  var backpackitems := ListRootItemsInContainer(backpack);
  var prodgroups    := FindConfigElem(mrcspawn_cfg, merchanttype);
  var buys          := GetConfigStringArray(prodgroups, "Buys");
  var nobuys        := GetConfigStringArray(prodgroups, "NoBuys");
  var iteminit := 0;
  var itemmark, normcost, normsell, percentage;
  if(buys.size() >= 1)
    iteminit := -1;
    itemmark := 0;
    prodgroups := buys;
  elseif(nobuys.size() >= 1)
    iteminit := 0;
    itemmark := -1;
    prodgroups := nobuys;
  endif
  foreach item in backpackitems
    item.buyprice := iteminit;
  endforeach
  var buynobuyable := { };
  var objtype;
  var counter := 0;
  if(prodgroups.size())
    foreach prodgroup in prodgroups
      foreach itemstr in GetConfigStringArray(FindConfigElem(mrcspawn_cfg, prodgroup), "Item")
        itemstr := SplitWords(itemstr);
        objtype := itemstr[1];
        if(CInt(objtype))
          objtype := CInt(objtype);
        else
          objtype := GetObjtypeByName(objtype);
        endif
        buynobuyable.append(objtype);
      endforeach
    endforeach
    if(buynobuyable.size())
      foreach item in backpackitems
        if((item.objtype in buynobuyable) && (!item.newbie))
          counter := counter + 1;
          if(itemmark == 0)
            if(!item.quality)
              item.quality := 1;
            endif
            normcost := itemconfig[item.objtype].VendorBuysFor;
            normsell := itemconfig[item.objtype].VendorSellsFor;
	        normcost := normcost * item.quality;
	        normsell := normsell * item.quality;
            percentage := ((item.hp * 10) / item.maxhp);
            if(percentage)
              normcost := CInt((normcost * percentage) / 10);
              normsell := CInt((normsell * percentage) / 10);
              item.buyprice := normcost;
              item.sellprice := normsell;
            else
              item.buyprice := itemmark;
            endif
          else
            item.buyprice := itemmark;
          endif
        endif
      endforeach
    endif
  endif
  return counter;
endfunction


