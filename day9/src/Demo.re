let isKrampus = n => {
  let intN = n |> Int64.of_string;
  let powerN = Int64.mul(intN, intN) |> Int64.to_string;
  let nLength = String.length(powerN);

  let rec fn = nIndex =>
    if (nIndex == nLength) {
      false;
    } else {
      let first = String.sub(powerN, 0, nIndex) |> Int64.of_string;
      let second =
        String.sub(powerN, nIndex, nLength - nIndex) |> Int64.of_string;

      if (first != Int64.zero
          && second != Int64.zero
          && Int64.add(first, second) == intN) {
        true;
      } else {
        fn(nIndex + 1);
      };
    };

  fn(1);
};

Node.Fs.readFileAsUtf8Sync("./krampus.txt")
|> Js.String.trim
|> Js.String.split("\n")
|> Array.to_list
|> List.filter(isKrampus)
|> List.map(int_of_string)
|> List.fold_left((+), 0)
|> Js.log;
