let dim = m => (Array.length(m), Array.length(m[0]));

let transpose = m => {
  let (rows, cols) = dim(m);
  Array.init(cols, c => Array.init(rows, r => m[r][c]));
};

let largestCoordinates = ((currX, currY), (x, y)) => (
  max(currX, x),
  max(currY, y),
);

let addOne = ((x, y)) => (x + 1, y + 1);

let getMaxDimension = coordinates =>
  coordinates |> Array.fold_left(largestCoordinates, (0, 0)) |> addOne;

let fillMatrix = (coordinates, matrix) => {
  coordinates |> Array.iter(((x, y)) => matrix[x][y] = "x");

  matrix;
};

let matrixOfCoordinates = coordinates => {
  let (x, y) = getMaxDimension(coordinates);
  Array.make_matrix(x, y, ".") |> fillMatrix(coordinates);
};

let printMatrix = matrix =>
  matrix
  |> Array.map(trip => Js.String.concatMany(trip, ""))
  |> Array.fold_left((prev, cur) => Js.String.concat("\n" ++ prev, cur), "");

Node.Fs.readFileAsUtf8Sync("turer.txt")
|> Js.String.split("---")
|> Array.map(Js.String.trim)
|> Array.map(Js.String.split("\n"))
|> Array.map(Array.map(Js.String.trim))
|> Array.map(
     Array.map(coordString => {
       let coordinates =
         Js.String.split(",", coordString) |> Array.map(int_of_string);

       (coordinates[0], coordinates[1]);
     }),
   )
|> Array.map(matrixOfCoordinates)
|> Array.map(transpose)
|> Array.map(printMatrix)
|> Array.map(Js.log);
