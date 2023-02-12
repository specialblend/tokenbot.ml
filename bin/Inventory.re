open Contract;
open List;
open Candy;

module DB = {
  open Redis;

  let scope = prefix("inventory");

  let getQty = (db, profile_id, token) => {
    let key = scope(profile_id);
    db->hget(key, token) ->? int_of_string |? 0;
  };

  let setQty = (db, profile_id, token, qty) => {
    let key = scope(profile_id);
    db->hset(key, token, Int.to_string(qty));
  };

  let modQty = (db, profile_id, token, fn) => {
    let qty = db->getQty(profile_id, token);
    db->setQty(profile_id, token, fn(qty));
  };

  let scan = (db, profile_id) => {
    let key = scope(profile_id);
    let stack = ((token, qty)) => {
      let qty = int_of_string(qty);
      {token, qty};
    };
    db->hgetall(key) ->> map(stack);
  };
};
