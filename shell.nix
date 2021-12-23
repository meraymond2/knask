with (import <unstable> {});

mkShell rec {
  name = "knask";

  buildInputs = [
    cmake
    clang_11
  ];

}
