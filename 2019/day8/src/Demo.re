type operations =
  | PLUSS4
  | PLUSS101
  | MINUS9
  | MINUS1
  | REVERSERSIFFER
  | OPP7
  | GANGEMSD
  | DELEMSD
  | PLUSS1TILPAR
  | TREKK1FRAODDE
  | ROTERPAR
  | ROTERODDE
  | ROTERALLE
  | STOPP;

type numberlist = {
  numbers: list(int),
  negative: bool,
};

type wheel = (operations, operations, operations, operations);

type machineType = list(wheel);

let machine: machineType = [
  (PLUSS101, OPP7, MINUS9, PLUSS101),
  (TREKK1FRAODDE, MINUS1, MINUS9, PLUSS1TILPAR),
  (PLUSS1TILPAR, PLUSS4, PLUSS101, MINUS9),
  (MINUS9, PLUSS101, TREKK1FRAODDE, MINUS1),
  (ROTERODDE, MINUS1, PLUSS4, ROTERALLE),
  (GANGEMSD, PLUSS4, MINUS9, STOPP),
  (MINUS1, PLUSS4, MINUS9, PLUSS101),
  (PLUSS1TILPAR, MINUS9, TREKK1FRAODDE, DELEMSD),
  (PLUSS101, REVERSERSIFFER, MINUS1, ROTERPAR),
  (PLUSS4, GANGEMSD, REVERSERSIFFER, MINUS9),
];

let getLastDigit = number => number mod 10;

let getFirstDigit = number =>
  (number |> abs |> string_of_int)->String.sub(0, 1) |> int_of_string;

let (/-) = (oper1, oper2) =>
  float_of_int(oper1) /. float_of_int(oper2) |> floor |> int_of_float;

let getOperationFromMachine = (machine, wheel) => {
  let (op, _, _, _) = List.nth(machine, wheel);
  op;
};

let up7 = number => {
  let rec fn = number' =>
    if (getLastDigit(number') |> abs == 7) {
      number';
    } else {
      fn(number' + 1);
    };

  fn(number);
};

let turnWheel = ((a, b, c, d): wheel) => (b, c, d, a);

let turnWheelAtIndex = (machine, index) =>
  machine
  |> List.mapi((machineIndex, wheel) =>
       if (machineIndex == index) {
         turnWheel(wheel);
       } else {
         wheel;
       }
     );

let turnEven = machine =>
  machine
  |> List.mapi((index, wheel) =>
       if (index mod 2 == 0) {
         turnWheel(wheel);
       } else {
         wheel;
       }
     );

let turnOdd = machine =>
  machine
  |> List.mapi((index, wheel) =>
       if (index mod 2 != 0) {
         turnWheel(wheel);
       } else {
         wheel;
       }
     );

let getNumberList = number => {
  let rec fn = (number', numbers) =>
    if (number' == 0) {
      numbers;
    } else {
      fn(number' / 10, [number' mod 10, ...numbers]);
    };

  fn(number, []);
};

let numberFromNumberList = numbers => {
  let rec fn = (numbers, factor, sum) =>
    switch (numbers) {
    | [head, ...tail] => fn(tail, factor * 10, sum + head * factor)
    | [] => sum
    };

  fn(List.rev(numbers), 1, 0);
};

let reverseDigit = number =>
  getNumberList(number) |> List.rev |> numberFromNumberList;

let subtractOddNumbers = number =>
  getNumberList(number)
  |> List.map(num =>
       if (num mod 2 != 0) {
         num - 1;
       } else {
         num;
       }
     )
  |> numberFromNumberList;

let addEvenNumbers = number =>
  getNumberList(number)
  |> List.map(num =>
       if (num mod 2 == 0) {
         num + 1;
       } else {
         num;
       }
     )
  |> numberFromNumberList;

let runMachine = (machine, startAmount) => {
  let rec run = (machine', currentAmount) => {
    let currentWheel = getLastDigit(currentAmount) |> abs;
    let nextMachine = turnWheelAtIndex(machine', currentWheel);

    switch (getOperationFromMachine(machine', currentWheel)) {
    | PLUSS4 => run(nextMachine, currentAmount + 4)
    | PLUSS101 => run(nextMachine, currentAmount + 101)
    | MINUS9 => run(nextMachine, currentAmount - 9)
    | MINUS1 => run(nextMachine, currentAmount - 1)
    | REVERSERSIFFER => run(nextMachine, reverseDigit(currentAmount))
    | OPP7 => run(nextMachine, up7(currentAmount))
    | GANGEMSD =>
      run(nextMachine, currentAmount * getFirstDigit(currentAmount))
    | DELEMSD =>
      run(nextMachine, currentAmount /- getFirstDigit(currentAmount))
    | PLUSS1TILPAR => run(nextMachine, addEvenNumbers(currentAmount))
    | TREKK1FRAODDE => run(nextMachine, subtractOddNumbers(currentAmount))
    | ROTERPAR => run(turnEven(nextMachine), currentAmount)
    | ROTERODDE => run(turnOdd(nextMachine), currentAmount)
    | ROTERALLE => run(List.map(turnWheel, nextMachine), currentAmount)
    | STOPP => currentAmount
    };
  };

  run(machine, startAmount);
};

List.map(runMachine(machine), [1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
|> List.fold_left(max, 0)
|> Js.log;
