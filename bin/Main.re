open Candy;
open List;

let conn = Redis_sync.Client.connect({host: "localhost", port: 6379});
let db = Redis_sync.Client.connect({host: "localhost", port: 6379});
let read = Worker.watch(conn, "example_channel");

while (true) {
  read() ->> map(print_endline) ->> ignore;
  let _profile = db->Profile.DB.scan("player1");
  let items = db->Inventory.DB.scan("player1");
  let stats = Stats.calc(items);
  let _scores = Scores.calc(stats, items);
  db->Inventory.DB.modQty("player1", "👍", Int.add(1))->ignore;
  let qty = db->Inventory.DB.getQty("player1", "👍");
  print_endline("👍: " ++ Int.to_string(qty));
};
