do 'declare _ text; begin _:=''''''''; raise notice ''%'' , _;end';

do language 'plpgsql' $asdf_asdf$ declare bla text;_ text; begin

bla := 'evilpostgres'' $abc$ /* --;; ';
null;
_ := '''';

raise 
notice 
'%' 
, 
bla;

raise notice'%',_;


 end $asdf_asdf$;