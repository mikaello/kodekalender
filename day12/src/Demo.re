let explode = someString => {
  let rec exp = (i, l) => i < 0 ? l : exp(i - 1, [someString.[i], ...l]);
  exp(String.length(someString) - 1, []);
};

let implode_to_int = (someCharList: list(char)) => {
  let join = (a, b) => a ++ String.make(1, b);
  List.fold_left(join, "", someCharList) |> int_of_string;
};

let padStart = (length, padding, someCharList: list(char)) => {
  let rec fn = charList =>
    if (List.length(charList) == length) {
      charList;
    } else {
      fn([padding, ...charList]);
    };

  fn(someCharList);
};

let getNumberOfIterations = number => {
  let rec fn = (number', iterations) =>
    if (number' == 6174) {
      iterations;
    } else {
      let numChars = number' |> string_of_int |> explode |> padStart(4, '0');

      let ascending =
        numChars |> List.sort(Pervasives.compare) |> implode_to_int;
      let descending =
        numChars
        |> List.sort(Pervasives.compare)
        |> List.rev
        |> implode_to_int;

      fn(descending - ascending, iterations + 1);
    };

  fn(number, 0);
};

let notAllEqualDigits = number =>
  number
  |> string_of_int
  |> explode
  |> List.sort_uniq(Pervasives.compare)
  |> List.length != 1;

let knowitDay12 = () => {
  let rec fn = (number, withSevenIter) =>
    if (number == 10000) {
      withSevenIter;
    } else if (notAllEqualDigits(number)) {
      let iterations = getNumberOfIterations(number);
      if (iterations == 7) {
        fn(number + 1, withSevenIter + 1);
      } else {
        fn(number + 1, withSevenIter);
      };
    } else {
      fn(number + 1, withSevenIter);
    };

  fn(1000, 0);
};

Js.log(knowitDay12());
