open Redis_sync;
include Client;

let prefix = (p, s) => p ++ ":" ++ s;
let float = float_of_string;
let int = int_of_string;
