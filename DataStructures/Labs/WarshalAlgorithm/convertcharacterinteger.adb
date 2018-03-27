with Ada.Text_IO; use Ada.Text_IO;  -- read and write characters.
with Unchecked_Conversion;  -- standard package with every validated Ada translator

procedure ConvertCharacterInteger is
    -- To read and write 16 bit integers on the PC compiler.
    package MyInt_IO is new Ada.Text_IO.Integer_IO(integer);
    use MyInt_IO;

    -- instantiations to convert between integer and character formats, 16 bits versus 8 bits.
    function integerToCharacter is new Unchecked_Conversion(Integer, Character);
    function characterToInteger is new Unchecked_Conversion(Character, Integer);

    c1, c2: Character;
    int1, int2: Integer;

    begin
       c1 := 'A';
       -- int1 := c1;  --error in Ada, strongly typed, suspects programmer error.
       int1 := characterToInteger( c1 );  -- Signal compiler to allow conversion.
       put(" int1 = "); put(int1,4); put("  ");
       put("c1 = "); put(c1); new_line(2);

       int2 := 66;
       -- c2 := int2;  -- error
       c2 := integerToCharacter(int2);
       put(" int2 = "); put(int2,4); put("  ");
       put("c2 = "); put(c2); new_line(2);


end ConvertCharacterInteger;
