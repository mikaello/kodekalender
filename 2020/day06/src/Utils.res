@bs.module("fs") external read: (string, string) => string = "readFileSync"

let readFile = filename => {
  read(`./${filename}`, "utf-8")->Js.String.trim
}

let stringToArray = s => s->Js.String2.split("")
let stringToList = s => s->stringToArray->Array.to_list

let teeLog = s => {
  Js.log(s)
  s
}
