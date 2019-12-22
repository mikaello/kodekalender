/* KNOWIT dag 13 */

type doorStatus =
  | Unvisited
  | Visited
  | Closed;

type movement =
  | Up
  | Down
  | Left
  | Right;

let string_of_status = status =>
  switch (status) {
  | Unvisited => "unvisited "
  | Visited => "visited "
  | Closed => "closed "
  };

exception UnknownValue(Js.Json.tagged_t);

let doorEncoder = _ => Js.Json.boolean(false);
let doorDecoder = json =>
  switch (Js.Json.classify(json)) {
  | Js.Json.JSONFalse => Belt.Result.Ok(Closed)
  | Js.Json.JSONTrue => Belt.Result.Ok(Unvisited)
  | value => raise(UnknownValue(value))
  };

[@decco]
type door = [@decco.codec (doorEncoder, doorDecoder)] doorStatus;

[@decco]
type cell = {
  x: int,
  y: int,
  top: door,
  left: door,
  bottom: door,
  right: door,
};

[@decco]
type mazetype = array(array(cell));

let getMovementForStrategi = (maze, (x, y), strategies) => {
  let isRoomAvailable = strategi =>
    switch (strategi) {
    | Up => maze[x][y].top == Unvisited
    | Down => maze[x][y].bottom == Unvisited
    | Left => maze[x][y].left == Unvisited
    | Right => maze[x][y].right == Unvisited
    };

  switch (List.find(isRoomAvailable, strategies)) {
  | room => Some(room)
  | exception Not_found => None
  };
};

let solveMaze = (maze, strategies) => {
  let rec fn = ((x, y), steps) =>
    if (Array.length(maze) == x - 1 && Array.length(maze[x]) == y - 1) {
      Some(steps);
    } else {
      switch (getMovementForStrategi(maze, (x, y), strategies)) {
      | Some(dir) =>
        switch (dir) {
        | Up => fn((x + 1, y), steps + 1)
        | Down => fn((x - 1, y), steps + 1)
        | Left => fn((x, y - 1), steps + 1)
        | Right => fn((x, y + 1), steps + 1)
        }
      | None => Some(steps + 1)
      };
    };

  fn((0, 0));
};

exception Error(string);

let getRes = (res: Decco.result(mazetype)) =>
  switch (res) {
  | Belt.Result.Ok(s) => solveMaze(s, [Down, Right, Left, Up])
  | Belt.Result.Error(er) => raise(Error(er.message))
  };

Node.Fs.readFileAsUtf8Sync("../MAZE.TXT.json")
|> Js.Json.parseExn
|> mazetype_decode
|> getRes
|> Js.log;
