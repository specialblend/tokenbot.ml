open Redis_sync;
include Client;

let prefix = (p, s) => p ++ ":" ++ s;
