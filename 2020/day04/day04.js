const { readFileSync } = require("fs");

const deliveries = readFileSync("./levering.txt").toString().split("\n");

const ingredients = {
  sukker: 0,
  mel: 0,
  egg: 0,
  melk: 0,
};

deliveries.forEach((singleDelivery) => {
  const parts = singleDelivery.split(", ");
  parts.forEach((part) => {
    const p = part.split(": ");
    ingredients[p[0]] = Number(p[1]);
  });
});

console.log(ingredients);
console.log(
  Math.min(
    Math.round(ingredients.sukker / 2),
    Math.round(ingredients.mel / 3),
    Math.round(ingredients.melk / 3),
    ingredients.egg
  )
);

/**
 * THIS DID NOT WORK :-()
 */
