let
  pkgs = import <nixpkgs> {};
in pkgs.mkShell {
  packages = [
    pkgs.gnuplot
    pkgs.bc
  ];
}
