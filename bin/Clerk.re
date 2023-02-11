open Sugar;

module Collector = {
  let use = (~rules, txn) => {
    rules ->> fold((res, rule) => rule(txn, res), []);
  };
};
