open Contract;
open Sugar;

let time = (now, profile) => {
  switch (profile.tz_offset) {
  | Some(offset) => Unix.gmtime(now +. offset)
  | None => Unix.localtime(now)
  };
};
