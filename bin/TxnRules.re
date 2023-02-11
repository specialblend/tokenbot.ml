open Contract;
open Clock;
open Txn;
open List;
open Pipe;

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

let baseToken = txn => {
  txn->recipients->map(give("👍", "thanks"))->append;
};

let fridayBonus = txn => {
  txn
  ->everyone
  ->filter(isFriday(txn.time))
  ->map(give("🍻", "TGIF"))
  ->append;
};

let rules = [baseToken, fridayBonus];
