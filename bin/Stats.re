open Contract;
open List;
open Pipe;
open Tokens;

let init_stats = {curse: 0, luck: 0, wealth: 0};

let modCurse = (fn, stats) => {
  {...stats, curse: fn(stats.curse)};
};

let modLuck = (fn, stats) => {
  {...stats, luck: fn(stats.luck)};
};

let modWealth = (fn, stats) => {
  {...stats, wealth: fn(stats.wealth)};
};

let stackEff = (~qty, stats, eff) => {
  open Int;
  let aff =
    switch (eff) {
    | Curse(amt) => modCurse(add(amt * qty))
    | Luck(amt) => modLuck(add(amt * qty))
    | Wealth(amt) => modWealth(add(amt * qty))
    };
  aff(stats);
};

let stackItem = (stats, item) => {
  let {token, qty} = item;
  token->fx->fold_left(stackEff(~qty), stats);
};

let calc = items => {
  items->fold_left(stackItem, init_stats);
};
