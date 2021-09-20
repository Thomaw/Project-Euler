open Big_int

let mult((a, b), (c, d)) ((w, x), (y, z))=
  ((add_big_int (mult_big_int a w) (mult_big_int b y), 
    add_big_int (mult_big_int a x) (mult_big_int b z)),
   (add_big_int (mult_big_int c w) (mult_big_int d y), 
    add_big_int (mult_big_int c x) (mult_big_int d z)));;
  
let rec expt a  n =
  if n = 1 then
    a
  else if n mod 2 = 0 then
    expt (mult a a) (n / 2)
  else
    mult a (expt a (n - 1));;

let fib n =
  if n = 0 then
    zero_big_int
  else
    let ((_, a), (_, _)) = 
      expt((unit_big_int, unit_big_int), 
           (unit_big_int, zero_big_int)) n in
    a;;

let main max_len =
  let rec loop n =
    if String.length(string_of_big_int(fib n)) >= max_len then
      n
    else
     loop (succ n) in
  loop 0;;

let () =
  Printf.printf "%d\n" (main 1000)
