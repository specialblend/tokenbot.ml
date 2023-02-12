open Contract;
open Candy;

let init_scores = {base: 0, bonus: 0, penalty: 0, total: 0};

let stack = (~points=Tokens.points, base, item) => {
  let {token, qty} = item;
  base + token->points * qty;
};

let calc = (~points=Tokens.points, stats, items) => {
  let {wealth, curse, _} = stats;
  let base = items->fold(stack(~points), 0);
  let bonus = wealth * base / 100;
  let penalty = curse * base / 100;
  let total = base + bonus - penalty;
  {base, bonus, penalty, total};
};
