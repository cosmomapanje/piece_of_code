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


(* 2 : number_in_month *)
val test_list = [(1,2,3), (2,3,4), (3,4,5), (3,2,4), (3,3,3), (3,2,3)]
fun number_in_month (m : (int * int * int) list, x : int) = 
  if null m
  then 0
  else if #2 (hd m) = x
  then 1 + number_in_month(tl m, x)
  else number_in_month(tl m, x)


(* 3 : number_in_months*)
fun number_in_months (m : (int * int * int) list, y : int list) =
  m

(* 4 : dates_in_month *)
fun dates_in_month (dl : (int * int * int) list, month : int) =
  if null dl
  then []
  else if #2 (hd dl) = month
  then hd dl :: dates_in_month(tl dl, month)
  else dates_in_month(tl dl, month)

(* 5 : dates_in_months *)
fun dates_in_months (m : (int * int * int) list, y : int list) =
  m

(* 6 : get_nth *)
val test_string = ["123", "234", "345", "456", "567", "678", "789", "890"]
fun get_nth (dl : string list, nth : int) =
  if null dl
  then ""
  else if nth = 1
  then hd dl
  else get_nth(tl dl, nth - 1)

(* 7 : date_to_string *)
fun date_to_string (dl : (int * int * int)) = 
  let val month_string = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
  in get_nth(month_string, #2 dl) ^ "-" ^ Int.toString(#1 dl) ^ "-" ^ Int.toString(#3 dl)
  end

(* 8 : number_before_reaching_sum *)
fun number_before_reaching_sum(sum : int, il : int list) =
  if null il
  then 0
  else if sum > 0
  then 1 + number_before_reaching_sum(sum - hd il, tl il)
  else 0

(* 9 : what_month *)
fun what_month (x : int) =
  let val month_list = [31,28,31,30,31,30,31,31,30,31,30,31]
	  val month_string = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
  in get_nth(month_string, number_before_reaching_sum(x, month_list))
  end

(* 10 : month_range *)
(* 11 : oldest *)
(* 12 : cumulative_sum *)
(* 13 : number_in_months_challenge / dates_in_months_challenge *)
(* 14 : reasonable_date*)
