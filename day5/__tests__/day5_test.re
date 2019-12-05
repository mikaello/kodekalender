open Jest;
open Expect;

let testStr = "PonnistallHoppeslottTrommesett"

describe("day5", () => {
  test("divide and switch ", () => {
    expect(Day5.divideInTwo(testStr) |> Day5.switch2 |> Day5.combine2)
    |> toEqual(
       "slottTrommesettPonnistallHoppe"
       );
  });

    test("switch every two", () => {
    expect(Day5.divideInTwo(testStr) |> Day5.switch2 |> Day5.combine2 |> Day5.explode |> Day5.switchEveryTwo |> Day5.implode)
    |> toEqual(
       "lstoTtormmsetePtnointslaHlpoep"
       );
  });

      test("switch every three inwards", () => {
    expect(Day5.divideInTwo(testStr) |> Day5.switch2 |> Day5.combine2 |> Day5.explode |> Day5.switchEveryTwo |> Day5.switchEveryThreeInwards |> Day5.implode )
    |> toEqual(
       "oepHlpslainttnotePmseormoTtlst"
       );
  });

});
