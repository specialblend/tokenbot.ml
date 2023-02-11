type msg_edited = {
  user: string,
  ts: string,
};

type app_mention = {
  client_msg_id: string,
  ts: string,
  text: string,
  user: string,
  team: string,
  channel: string,
  event_ts: string,
  edited: option(msg_edited),
};

type scores = {
  base: int,
  bonus: int,
  penalty: int,
  total: int,
};

type stats = {
  curse: int,
  luck: int,
  wealth: int,
};

type item = {
  token: string,
  qty: int,
};

type profile = {
  id: string,
  name: string,
  tz_offset: option(float),
  // cake_month: option(int),
  // cake_day: option(int),
};

type player = {
  profile,
  items: list(item),
  stats,
  scores,
};

type mtxn = {
  id: string,
  target: string,
  about: string,
  item,
};

type txnh = {
  id: string,
  time: float,
  msg: string,
  sender: profile,
  recipients: list(profile),
};

type fx =
  | Curse(int)
  | Luck(int)
  | Wealth(int);
