let (|.) = (|>); // (->) pipe first
let (->>) = (|>); // (->>) pipe last

// unwrap option or return fallback
let (|?) = (opt, def) => {
  switch (opt) {
  | Some(opt) => opt
  | _ => def
  };
};

// map over option
let (->?) = (opt, fn) => Option.map(fn, opt);

let fold = (ls, fn, init) => List.fold_left(fn, init, ls);

// map over list, only keep items that are Some(_)
let keep = (fn, ls) => {
  let stack = (res, el) => {
    switch (fn(el)) {
    | Some(el) => [el, ...res]
    | _ => res
    };
  };
  ls->fold(stack, []);
};

// make 2 tuple
let pair = (x, y) => (x, y);
