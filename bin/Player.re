module Mock = {
  let gen = (~profile=Profile.Mock.gen(), ~items=[], ()) => {
    let stats = Stats.calc(items);
    let scores = Scores.calc(stats, items);
    {profile, items, stats, scores};
  };
};
