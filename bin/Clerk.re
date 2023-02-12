open Candy;
open Contract;
open List;

module Collector = {
  let use = (~rules=Rules.rules, txn) => {
    let stack = (res, rule) => rule(txn, res);
    rules ->> fold(stack, []);
  };
};

module Distributor = {
  let use = (~db, mtxns) => {
    let doMtx = mtx => {
      let {target, item: {token, qty}, _} = mtx;
      db->Inventory.DB.modQty(target, token, Int.add(qty));
    };
    mtxns ->> map(doMtx);
  };
};
