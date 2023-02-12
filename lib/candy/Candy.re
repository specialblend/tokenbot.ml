let (|.) = (|>); // (->) candy first
let (->>) = (|>); // (->>) candy last

let ( *? ) = (opt, def) => {
  switch (opt) {
  | Some(opt) => opt
  | _ => def
  };
};

let (->?) = (opt, fn) => Option.map(fn, opt);

let fold = List.fold_left;

let keep = (fn, ls) => {
  let stack = (res, el) => {
    switch (fn(el)) {
    | Some(el) => [el, ...res]
    | _ => res
    };
  };
  ls ->> fold(stack, []);
};

let pair = (x, y) => (x, y);
