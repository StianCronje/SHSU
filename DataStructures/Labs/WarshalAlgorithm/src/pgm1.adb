with Ada.Text_IO; use Ada.Text_IO;
with Unchecked_Conversion;
with gbmr;

procedure pgm1 is
   package someBMR is new gbmr(10, integer);
   use someBMR;

begin
      Put_Line("Hello World!");
      someBMR.add(5, 2);
end pgm1;


-- ask number nodes
-- prompt for values/names
-- can i talk to j, relationship loop
