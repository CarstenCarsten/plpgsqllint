-- Single line comments will go to the end of the line
-- exceptions:
-- * if there is already an opened multi line comment
-- * if there is already an opened multi line string


-- multi line comment comments out single line comment 
do $$
declare
begin
/*
raise notice 'hello world';
-- */ raise notice 'this is a message';
end;
$$ language plpgsql;

do $$
declare
xyz text;
begin
xyz := $test$
raise notice 'hello world';
-- $test$; raise notice 'this is a message';
end;
--$$ language plpgsql;



do $$
declare
begin
raise notice 'hello world';
-- */ raise notice 'this is a message';
end;
$$ language plpgsql;


-- single line comment can comment out multi line comment start 
do $$
declare
begin
--/*
raise notice 'hello world';
--*/ raise notice 'this is a message';
end;
$$ language plpgsql;


-- multi line comment comments out start of multi line string
do $$
declare
bla text;
begin
/*
bla := $abc$
raise notice 'hello world';
*/
$abc$; raise notice 'this is a message';
raise notice '%' , bla;
end;
$$ language plpgsql;

-- multi line comment comments out end of multi line string
do $$
declare
bla text;
begin
bla := $abc$
/*
raise notice 'hello world';

$abc$; raise notice 'this is a message';
*/
raise notice '%' , bla;
end;
$$ language plpgsql;
