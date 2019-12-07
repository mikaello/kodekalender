open Jest;
open Expect;

let day2 = 13825167
let day3 = 9216778
let day4 = 20734802

describe("day7", () => {
  test("check vault day 2", () => {
    expect(Demo.getCodeForDay(2)) |> toEqual(day2);
  });
  test("check vault day 3", () => {
    expect(Demo.getCodeForDay(3)) |> toEqual(day3);
  });
  test("check vault day 4", () => {
    expect(Demo.getCodeForDay(4)) |> toEqual(day4);
  });
})
