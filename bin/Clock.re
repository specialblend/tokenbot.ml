open Unix;

type weekday =
  | Monday
  | Tuesday
  | Wednesday
  | Thursday
  | Friday
  | Saturday
  | Sunday;

let weekday = tm => {
  switch (tm.tm_wday) {
  | 0 => Sunday
  | 1 => Monday
  | 2 => Tuesday
  | 3 => Wednesday
  | 4 => Thursday
  | 5 => Friday
  | 6 => Saturday
  | _ => Monday
  };
};
