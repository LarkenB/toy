{
  pkgs ? import <nixpkgs> {}
}:
let
  vimrcConfig = {
    customRC = ''
      "Start terminal if not open in file
      autocmd VimEnter * if empty(bufname(''')) | exe "terminal" | endif
      autocmd BufEnter * let buf=bufname() | if isdirectory(buf) | exec 'terminal' | call feedkeys('icd' ".buf."\<CR> | endif

      set nu
      colorscheme molokai
      set tabstop=2
      set shiftwidth=2

			tnoremap <ESC>  <C-\><C-n>
    '';
    
    packages.myPackages = with pkgs.vimPlugins; {
      start = [
        # Style
        vim-colorschemes
        vim-airline 
        vim-airline-themes

        # Errors
        ale 
      ];
    };
  };
in
pkgs.mkShell {
  name = "devkit";
  buildInputs = [
    (pkgs.neovim.override {
      configure = vimrcConfig; 
    })
		pkgs.bat
  ];
  shellHook = ''
    echo "Entered Dev Kit"
  '';
}
