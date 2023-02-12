open List;
open Candy;

module Collector = {
  let use = (~rules=Rules.rules, txn) => {
    let stack = (res, rule) => rule(txn, res);
    rules ->> fold(stack, []);
  };
};
