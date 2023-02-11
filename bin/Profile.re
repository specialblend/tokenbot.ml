open Contract;
open Pipe;

let time = (now, profile) => {
  switch (profile.tz_offset) {
  | Some(offset) => Unix.gmtime(now +. offset)
  | None => Unix.localtime(now)
  };
};

module DB = {
  open Redis;

  let scope = prefix("profile");

  let scan = (db, pid) => {
    let key = scope(pid);
    let read = db->hget(key);
    switch (read("id"), read("name")) {
    | (Some(id), Some(name)) when id == pid =>
      open Option;
      let tz_offset = read("tz_offset") ->> map(float_of_string);
      let cake_month = read("cake_month") ->> map(int_of_string);
      let cake_day = read("cake_day") ->> map(int_of_string);
      let profile = {id, name, tz_offset, cake_month, cake_day};
      Some(profile);
    | _ => None
    };
  };
};

module Mock = {
  let gen =
      (
        ~id="player1",
        ~name=id,
        ~tz_offset=None,
        ~cake_month=None,
        ~cake_day=None,
        (),
      ) => {
    {id, name, tz_offset, cake_month, cake_day};
  };
};
