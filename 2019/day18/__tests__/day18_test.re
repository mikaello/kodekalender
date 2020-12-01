open Jest;
open Expect;

open Demo;

describe("alphabet position", () => {
  test("lowercase", () =>
    expect(getAlphabetPosition('a')) |> toEqual(0)
  );
  test("caps", () =>
    expect(getAlphabetPosition('A')) |> toEqual(0)
  );
  test("last position", () =>
    expect(getAlphabetPosition('z')) |> toEqual(25)
  );
});
