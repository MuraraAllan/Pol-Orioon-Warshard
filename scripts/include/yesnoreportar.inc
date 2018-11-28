use uo;



function YesNo(me, prompt)



	var layout := array(

                        "page 0",

			"nodispose",

                        "gumppic 450 450 2070",

                        "button 480 525 2130 2129 1 0 1",

                        "button 550 525 2119 2120 1 0 0",

                        "text 480 480 502 0"

                       

	);


me.paralyzed := 1;
	var data := array(  prompt  );



	var res := SendDialogGump( me, layout, data );



	if (res)

		return 1;

	else

		return 0;

	endif



endfunction
