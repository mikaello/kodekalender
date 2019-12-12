let explode = someString => {
  let rec exp = (i, l) => i < 0 ? l : exp(i - 1, [someString.[i], ...l]);
  exp(String.length(someString) - 1, []);
};

type prevTerrain =
  | Air
  | G
  | I(int)
  | A
  | S
  | F(bool);

exception UnknownTerrain;

let calculateStopLength = terrain => {
  let rec calc = (t, speed, length, previous) =>
    if (speed <= 0) {
      length;
    } else {
      switch (t, previous) {
      | (['G', ...rest], _) => calc(rest, speed - 27, length + 1, G)
      | (['I', ...rest], I(cons)) =>
        calc(rest, speed + 12 * cons, length + 1, I(cons + 1))
      | (['I', ...rest], _) => calc(rest, speed + 12, length + 1, I(2))
      | (['A', ...rest], _) => calc(rest, speed - 59, length + 1, A)
      | (['S', ...rest], _) => calc(rest, speed - 212, length + 1, S)
      | (['F', ...rest], F(true)) =>
        calc(rest, speed + 35, length + 1, F(false))
      | (['F', ...rest], _) => calc(rest, speed - 70, length + 1, F(true))
      | (_, _) => raise(UnknownTerrain)
      };
    };

  calc(terrain, 10703437, 0, Air);
};

Node.Fs.readFileAsUtf8Sync("./terreng.txt")
|> Js.String.replace("\n", "")
|> Js.String.trim
|> explode
|> calculateStopLength
|> Js.log;
