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
      Some(id) ->> map(pair("id")),
      Some(name) ->> map(pair("name")),
      tz_offset ->> map(Float.to_string) ->> map(pair("tz_offset")),
      cake_month ->> map(Int.to_string) ->> map(pair("cake_month")),
      cake_day ->> map(Int.to_string) ->> map(pair("cake_day")),
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
      let tz_offset = read("tz_offset") ->> map(float);
      let cake_month = read("cake_month") ->> map(int);
      let cake_day = read("cake_day") ->> map(int);
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
