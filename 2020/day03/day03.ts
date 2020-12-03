const { readFileSync } = require("fs");

console.time("day03");

const reverseString = (s: string) => [...s].reverse().join("");

const containesHorizontal = (matrix: string[], word: string) => {
  const bWord = reverseString(word);
  for (let row of matrix) {
    if (row.includes(word) || row.includes(bWord)) {
      return true;
    }
  }
  return false;
};

const transpose = (matrix: any[][]) => {
  const transposed = matrix[0].map((_, colIndex) =>
    matrix.map((row) => row[colIndex])
  );
  return transposed;
};

/**
 *          --a--
 *          -b-a-
 * aaa      c-b-a
 * bbb  =>  -c-b-
 * ccc      --c--
 *
 * Credit: https://math.stackexchange.com/questions/732679/how-to-rotate-a-matrix-by-45-degrees */
const rotate45degrees = (matrix: string[][]) => {
  const rotatedMatrixSize = matrix.length * 2 - 1;
  const rotatedMatrix = Array(rotatedMatrixSize);
  for (let x = 0; x < rotatedMatrixSize; x++) {
    rotatedMatrix[x] = Array(rotatedMatrixSize).fill("-");
  }

  matrix.forEach((row, x) => {
    row.forEach((cell, y) => {
      rotatedMatrix[x + y][-x + y + matrix.length - 1] = cell;
    });
  });

  return rotatedMatrix;
};

const stringifyCharArray = (arr: string[]) => arr.join("");

const matrix = readFileSync("./matrix.txt").toString().split("\n");
const words = readFileSync("./words.txt").toString().split("\n");

const charMatrix = matrix.map((str: string) => str.split(""));
const matrixTransposed = transpose(charMatrix).map(stringifyCharArray);
const rotatedMatrixChar = rotate45degrees(charMatrix);
const rotatedMatrix = rotatedMatrixChar.map(stringifyCharArray);
const rotatedMatrixTransposed = transpose(rotatedMatrixChar).map(
  stringifyCharArray
);

const notFound: string[] = [];

const insertCharInbetween = (word: string, char: string) =>
  [...word].join(char);

words.forEach((word: string) => {
  if (
    !(
      containesHorizontal(matrix, word) ||
      containesHorizontal(matrixTransposed, word) ||
      containesHorizontal(rotatedMatrix, insertCharInbetween(word, "-")) ||
      containesHorizontal(
        rotatedMatrixTransposed,
        insertCharInbetween(word, "-")
      )
    )
  ) {
    notFound.push(word);
  }
});
console.timeEnd("day03");

console.log("Not found words:\n" + notFound.sort());
