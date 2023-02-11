open Contract;
open Unix;
open Sugar;

let time = (now, profile) => {
  switch (profile.tz_offset) {
  | Some(offset) => now +. offset->gmtime
  | None => now->localtime
  };
};

module DB = {
  open Redis;
  let scope = prefix("profile");
};
