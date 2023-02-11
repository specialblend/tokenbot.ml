open Contract;
open List;
open Pipe;
open Redis;

let scope = prefix("inventory");

let getQty = (db, profile_id, token) => {
  let key = profile_id->scope;
  switch (db->hget(key, token)) {
  | Some(qty) => int_of_string(qty)
  | None => 0
  };
};

let setQty = (db, profile_id, token, qty) => {
  let key = profile_id->scope;
  db->hset(key, token, qty->Int.to_string);
};

let modQty = (db, profile_id, token, fn) => {
  let qty = db->getQty(profile_id, token);
  db->setQty(profile_id, token, fn(qty));
};

let scan = (db, profile_id) => {
  let key = profile_id->scope;
  let stack = ((token, qty)) => {
    let qty = int_of_string(qty);
    {token, qty};
  };
  db->hgetall(key) ->> map(stack);
};
