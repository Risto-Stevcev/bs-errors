open BsMochajs.Mocha;

let message = "This is a foobar error";
let foobar = Error.make(message);

describe("throw_error", () => {
  it("should throw the error", () => {
    let result =
      try ({
        Error.throw(foobar);
        false;
      }) { | _ => true };

    expect(result).to_be(true)
  })
});

describe("unsafe_from_exception and unsafe_to_exception", () => {
  let stack_trace = error => Js.Exn.stack(error) |> Js.Option.getWithDefault("");

  it("should convert a Js error to/from an Ocaml exception", () => {
    let expected_stack_trace =
      Js.Re.fromString("^Error: "++ message ++"\n    at make \\([^:]+:\\d+:\\d+\\)");

    expect(Js.Re.test(stack_trace(foobar), expected_stack_trace)).to_be(true);
    expect(
      foobar |> Error.unsaafe_to_exception |> Error.unsafe_from_exception |> stack_trace
    ).to_be(stack_trace(foobar));
  });
});

/*
Js.log(Js.Exn.stack(foobar) |> Js.Option.getWithDefault(""));
Js.Re.fromString("Error: foobar\n    at make \([^:]+:\d+:\d+\)");
*/
/*
/Error: foobar\n    at make \([^:]+:\d+:\d+\)/
*/
