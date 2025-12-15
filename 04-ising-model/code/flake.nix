{
  description = "Basic Rust Flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    naersk.url = "github:nix-community/naersk";
  };

  outputs =
    {
      self,
      nixpkgs,
      naersk,
    }:
    let
      pkgs = nixpkgs.legacyPackages."x86_64-linux";
      naerskLib = pkgs.callPackages naersk { };
      myShell = "${pkgs.zsh}/bin/zsh";
    in
    {
      packages."x86_64-linux".default = pkgs.callPackage ./default.nix { naerskLib = naerskLib; };

      devShells."x86_64-linux".default = pkgs.mkShell {
        # TOOLS: Python and plotting libraries
        # We use 'packages' here because these are utilities to run,
        # not libraries your Rust code needs to compile/link against.
        packages = with pkgs; [
          python3
          python312Packages.pandas
          python312Packages.numpy
          python312Packages.matplotlib
          python312Packages.imageio
        ];

        # LIBRARIES & BUILD DEPS: Rust compilation needs
        buildInputs = with pkgs; [
          cargo
          rustc
          clippy
        ];

        nativeBuildInputs = [ pkgs.pkg-config ];

        env.RUST_SRC_PATH = "${pkgs.rust.packages.stable.rustPlatform.rustLibSrc}";

        shellHook = ''
          echo "Welcome to your Rust development shell with Python support!"
          exec ${myShell}
        '';
      };
    };
}
