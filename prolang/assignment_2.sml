(* Dan Grossman, CSE341 Spring 2013, HW2 Provided Code *)

(* if you use this function to compare two strings (returns true if the same
   string), then you avoid several of the functions in problem 1 having
   polymorphic types that may be confusing *)
fun same_string(s1 : string, s2 : string) =
    s1 = s2

(* put your solutions for problem 1 here *)
(* a *)
fun remove_option(x1 : string, x2 : string list) =
  if null x2
  then NONE
  else let fun remove_option_nonempty(s : string, sl : string list) =
			 if null sl
			 then []
			 else
				 if same_string(s, hd sl)
				 then remove_option_nonempty(s, tl sl)
				 else hd sl :: remove_option_nonempty(s, tl sl)
	   in SOME(remove_option_nonempty(x1, x2))
	   end
(* b *)
(* c *)
(* d *)
(* you may assume that Num is always used with values 2, 3, ..., 10
   though it will not really come up *)
datatype suit = Clubs | Diamonds | Hearts | Spades
datatype rank = Jack | Queen | King | Ace | Num of int 
type card = suit * rank

datatype color = Red | Black
datatype move = Discard of card | Draw 

exception IllegalMove

(* put your solutions for problem 2 here *)
