open Contract;
open Clerk;
open List;
open Sugar;

let rules = TxnRules.rules;
let collect = Collector.use(~rules);

let player1 = {id: "player1", name: "player1", tz_offset: None};
let player2 = {id: "player2", name: "player2", tz_offset: None};
let player3 = {id: "player3", name: "player3", tz_offset: None};

let txn = {
  id: "test",
  time: Unix.time(),
  msg: "test msg",
  sender: player1,
  recipients: [player2, player3],
};

let result = collect(txn);

result
->> map(mtxn => {
      print_endline(mtxn.target);
      print_endline(mtxn.item.token);
      print_endline(mtxn.item.qty ->> Int.to_string);
      print_endline(mtxn.about);
    });

// print_endline(Profile.time(txn.time, player1).tm_wday |> Int.to_string);
