open Contract;

let sender = txn => txn.sender;
let recipients = txn => txn.recipients;
let everyone = txn => [txn.sender, ...txn.recipients];

module Mtx = {
  let fillId = (~cuid=Cuid.generate, mtx: mtxn) => {
    switch (mtx.id) {
    | "" => {...mtx, id: cuid()}
    | _ => mtx
    };
  };
};
