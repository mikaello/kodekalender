let isPrime = n => {
  let rec isPrime' = (x, d) =>
    switch (d) {
    | 1. => true
    | _ => mod_float(x, d) != 0. && isPrime'(x, d -. 1.)
    };

  let n = float_of_int(n);
  isPrime'(n, n -. 1.);
};

let isHashadPrime = num =>
  num
  |> string_of_int
  |> Tablecloth.String.split(~on="")
  |> List.map(int_of_string)
  |> List.fold_left((+), 0)
  |> (sum => num mod sum == 0 && isPrime(sum));

let getNumberOfHashadPrimes = stop => {
  let count = ref(1); /* 2 is a hashad prime */
  for (i in 3 to stop) {
    if (isHashadPrime(i)) {
      count := count^ + 1;
    };
  };

  count^;
};

Js.log(getNumberOfHashadPrimes(98765432));

/*
     Hashad numbers: https://oeis.org/wiki/Harshad_numbers

     Optimalisering:
     Det er egentlig bare veldig få primtall som brukes (bare 69 og nedover),
     så det hadde egentlig holdt å hardkode disse og sjekke om tallet er et av
     disse
 */
