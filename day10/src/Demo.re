exception UnknownInput;

let getMonth = month =>
  switch (month) {
  | "Jan" => 0.
  | "Feb" => 1.
  | "Mar" => 2.
  | "Apr" => 3.
  | "May" => 4.
  | "Jun" => 5.
  | "Jul" => 6.
  | "Aug" => 7.
  | "Sep" => 8.
  | "Oct" => 9.
  | "Nov" => 10.
  | "Dec" => 11.
  | _ => raise(UnknownInput)
  };

let getDate = date => String.sub(date, 0, 2) |> float_of_string;

type consumption = {
  toothpaste: int,
  shampoo: int,
  toiletPaper: int,
  sundayShampoo: int,
  wednesdayToiletPaper: int,
};

let addToothpaste = (amount, consumption) => {
  let amount = int_of_string(amount);
  {...consumption, toothpaste: consumption.toothpaste + amount};
};

let addShampoo = (amount, consumption, date) => {
  let amount = int_of_string(amount);
  ReDate.isSunday(date) ?
    {
      ...consumption,
      shampoo: consumption.shampoo + amount,
      sundayShampoo: consumption.sundayShampoo + amount,
    } :
    {...consumption, shampoo: consumption.shampoo + amount};
};

let addToiletPaper = (amount, consumption, date) => {
  let amount = int_of_string(amount);

  ReDate.isWednesday(date) ?
    {
      ...consumption,
      toiletPaper: consumption.toiletPaper + amount,
      wednesdayToiletPaper: consumption.wednesdayToiletPaper + amount,
    } :
    {...consumption, toiletPaper: consumption.toiletPaper + amount};
};

let calculateConsumption = log => {
  let makeDate = Js.Date.makeWithYMDH(~year=2018., ~hours=12.);

  let rec cc = (day, index, consumption) =>
    if (Array.length(log) == index) {
      consumption;
    } else {
      switch (log[index]) {
      | ["*", amount, "ml", "tannkrem"] =>
        cc(day, index + 1, addToothpaste(amount, consumption))
      | ["*", amount, "ml", "sjampo"] =>
        cc(day, index + 1, addShampoo(amount, consumption, day))
      | ["*", amount, "meter", "toalettpapir"] =>
        cc(day, index + 1, addToiletPaper(amount, consumption, day))
      | [month, date] =>
        cc(
          makeDate(~month=getMonth(month), ~date=getDate(date), ()),
          index + 1,
          consumption,
        )
      | _ => raise(UnknownInput)
      };
    };

  Js.log(makeDate(~month=0., ~date=1., ()) |> Js.Date.toISOString);
  cc(
    makeDate(~month=0., ~date=1., ()),
    0,
    {
      toothpaste: 0,
      shampoo: 0,
      toiletPaper: 0,
      sundayShampoo: 0,
      wednesdayToiletPaper: 0,
    },
  );
};

let sumComsumption = consumption => {
  let toothpasteTube = 125;
  let shampooTube = 300;
  let toiletPaperRoll = 25;

  let toothpasteTubes = consumption.toothpaste / toothpasteTube;
  let shampooTubes = consumption.shampoo / shampooTube;
  let toiletPaperRolls = consumption.toiletPaper / toiletPaperRoll;

  toothpasteTubes
  * shampooTubes
  * toiletPaperRolls
  * consumption.sundayShampoo
  * consumption.wednesdayToiletPaper;
};

Node.Fs.readFileAsUtf8Sync("./logg.txt")
|> Js.String.trim
|> Js.String.split("\n")
|> Array.map(el => el |> Js.String.trim |> Js.String.split(" "))
|> Array.map(Array.to_list)
|> calculateConsumption
|> sumComsumption
|> Js.log;
