let make: string => Js.Exn.t = [%raw
  {|
  function(message) { return new Error(message) }
|}
];

let throw: Js.Exn.t => unit = [%raw {| function(error) { throw error } |}];

let unsafe_from_exception: exn => Js.Exn.t =
  exception_ =>
    switch (exception_) {
    | Js.Exn.Error(e) => e
    | _ => raise(Not_found)
    };

let unsafe_to_exception: Js.Exn.t => exn =
  error =>
    try (
      {
        throw(error);
        Not_found;
      }
    ) {
    | Js.Exn.Error(_) as js_exn => js_exn
    };
