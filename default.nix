
{ pkgs ? import <nixpkgs> {} }:

(pkgs.buildFHSUserEnv {
  name = "loki-fhs";
  targetPkgs = pkgs: (with pkgs;
    [ 
      glibc.static
      git
      gcc
      cmake
      fontconfig
      libxml2.dev
      zlib
      mesa_glu
      cmakeCurses
      glfw
      pkgconfig
      freeglut
      libglvnd
      libglvnd.dev
      mesa_glu
      openssl
      curl
      gtk3
      pkgconfig
      bintools-unwrapped
    ]) ++ (with pkgs.xorg;
    [
      libX11.dev
      libX11
      libXdamage
      libXext
      libXfixes
      libXv
      libXrandr
      libXrandr.dev
      libXinerama
      libXinerama.dev
      libxkbfile
      libxkbfile.dev
      libxcb
      libxcb.dev
      libXcursor
      libXcursor.dev
      xinput
      libXi
      libXi.dev
      libICE
      libSM
      libXres
      libICE.dev
      libSM.dev
      libXres.dev
      libXext
      libXext.dev
      xorgproto
      xcbproto
      libXau
      libXau.dev
      libXdmcp
      libXdmcp.dev
      
    ]);
  multiPkgs = pkgs: (with pkgs;
    [ 
    ]);
  runScript = "bash";
}).env
