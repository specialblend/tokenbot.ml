open Contract;

let sender = txn => txn.sender;
let recipients = txn => txn.recipients;
let everyone = txn => [txn.sender, ...txn.recipients];
