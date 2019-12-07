let numberspace = 27644437;

let addNumberspaceUntilPositive = num => {
  let rec fn = num' =>
    if (num' >= 0) {
      num';
    } else {
      fn(num' + numberspace);
    };

  fn(num);
};

let modNumberspace = num => num mod numberspace |> addNumberspaceUntilPositive;

let calculateY = x => {
  let stepA = y' => y' * x;

  let rec fn = y' =>
    if (y' == numberspace) {
      None;
    } else {
      let b = stepA(y');
      let r = modNumberspace(b);

      if (r == 1) {
        Some(y');
      } else {
        fn(y' + 1);
      };
    };

  fn(2);
};

let calculateZ = (hash, y) => hash * y;

let (|-) = (hash, x) =>
  switch (calculateY(x)) {
  | None => (-1)
  | Some(y) =>
    let z = y |> calculateZ(hash);
    modNumberspace(z);
  };

let getCodeForDay = day => 5897 |- day;

Js.log(getCodeForDay(7));
