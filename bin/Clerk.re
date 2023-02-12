open List;
open Candy;

module Collector = {
  let use = (~rules, txn) => {
    let stack = (res, rule) => rule(txn, res);
    rules ->> fold(stack, []);
  };
};
