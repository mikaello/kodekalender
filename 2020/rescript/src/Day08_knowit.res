open Tablecloth

type point = Point(int, int)

type location = {
  coord: point,
  time: float,
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
      fillCoordinates(
        idx + 1,
        locations->Belt.Map.String.set(name, {time: 0.0, coord: coordinateStr->getPointFromStr}),
      )
    }
  }

  fillCoordinates(0, Belt.Map.String.empty)
}

let getLargesTimeDiff = cities => {
  let rec getDiff = (idx, min, max) => {
    switch cities->Belt.Array.get(idx) {
    | Some({time, coord: _}) => getDiff(idx + 1, Float.minimum(time, min), Float.maximum(time, max))
    | None => max -. min
    }
  }

  let f = cities->Belt.Array.getUnsafe(0)

  getDiff(1, f.time, f.time)
}
let updateCities = (nissePos, cities) => {
  let getManhattenDistance = (Point(p1, p2), Point(q1, q2)) => {
    Int.absolute(p1 - q1) + Int.absolute(p2 - q2)
  }

  cities->Belt.Map.String.map(value => {
    let distance = getManhattenDistance(nissePos, value.coord)
    if distance == 0 {
      value
    } else if distance < 5 {
      {coord: value.coord, time: value.time +. 0.25}
    } else if distance < 20 {
      {coord: value.coord, time: value.time +. 0.5}
    } else if distance < 50 {
      {coord: value.coord, time: value.time +. 0.75}
    } else {
      {coord: value.coord, time: value.time +. 1.0}
    }
  })
}

let nisseTravel = (~cityCoordinates, route) => {
  let getDistance = (city, Point(p1, p2)) => {
    let {coord: Point(x, y), time: _} = cityCoordinates->Belt.Map.String.getExn(city)

    (p1 - x, p2 - y)
  }

  let getNewPosition = ((dist1, dist2), Point(p1, p2)) => {
    if dist1 > 0 {
      Point(p1 - 1, p2)
    } else if dist1 < 0 {
      Point(p1 + 1, p2)
    } else if dist2 > 0 {
      Point(p1, p2 - 1)
    } else {
      Point(p1, p2 + 1)
    }
  }

  let rec travel = (idx, cities, pos, currentCity) => {
    if Array.length(route) == idx {
      cities
    } else {
      let (x, y) = getDistance(currentCity, pos)

      if x != 0 || y != 0 {
        let newPos = getNewPosition((x, y), pos)
        let newCities = updateCities(newPos, cities)
        travel(idx, newCities, newPos, currentCity)
      } else {
        let city = route->Belt.Array.getUnsafe(idx)
        travel(idx + 1, cities, pos, city)
      }
    }
  }

  travel(1, cityCoordinates, Point(0, 0), route->Belt.Array.getUnsafe(0))
}

let nameToCoordinate = "input.txt"->Utils.readFileLineRange(~from=0, ~to_=50)->getCoordinates

"input.txt"
->Utils.readFileLineRange(~from=50)
->nisseTravel(~cityCoordinates=nameToCoordinate)
->Belt.Map.String.valuesToArray
->getLargesTimeDiff
->Js.log
