open Contract;
open List;
open Sugar;

module DB = {
  let getQty = (~db, profile_id, token) => {
    0; // todo
  };
  let setQty = (~db, profile_id, token, qty) => {
    (); // todo
  };

  let updateQty = (~db, profile_id, token, doQty) => {
    let qty = getQty(~db, profile_id, token);
    setQty(~db, profile_id, token, doQty(qty));
  };

  let scan = (~tokens, ~db, profile_id) => {
    let scanToken = token => {
      let qty = getQty(~db, profile_id, token);
      {token, qty};
    };
    tokens ->> map(scanToken);
  };
};
