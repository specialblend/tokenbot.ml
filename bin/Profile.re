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

  let put = (db, profile) => {
    open Option;
    let rejectNone = keep(x => x);
    let {id, name, tz_offset, cake_month, cake_day} = profile;
    let key = scope(id);
    let data = [
      Some(id) ->? pair("id"),
      Some(name) ->? pair("name"),
      tz_offset ->? Float.to_string ->? pair("tz_offset"),
      cake_month ->? Int.to_string ->? pair("cake_month"),
      cake_day ->? Int.to_string ->? pair("cake_day"),
    ];
    db->hmset(key, rejectNone(data));
  };

  let scan = (db, pid) => {
    let key = scope(pid);
    let read = db->hget(key);

    let id = read("id");
    let name = read("name");

    switch (id, name) {
    | (Some(id), Some(name)) =>
      open Option;
      let tz_offset = read("tz_offset") ->? float;
      let cake_month = read("cake_month") ->? int;
      let cake_day = read("cake_day") ->? int;
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
