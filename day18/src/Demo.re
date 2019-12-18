let explode = someString => {
  let rec exp = (i, l) => i < 0 ? l : exp(i - 1, [someString.[i], ...l]);
  exp(String.length(someString) - 1, []);
};

let getAlphabetPosition = someChar => {
  let charValue = int_of_char(someChar);
  if (charValue < 97) {
    charValue - 65;
  } else {
    charValue - 97;
  };
};
