open Candy;
open Contract;

let player1 = Profile.Mock.gen(~id="player1", ());
let player2 = Profile.Mock.gen(~id="player2", ~tz_offset=Some(12345.), ());
let player3 =
  Profile.Mock.gen(
    ~id="player3",
    ~tz_offset=Some(12345.),
    ~cake_month=Some(12),
    ~cake_day=Some(21),
    (),
  );

let txn = {
  id: Cuid.generate(),
  time: Unix.time(),
  msg: "test",
  sender: player1,
  recipients: [player2, player3],
};

let res = Clerk.Collector.use(txn);

res ->> List.map((mtxn: mtxn) => {print_endline(mtxn.id)});

//let db = Redis.connect({host: "localhost", port: 6379});
//
//switch (db->Profile.DB.scan("player3")) {
//| Some(player3) =>
//  print_endline(player3.id);
//  print_endline(player3.name);
//  print_endline((player3.tz_offset *? 0.)->Float.to_string);
//| None => print_endline("player3 not found")
//};
