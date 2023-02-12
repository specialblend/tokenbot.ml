open Contract;
open Candy;
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

let stackFx = (~qty, stats, fx) => {
  open Int;
  let update =
    switch (fx) {
    | Curse(amt) => modCurse(add(amt * qty))
    | Luck(amt) => modLuck(add(amt * qty))
    | Wealth(amt) => modWealth(add(amt * qty))
    };
  update(stats);
};

let stackItem = (stats, item) => {
  let {token, qty} = item;
  token->fx->fold(stackFx(~qty), stats);
};

let calc = items => {
  items->fold(stackItem, init_stats);
};
