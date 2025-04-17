let
  pkgs = import <nixpkgs> {};
in pkgs.mkShell {
  packages = [
    pkgs.gcc
    pkgs.SDL2
    pkgs.SDL2_ttf
    pkgs.pkg-config
    pkgs.dejavu_fonts
  ];

  # This makes sure pkg-config works correctly
  PKG_CONFIG_PATH = pkgs.lib.makeSearchPath "lib/pkgconfig" [
    pkgs.SDL2
    pkgs.SDL2_ttf
  ];
}
