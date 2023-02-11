open Contract;
open List;
open Sugar;

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
  let f =
    switch (fx) {
    | Curse(amt) => modCurse(add(amt * qty))
    | Luck(amt) => modLuck(add(amt * qty))
    | Wealth(amt) => modWealth(add(amt * qty))
    };
  f(stats);
};

let stackItem = (~scanFx, stats, item) => {
  let {token, qty} = item;
  let fx = scanFx(token);
  fx->fold_left(stackFx(~qty), stats);
};

let calc = (~scanFx, items) => {
  items->fold_left(stackItem(~scanFx), init_stats);
};
