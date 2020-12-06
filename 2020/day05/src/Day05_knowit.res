// open Tablecloth

let smallInput = `HHOOVVNN` // 4 kvm
let largeInput = `HHHHHHOOOOVVNNNVVOVVNN` // 14 kvm

@bs.module("fs") external read: (string, string) => string = "readFileSync"

// Credit: https://www.mathsisfun.com/geometry/area-irregular-polygons.html

let toCoordinates = mousePath => {
  let rec traversePath = (mousePath, area, len, (x: int, y: int)) => {
    switch mousePath {
    | list{"H", ...rest} => traversePath(rest, area, len + 1, (x + 1, y))
    | list{"V", ...rest} => traversePath(rest, area, len - 1, (x - 1, y))
    | list{"N", ...rest} => traversePath(rest, area + len * y, 0, (x, y - 1))
    | list{"O", ...rest} => traversePath(rest, area + len * y, 0, (x, y + 1))
    | list{a, ..._} => raise(Invalid_argument(a))
    | _ => Js.log("done: " ++ string_of_int(Js.Math.abs_int(area)))
    }
  }

  traversePath(mousePath, 0, 0, (0, 0))
}

let split = s => s->Js.String2.split("")->Array.to_list

read("./rute.txt", "utf-8")->split->toCoordinates
