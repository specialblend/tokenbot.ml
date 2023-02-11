open List;
open Pipe;

module Collector = {
  let use = (~rules, txn) => {
    let stack = (res, rule) => rule(txn, res);
    rules ->> fold(stack, []);
  };
};
