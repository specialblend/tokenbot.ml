open Contract;
open Clock;
open Txn;
open List;
open Candy;

let baseToken = (txn, res) => {
  txn ->> recipients ->> map(give("👍", "thanks")) ->> append(res);
};

let fridayBonus = (txn, res) => {
  txn
  ->> everyone
  ->> filter(isFriday(txn.time))
  ->> map(give("🍻", "TGIF"))
  ->> append(res);
};

let rules = [baseToken, fridayBonus];
