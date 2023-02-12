open Candy;
open Stream;
open Redis_sync.Client;

let use = (conn, channel) => {
  let events = stream(conn);
  subscribe(conn, [channel]);

  let handleMsg =
    fun
    | `Bulk(Some(msg)) when msg == channel => None
    | `Bulk(Some(msg)) when msg == "subscribe" => None
    | `Bulk(Some(msg)) when msg == "message" => None
    | `Bulk(Some(msg)) => Some(msg)
    | _ => None;

  let read = () => {
    events ->> next ->> keep(handleMsg);
  };

  read;
};
