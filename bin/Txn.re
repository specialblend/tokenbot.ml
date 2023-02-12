open Contract;

let sender = txn => txn.sender;
let recipients = txn => txn.recipients;
let everyone = txn => [txn.sender, ...txn.recipients];

let give = (~cuid=Cuid.generate, ~qty=1, token, about, target: profile) => {
  {
    id: cuid(),
    target: target.id,
    item: {
      token,
      qty,
    },
    about,
  };
};
