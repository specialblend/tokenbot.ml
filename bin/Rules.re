open Contract;
open Clock;
open Txn;
open List;
open Candy;

let give = (~qty=1, token, about, target: profile) => {
  {
    id: "",
    target: target.id,
    item: {
      token,
      qty,
    },
    about,
  };
};

let baseToken = (txn, res) => {
  txn->recipients->map(give("👍", "thanks"))->append(res);
};

let fridayBonus = (txn, res) => {
  txn
  ->everyone
  ->filter(isFriday(txn.time))
  ->map(give("🍻", "TGIF"))
  ->append(res);
};

let rules = [baseToken, fridayBonus];
