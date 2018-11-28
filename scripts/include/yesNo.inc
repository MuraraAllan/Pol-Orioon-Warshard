use uo;



function YesNo(me, prompt)



	var layout := array(

                        "page 0",

			"nodispose",

                        "gumppic 0 0 2070",

                        "button 30 75 2130 2129 1 0 1",

                        "button 90 75 2119 2120 1 0 0",

                        "text 40 30 502 0"

                       

	);



	var data := array(  prompt  );

          

	var res := SendDialogGump( me, layout, data );



	if (res)

		return 1;

	else

		return 0;

	endif



endfunction


function SimNao(quem,msg)
var xxxx:=array(
"page 0",
"nodispose",
"text 18 20 77 0",
"text 10 40 77 2",
"text 10 70 77 2",
"text 10 100 77 2",
"button 45 50 2130 2129 1 0 1",
"button 125 50 2119 2120 1 0 0"
);

var dddd:={
Cstr(msg),
"",
"",
""
};

var res:=SendDialogGump(quem, xxxx, dddd);

	if (res)

		return 0;

	else

		return 1;

	endif
endfunction 