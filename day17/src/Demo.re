let isPerfectSquare = n => n == ceil(sqrt(n)) ** 2.0;

let getTriangularNumber = n => n *. (n +. 1.) /. 2.;

let isFinishedRolling = (num, rollCount) => rollCount == String.length(num);

let roll = (num, rollCount) =>
  if (String.length(num) == 1) {
    (num, 1);
  } else {
    let splitPoint = String.length(num) - 1;
    let endDigit = Js.String.sliceToEnd(~from=splitPoint, num);
    let start = Js.String.slice(~from=0, ~to_=splitPoint, num);

    let result = endDigit ++ start;
    (result, rollCount + 1);
  };

let getCount = () => {
  let count = ref(0);

  for (i in 0 to 1000000) {
    let rollCount = ref(0);
    let numString =
      ref(i |> float_of_int |> getTriangularNumber |> Js.Float.toString);
    let perfectSquare = ref(false);

    while (!isFinishedRolling(numString^, rollCount^) && ! perfectSquare^) {
      perfectSquare := numString^ |> float_of_string |> isPerfectSquare;

      let (rolledNumber, newCount) = roll(numString^, rollCount^);
      numString := rolledNumber;
      rollCount := newCount;
    };

    if (perfectSquare^) {
      count := count^ + 1;
    };
  };

  count^;
};

Js.log(getCount());
