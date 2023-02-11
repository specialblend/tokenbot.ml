open Sugar;

module Collector = {
  let stack = (res, rule) => rule(txn, res)
  let use = (~rules, txn) => {
    rules->fold(stack, []);
  };
};
