let splitByParantheses = wordWithParan =>
  wordWithParan->Js.String2.splitByRe(%re("/([()])/"))->Belt.Array.keepMap(maybeStr =>
    switch maybeStr {
    | Some(str) =>
      if String.length(str) > 0 {
        Some(str)
      } else {
        None
      }
    | None => None
    }
  )

let traverseFamilyTree = tree => {
  let generationCounts = Belt.Array.makeBy(10000, _ => 0)

  let increaseGenerationCount = generation => {
    let current = generationCounts->Belt.Array.getUnsafe(generation)
    let _ = generationCounts->Belt.Array.set(generation, current + 1)
  }

  let rec traverse = (currGeneration, currTree) => {
    switch currTree {
    | list{head, ...rest} =>
      switch head {
      | "(" => traverse(currGeneration + 1, rest)
      | ")" => traverse(currGeneration - 1, rest)
      | _ =>
        increaseGenerationCount(currGeneration)
        traverse(currGeneration, rest)
      }
    | list{} => generationCounts->Belt.Set.Int.fromArray->Belt.Set.Int.maximum
    }
  }

  traverse(0, tree)
}

"family.txt"
->Utils.readFile
->Js.String2.splitByRe(%re("/\s/"))
->Belt.Array.keepMap(x => x)
->Belt.Array.map(splitByParantheses)
->Belt.Array.concatMany
->Belt.List.fromArray
->traverseFamilyTree
->Js.log
