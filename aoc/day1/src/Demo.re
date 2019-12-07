Js.log("Hello, BuckleScript and Reason!");

let calculateFuel = (mass) => {
    mass / 3 - 2
}




Node.Fs.readFileAsUtf8Sync("./input")
  |> Js.String.trim
  |> Js.String.split("\n")
  |> Array.map(int_of_string)
  |> Array.map(calculateFuel)
  |> Array.fold_left((+), 0)
  |> Js.log
 