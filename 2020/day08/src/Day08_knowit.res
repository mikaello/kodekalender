open Tablecloth

type point = Point(int, int)

type location = {
  coord: point,
  name: string,
}

let getPointFromStr = pointStr => {
  let [_, x, y] = pointStr->Js.String2.match_(%re("/\((\d+), (\d+)\)/"))->Option.getExn

  Point(int_of_string(x), int_of_string(y))
}

let getCoordinates = data => {
  let rec fillCoordinates = (idx, locations) => {
    if Array.length(data) == idx {
      locations
    } else {
      let [name, coordinateStr] = data->Belt.Array.getUnsafe(idx)->Js.String2.split(": ")

      fillCoordinates(idx + 1, locations->Belt.Map.String.set(name, coordinateStr->getPointFromStr))
    }
  }

  fillCoordinates(0, Belt.Map.String.empty)
}

let nameToCoordinate = "input.txt"->Utils.readFileLineRange(~from=0, ~to_=50)->getCoordinates

// "input.txt"->Utils.readFileLineRange(~from=50)->Utils.teeLog
