let columnContainsWord = (listOfExplodedWords, word) => {
  let transpose = matrix =>
    matrix
    ->Belt.Array.getUnsafe(0)
    ->Belt.Array.mapWithIndex((colIndex, _) =>
      matrix->Belt.Array.map(row => row->Belt.Array.getUnsafe(colIndex))
    )

  listOfExplodedWords
  ->transpose
  ->Belt.Array.map(Utils.arrayToString)
  ->Belt.Array.some(w => w->Js.String2.includes(word))
}

let addTwoSmallCapChars = (c1, c2) => {
  (c1 - 97 + (c2 - 97))->mod(26)->(c => c + 97)
}

let getNextWord = currWord => {
  let stringToCharCode = s => Js.String.charCodeAt(0, s)->int_of_float
  let rotateChar = c => (c + 1)->mod(122)->max(97)

  let nextWord = currWord->Belt.Array.sliceToEnd(1)
  nextWord
  ->Belt.Array.map(stringToCharCode)
  ->Belt.Array.map(rotateChar)
  ->Belt.Array.mapWithIndex((idx, c) =>
    currWord->Belt.Array.getUnsafe(idx)->stringToCharCode->addTwoSmallCapChars(c)
  )
  ->Belt.Array.map(Js.String.fromCharCode)
}

let clueContainsPassword = (clue, password) => {
  let rec runProcedure = (idx, clueArr) => {
    if String.length(clue) == idx {
      columnContainsWord(clueArr, password)
    } else {
      let previousElement = clueArr->Belt.Array.getUnsafe(idx)

      let nextWord = getNextWord(previousElement)

      runProcedure(idx + 1, Belt.Array.concat(clueArr, [nextWord]))
    }
  }

  runProcedure(0, [clue->Utils.stringToArray])
}

"hint.txt"->Utils.readFile->Js.String2.split("\n")->Belt.Array.forEach(w =>
  if w->clueContainsPassword("eamqia") {
    Js.log(w)
  }
)
