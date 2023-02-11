open Contract;
open List;
open Sugar;
open Redis;

let scope = prefix("inventory");

let getQty = (db, profile_id, token) => {
  let key = profile_id->scope;
  switch (db->hget(key, token)) {
  | Some(s) => s->int_of_string
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

let read = (db, profile_id) => {
  let key = profile_id->scope;
  db->hgetall(key) ->> map(((token, q)) => {token, qty: q->int_of_string});
};

let scan = (~tokens=Tokens.all_tokens, db, profile_id) => {
  let scanToken = token => {
    let qty = db->getQty(profile_id, token);
    {token, qty};
  };
  tokens ->> map(scanToken);
};
