Js.log("day5");

let switch2 = ((one, two)) => { 
    (two, one)
}

let combine2 = ((one, two)) => {
    one ++ two
}

let divideInTwo = someString => {
    let length = String.length(someString);

    let first = String.sub(someString, 0, length/2);
    let second = String.sub(someString, length/2, length/2);

    (first, second);
}

let explode = someString => {
  let rec exp = (i, l) => i < 0 ? l : exp(i - 1, [someString.[i], ...l]);
  exp(String.length(someString) - 1, []);
};

let implode = (someCharList: list(char)) => {
    let join = (a,b) => a ++ String.make(1, b);
    List.fold_left(join, "", someCharList)
}

let switchEveryTwo = someList => {
    let rec fn = someList => {
        switch(someList) {
            | [a,b, ...rest] => [ b,a, ...fn(rest)]
            | [a] => [a]
            | [] => [ ]
        }
    }

    fn(someList)
}

let switchEveryThreeInwards = someList => {
   let rec fn = (someList) => {
       switch(someList) {
           | ([a,b,c, ...rest] ) => List.concat([fn(rest), [a,b,c]])
           | ([a,b, ..._]) => [a,b]
           | ([a, ..._]) => [a]
           | ([]) => []
       }
   } 

   fn(someList);
}

let theString = "tMlsioaplnKlflgiruKanliaebeLlkslikkpnerikTasatamkDpsdakeraBeIdaegptnuaKtmteorpuTaTtbtsesOHXxonibmksekaaoaKtrssegnveinRedlkkkroeekVtkekymmlooLnanoKtlstoepHrpeutdynfSneloietbol";

theString |> explode |> switchEveryThreeInwards |> switchEveryTwo |> implode |> divideInTwo |> switch2 |> combine2 |> Js.log

