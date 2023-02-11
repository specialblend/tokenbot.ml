open Sugar;
open List;
open Inventory;
open Contract;

let db = Redis.connect({host: "localhost", port: 6379});

db->modQty("player1", "👍", Int.add(1));
db->modQty("player1", "🍕", Int.add(1));

let printItem = item => {
  let {token, qty} = item;
  print_endline(token ++ ": " ++ qty->Int.to_string);
};

db->scan("player1") ->> map(printItem);
