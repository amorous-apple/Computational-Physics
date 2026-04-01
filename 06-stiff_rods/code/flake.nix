{
  description = "C development environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-25.05";
  };

  outputs =
    { self, nixpkgs }:
    let
      pkgs = nixpkgs.legacyPackages.x86_64-linux;
      myShell = "${pkgs.zsh}/bin/zsh"; # change this to bash, fish, etc.
    in
    {
      devShells.x86_64-linux.default = pkgs.mkShell {
        packages = with pkgs; [
          zsh # shell for running the script
          gcc # compiler
          gnumake # add make
          gdb # stepping through code
          gef # extension of gdb
          valgrind # memory debugger
          bear # generated a compilation database

          python3 # for plotting
          python312Packages.pandas
          python312Packages.numpy
          python312Packages.matplotlib
          python312Packages.imageio
        ];

        shellHook = ''
          echo "Welcome to your C development shell!"
          exec ${myShell}
        '';
      };
    };
}
