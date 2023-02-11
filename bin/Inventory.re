open Contract;
open List;
open Sugar;
open Redis;

let scope = prefix("inventory");

let getQty = (db, profile_id, token) => {
  let key = token->prefix(profile_id)->scope;
  switch (db->get(key)) {
  | Some(s) => s->int_of_string
  | None => 0
  };
};

let setQty = (db, profile_id, token, qty) => {
  let key = token->prefix(profile_id)->scope;
  db->set(key, qty->Int.to_string);
};

let modQty = (db, profile_id, token, fn) => {
  let qty = db->getQty(profile_id, token);
  db->setQty(profile_id, token, fn(qty));
};

let scan = (~tokens=Tokens.all_tokens, db, profile_id) => {
  let scanToken = token => {
    let qty = db->getQty(profile_id, token);
    {token, qty};
  };
  tokens ->> map(scanToken);
};
