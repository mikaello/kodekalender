open Jest;
open Expect;

open Demo;

describe("truthy hashadPrime", () => {
  test("2", () =>
    expect(isHashadPrime(2)) |> toBe(true)
  );
  test("3", () =>
    expect(isHashadPrime(3)) |> toBe(true)
  );
  test("5", () =>
    expect(isHashadPrime(5)) |> toBe(true)
  );
  test("7", () =>
    expect(isHashadPrime(7)) |> toBe(true)
  );
  test("200", () =>
    expect(isHashadPrime(200)) |> toBe(true)
  );
  test("201", () =>
    expect(isHashadPrime(201)) |> toBe(true)
  );
  test("133", () =>
    expect(isHashadPrime(133)) |> toBe(true)
  );
  test("1729", () =>
    expect(isHashadPrime(1729)) |> toBe(true)
  );
  test("100002", () =>
    expect(isHashadPrime(100002)) |> toBe(true)
  );
});

describe("falsy hashadPrime", () => {
  test("1", () =>
    expect(isHashadPrime(1)) |> toBe(false)
  );
  test("4", () =>
    expect(isHashadPrime(4)) |> toBe(false)
  );
  test("11", () =>
    expect(isHashadPrime(11)) |> toBe(false)
  );
  test("37", () =>
    expect(isHashadPrime(37)) |> toBe(false)
  );
  test("54", () =>
    expect(isHashadPrime(54)) |> toBe(false)
  );
  test("100", () =>
    expect(isHashadPrime(100)) |> toBe(false)
  );
  test("132", () =>
    expect(isHashadPrime(132)) |> toBe(false)
  );
  test("204", () =>
    expect(isHashadPrime(204)) |> toBe(false)
  );
  test("1000", () =>
    expect(isHashadPrime(1000)) |> toBe(false)
  );
  test("1730", () =>
    expect(isHashadPrime(1730)) |> toBe(false)
  );
  test("10000", () =>
    expect(isHashadPrime(10000)) |> toBe(false)
  );
  test("100000", () =>
    expect(isHashadPrime(100000)) |> toBe(false)
  );
  test("100001", () =>
    expect(isHashadPrime(100001)) |> toBe(false)
  );
});
