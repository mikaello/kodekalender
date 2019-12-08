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

let getOperationFromMachine = (machine: machineType, wheel) => {
  let (op, _, _, _) = List.nth(machine, wheel);
  op;
};

let runMachine = (machine, startAmount) => {
  let rec run = (machine', currentAmount) =>
    switch (getLastDigit(currentAmount) |> getOperationFromMachine(machine')) {
    | PLUSS4
    | PLUSS101 => run(machine', currentAmount + 101)
    | MINUS9 => run(machine', currentAmount - 9)
    | MINUS1 => run(machine', currentAmount - 1)
    | REVERSERSIFFER => run(machine', currentAmount)
    | OPP7 => run(machine', currentAmount)
    | GANGEMSD => run(machine', currentAmount)
    | DELEMSD => run(machine', currentAmount)
    | PLUSS1TILPAR => run(machine', currentAmount)
    | TREKK1FRAODDE => run(machine', currentAmount)
    | ROTERPAR => run(machine', currentAmount)
    | ROTERODDE => run(machine', currentAmount)
    | ROTERALLE => run(machine', currentAmount)
    | STOPP => currentAmount
    };

  run(machine, startAmount);
};
