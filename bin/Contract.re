type scores = {
  base: int,
  bonus: int,
  penalty: int,
  total: int,
};

type stats = {
  curse: int,
  greed: int,
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
  tz_offset: float,
  cake_month: option(int),
  cake_day: option(int),
};

type player = {
  profile,
  items: list(item),
  stats,
  scores,
};

type header = {
  time: string,
  msg: string,
  sender: profile,
  recipients: list(profile),
};

type mtx = {
  id: string,
  target: string,
  item,
  about: string,
};

type txn = {
  id: string,
  header,
  body: list(mtx),
};

type fx =
  | Curse(int)
  | Greed(int)
  | Luck(int)
  | Wealth(int);

type dyn = {
  cuid: unit => string,
  clock: unit => string,
  dice: int => int,
};

type tokens = {
  base_token: string,
  bonus_tokens: list(string),
  special_tokens: list(string),
  all_tokens: list(string),
  points: string => int,
  fx: string => list(fx),
};

type txn_players = {
  sender: player,
  recipients: list(player),
};

type txn_deps = {
  tokens,
  txn: txn_players,
  dyn,
};

type txn_rule = (txn_deps, list(mtx)) => list(mtx);
type rules = {txn_rules: list(txn_rule)};

type inflag =
  | Exclude(string)
  | Penalize(string, string);

type outflag =
  | NotFound
  | Expired
  | NoRecipients
  | Banned(string)
  | Warned((string, int, int))
  | BanIssued(string);
