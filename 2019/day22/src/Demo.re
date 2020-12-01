let isTreeTop = (forest, x, y) =>
  if (forest[y][x] == "#") {
    if (y == 0) {
      true;
    } else if (x == 0 || x == Array.length(forest[y]) - 1) {
      false;
    } else {
      let a = Array.length(forest[y - 1]) - 1 < x || forest[y - 1][x] != "#";
      let b = forest[y][x - 1] != "#";
      let c = forest[y][x + 1] != "#";

      a && b && c;
    };
  } else {
    false;
  };

let findTreeTops = forest => {
  let treeTops = ref([]);

  for (y in 0 to Array.length(forest) - 1) {
    for (x in 0 to Array.length(forest[y]) - 1) {
      if (isTreeTop(forest, x, y)) {
        treeTops :=
          [float_of_int(Array.length(forest[y]) - (y + 1)), ...treeTops^];
      };
    };
  };

  treeTops^;
};

Node.Fs.readFileAsUtf8Sync("../forest.txt")
|> Js.String.split("\n")
|> Array.map(Js.String.split(""))
|> findTreeTops
|> List.map(el => el /. 5. *. 200.)
|> List.fold_left((+.), 0.)
|> Js.log;
