datatype fruit =
		 Peach
	   | Apple
	   | Pear
	   | Lemon
	   | Fig

datatype tree =
		 Bud
		 | Flat of fruit * tree
		 | Split of tree * tree

fun flat_only(Bud)
    = true
  | flat_only(Flat(f,t))
	= flat_only(t)
  | flat_only(Split(s,t))
	= false

fun split_only(Bud)
    = true
  | split_only(Flat(f,t))
	= false
  | split_only(Split(s,t))
	= if split_only(s)
	  then split_only(t)
	  else false

fun contains_fruit(Bud)
  = false
  | contains_fruit(Flat(f, t))
	= true
  | contains_fruit(Split(s, t))
	= if contains_fruit(s)
	  then true
	  else contains_fruit(t)

fun less_than(x, y)
  = x < y

fun larger_of(n, m)
  = if less_than(n, m)
	then m
	else n

fun height(Bud)
  = 0
  | height(Flat(f, t))
	= 1 + height(t)
  | height(Split(s, t))
	= 1 + larger_of(height(s), height(t))


(* Peach | Apple | Pear | Lemon | Fig *)
fun eq_fruit(Peach, Peach)
  = true
  | eq_fruit(Apple, Apple)
	= true
  | eq_fruit(Pear, Pear)
	= true
  | eq_fruit(Lemon, Lemon)
	= true
  | eq_fruit(Fig, Fig)
	= true
  | eq_fruit(x, y)
	= false

fun subst_in_tree(n, a, Bud)
  = Bud
  | subst_in_tree(n, a, Flat(f, t))
	= if eq_fruit(f, a)
	  then Flat(n, subst_in_tree(n, a, t))
	  else Flat(a, subst_in_tree(n, a, t))
  | subst_in_tree(n, a, Split(s, t))
	= Split(subst_in_tree(n, a, s),
			subst_in_tree(n, a, t))

fun occurs(a, Bud)
  = 0
  | occurs(a, Flat(f, t))
	= if eq_fruit(a, f)
	  then 1 + occurs(a, t)
	  else occurs(a, t)
  | occurs(a, Split(s, t))
	= occurs(a, s) + occurs(a, t)
