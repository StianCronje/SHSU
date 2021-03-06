generic  -- You may modify this as required but observe the spirit.
	type SortElement is private;  -- An element J (or K) of the partial ordering J < K processed
             -- by the topological sort.  J and K represent objects in the partial ordering.

**	with function get(Job:  out SortElement) return SortElement;  // Reads J or K.
**	with procedure put(Job:  in SortElement);  // Print the value of J or K.


package GenericTopologicalSort is

	--  additional procedures/functions to export if required
end GenericTopologicalSort;

package body GenericTopologicalSort is
	-- This should read (get) the relations and print (put) the results.
type Node;
type NodePointer is access Node;
type Node is tagged record

	Next:	NodePointer;
end record;

type JobElement is record
	Count:  Integer := 0;  -- This field should be used for counting and as queue links.
	Top:	NodePointer;
end record;

SortStructure:  Array(SortElement) of JobElement;
-- other declarations


	begin -- Program to obtain the relations in the partial ordering,
          -- sort the jobs, and print results;
end TopologicalSort;
end GenericTopologicalSort;

with GenericTopologicalSort;
procedure Main is

	type NameType is (Mary, Joe, Tom, Bob, Sara, Julie, Larry, Sam);

	package NameTypeIO is new Ada.Text_IO.Enumeration_IO(NameType);
	use NameTypeIO;




	package NameTopologicalSort is new
		GenericTopologicalSort(NameType, get, put);
	use NameTopologicalSort;
begin
-- rest of program
end Main;
