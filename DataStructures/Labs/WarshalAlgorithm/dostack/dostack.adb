-- in file Dostack.adb
WITH Ada.Text_IO;
USE Ada.Text_IO;
PROCEDURE Dostack IS
   PACKAGE MyInt_IO IS NEW Ada.Text_IO.Integer_IO(Integer);
   USE MyInt_IO;
   M : Integer;

   Max : CONSTANT                             := 100; -- Declare the stack
   S   :          ARRAY (1 .. Max) OF Integer;
   Top :          Integer RANGE 0 .. Max      := 0;

   PROCEDURE Push (
         X : Integer) IS
   BEGIN
      Top := Top + 1;
      S(Top) := X;
   END Push;

   PROCEDURE Pop (
         X :    OUT Integer) IS
   BEGIN
      X := S(Top);
      Top := Top - 1;
   END Pop;

BEGIN
   Top := 0; --initialize top of stack to empty
   FOR I IN 1..4 LOOP
      Put("enter an integer");
      Get(M);
      Push(M);
   END LOOP;

   FOR I IN 1..4 LOOP
      Put("result of pop");
      Pop(M);
      Put(M);
      New_Line;
   END LOOP;
END Dostack;
