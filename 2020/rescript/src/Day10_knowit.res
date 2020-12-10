let compToPoints = result =>
  result
  ->Belt.Array.mapWithIndex((i, res) => (res, Array.length(result) - (i + 1)))
  ->Belt.Map.String.fromArray

let mergeResMap = (_, val1, val2) =>
  switch (val1, val2) {
  | (Some(val1), Some(val2)) => Some(val1 + val2)
  | (Some(val1), None) => Some(val1)
  | (None, Some(val2)) => Some(val2)
  | (None, None) => None
  }

"leker.txt"
|> Utils.readFile
|> Js.String.split("\n")
|> Array.map(Js.String.split(","))
|> Array.map(compToPoints)
|> Array.fold_left((a, b) => Belt.Map.String.merge(a, b, mergeResMap), Belt.Map.String.empty)
|> Belt.Map.String.toArray
|> Array.fold_left(((k1, v1), (k2, v2)) =>
  if v1 > v2 {
    (k1, v1)
  } else {
    (k2, v2)
  }
, ("", 0))
|> Js.log
