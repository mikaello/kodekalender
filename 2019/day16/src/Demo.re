let printMap = map =>
  Array.fold_left(
    (acc, arr) => Array.fold_left((++), acc ++ "\n", arr),
    "",
    map,
  );

let getBirte = fjord => {
  let index = ref((0, 0));

  for (i in 0 to Array.length(fjord) - 1) {
    for (j in 0 to Array.length(fjord[i]) - 1) {
      if (fjord[i][j] == "B") {
        index := (i, j);
      };
    };
  };

  index^;
};

type direction =
  | NorthEast
  | SouthEast;

exception UnknownSymbol(string);

let calculateTurns = fjord => {
  let rec calc = (fjord', (i, j), turns, direction) =>
    if (Array.length(fjord'[i]) == j) {
      turns;
    } else {
      let borderIndex =
        switch (direction) {
        | NorthEast => i - 2
        | SouthEast => i + 2
        };

      /*      Node.Fs.writeFileAsUtf8Sync("fjord2.txt", printMap(fjord'));*/

      switch (fjord'[borderIndex][j], direction) {
      | ("#", NorthEast) => calc(fjord', (i + 1, j), turns + 1, SouthEast)
      | ("#", SouthEast) => calc(fjord', (i - 1, j), turns + 1, NorthEast)
      | (" ", NorthEast) =>
        fjord'[i][j] = "/";
        calc(fjord', (i - 1, j + 1), turns, direction);
      | (" ", SouthEast) =>
        fjord'[i][j] = "\\";
        calc(fjord', (i + 1, j + 1), turns, direction);
      | (any, _) => raise(UnknownSymbol(any))
      };
    };

  calc(fjord, getBirte(fjord), 1, NorthEast);
};

Node.Fs.readFileAsUtf8Sync("fjord.txt")
|> Js.String.trim
|> Js.String.split("\n")
|> Array.map(el => el |> Js.String.split(""))
|> calculateTurns
|> Js.log;
