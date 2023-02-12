open Candy;
open Stream;
open Redis_sync.Client;

let watch = (conn, channel) => {
  let events = stream(conn);
  subscribe(conn, [channel]);

  let doMsg =
    fun
    | `Bulk(Some("subscribe")) => None
    | `Bulk(Some("message")) => None
    | `Bulk(Some(msg)) when msg == channel => None
    | `Bulk(Some(msg)) => Some(msg)
    | _ => None;

  () => events ->> next ->> keep(doMsg);
};
