let willBeInfected = (elves, (x, y)) => {
  let infectedNeighbours = ref(0)

  let addIfInfected = (x, y) => {
    if elves->Belt.Array.getUnsafe(y)->Belt.Array.getUnsafe(x) == "S" {
      infectedNeighbours := infectedNeighbours.contents + 1
    }
  }

  if x > 0 {
    addIfInfected(x - 1, y)
  }
  if y > 0 {
    addIfInfected(x, y - 1)
  }
  if y < Array.length(elves) - 1 {
    addIfInfected(x, y + 1)
  }
  if x < elves->Belt.Array.getUnsafe(y)->Array.length {
    addIfInfected(x + 1, y)
  }

  infectedNeighbours.contents >= 2
}

let findNewInfected = elves => {
  let countInfected = ref(0)

  let updatedElves = elves |> Array.mapi((y, row) => row |> Array.mapi((x, cell) => {
      switch cell {
      | "F" =>
        if willBeInfected(elves, (x, y)) {
          countInfected := countInfected.contents + 1
          "S"
        } else {
          "F"
        }
      | "S" => cell
      | a => raise(Invalid_argument(a))
      }
    }))

  (updatedElves, countInfected.contents)
}

let runTuborg = elves => {
  let rec run = (round, elves') => {
    let (updatedElves, newInfected) = findNewInfected(elves')
    if newInfected == 0 {
      round
    } else {
      run(round + 1, updatedElves)
    }
  }

  run(1, elves)
}

"elves.txt"
->Utils.readFile
->Js.String2.split("\n")
->Belt.Array.map(Utils.stringToArray)
->runTuborg
->Js.log
