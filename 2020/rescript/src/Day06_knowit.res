open Tablecloth

let getMaxSum = (~divisor, numbers) => {
  let rec getSum = (idx, sum, highestSum, highestSumIdx) => {
    switch numbers[idx] {
    | None => `${string_of_int(highestSum / divisor)},${string_of_int(highestSumIdx + 1)}`
    | Some(number) => {
        let newSum = sum + number
        if mod(newSum, divisor) == 0 {
          getSum(idx + 1, newSum, newSum, idx)
        } else {
          getSum(idx + 1, newSum, highestSum, highestSumIdx)
        }
      }
    }
  }

  getSum(0, 0, 0, 0)
}

let sampleSize = 10
let sampleElfs = 9
let sample =
  "14,10,14,15,14,13,13,13,15,11"
  ->Js.String2.split(",")
  ->Array.map(~f=int_of_string)
  ->Js.Array2.sortInPlace
  ->Js.Array2.reverseInPlace
  ->getMaxSum(~divisor=sampleElfs)
  ->Utils.teeLog

let elfs = 127
let candyBags = 10000

"godteri.txt"
->Utils.readFile
->Js.String2.split(",")
->Array.map(~f=int_of_string)
->Js.Array2.sortInPlace
->Js.Array2.reverseInPlace
->getMaxSum(~divisor=elfs)
->Utils.teeLog
