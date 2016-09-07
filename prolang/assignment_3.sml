(* 1 : only_lowercase *)
val only_lowercase =
  List.filter (fn x => Char.isLower(String.sub(x, 0)))

(* 2 : longest_string1 *)
val longest_string1 =
	foldl (fn (x, y) => if String.size x > String.size y then x else y) ""

(* 3 : longest_string2 *)
val longest_string2 =
	foldl (fn (x, y) => if String.size x < String.size y then y else x) ""

(* 4 : longest_string_helper longest_string3 longest_string4 *)
(* longest_string_helper : (int * int -> bool) -> string list -> string *)
(*
val longest_string_helper = (fn (f, x, y) => if (f (String.size x) (String.size y)) then x else y)
val longest_string3 = 0
val longest_string4 = 0

val ver = (fn (x, y) => foldl y "" x)
*)
(* 5 : longest_lowercase *)
(*
fun add1 x = 1 + x
val test = ~ o add1
val longest_lowercase = (fn x = foldl String.sub(x, 0)
*)

(* 6 : rev_string *)
val rev_string =
    (fn x => implode (rev (explode x))) o (fn x => String.map (Char.toUpper) x)
