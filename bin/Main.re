open Clerk;
open Contract;
open List;
open Pipe;

let player1 = Profile.Mock.gen(~id="player1");
let player2 = Profile.Mock.gen(~id="player2");

open Inventory.DB;

let db = Redis.connect({host: "localhost", port: 6379});

db->modQty("player1", "👍", Int.add(1));
db->modQty("player1", "🍕", Int.add(1));

let printItem = item => {
  let {token, qty} = item;
  print_endline(token ++ ": " ++ qty->Int.to_string);
};

let collect = Collector.use;

db->scan("player1") ->> map(printItem);
