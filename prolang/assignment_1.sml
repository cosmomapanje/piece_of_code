(* date is a type (int * int * int) *)
(* first part is day, second part is month, third part is year *)
(* a year and a month is between 1 and 12, a day no greater than 31 *)


(* 1 : is_older *)
fun is_older ((d1 : int, m1 : int, y1 : int), (d2 : int, m2 : int, y2 : int)) = 
  if y1 < y2
  then true
  else if y1 > y2
  then false
  else
      if m1 < m2
      then true
      else if m1 > m2
      then false
      else
	  if d1 < d2
	  then true
	  else false


(* 2 : number_in_number *)
val test_list = [(1,2,3), (2,3,4), (3,4,5), (3,2,4), (3,3,3), (3,2,3)]
fun number_in_month (m : (int * int * int) list, x : int) = 
  if null m
  then 0
  else if #2 (hd m) = x
  then 1 + number_in_month(tl m, x)
  else number_in_month(tl m, x)


(* 3 : number_in_months*)
fun number_in_months (m : (int * int * int) list, y : int list) =
  1

fun dates_in_month (m : (int * int * int) list, y : int) =
  m

fun dates_in_months (m : (int * int * int) list, y : int list) =
  m
