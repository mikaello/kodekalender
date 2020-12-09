@bs.module("fs") external read: (string, string) => string = "readFileSync"

let readFile = filename => {
  read(`./${filename}`, "utf-8")->Js.String.trim
}

let readFileLineRange = (~from, ~to_=?, filename) => {
  let lines = filename->readFile->Js.String2.split("\n")

  switch to_ {
  | Some(to_) => lines->Belt.Array.slice(~offset=from, ~len=to_ - from)
  | None => lines->Belt.Array.sliceToEnd(from)
  }
}

let stringToArray = s => s->Js.String2.split("")
let stringToList = s => s->stringToArray->Array.to_list

let teeLog = s => {
  Js.log(s)
  s
}
