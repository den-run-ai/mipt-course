" ------- vimrc
map ,u :source ~/.vimrc<CR>
map ,v :e ~/.vimrc<CR>

" ------- substitute (,s = empty; .s = current word)
map ,s :.,$s///gcI<Left><Left><Left><Left><Left>
map .s :.,$s/\<\>//gcI<Left><Left><Left><Left>

" ------- status line
set laststatus=2
set statusline=%f%M%R%Y%=\ \ \ %{strftime(\"%H:%M\",localtime())}\ \ %P\ %3c\ %4l/%L\

set autowrite " save file when switching to another buffer
" ------- F2=save
map OQ :w<CR>
imap OQ <C-o>:w<CR>

" ------- F3=toggle paste
map OR :set paste!<CR>
imap OR <C-o>:set paste!<CR>

" ------- F6=toggle linenumbers
map OS :set nu!<CR>
imap OS <C-o>:set nu!<CR>

" ------- Alt-N -- switch to N-th buffer
map 1 :b 1<CR>
map 2 :b 2<CR>
map 3 :b 3<CR>
map 4 :b 4<CR>
map 5 :b 5<CR>
map 6 :b 6<CR>
map 7 :b 7<CR>
map 8 :b 8<CR>
map 9 :b 9<CR>
map 0 :b 0<CR>

" ------- Disable Ctrl-Z, remap to undo
map   u
imap  <C-o>u

" ------ Jumping to the previous position in file
:au BufReadPost * if line("'\"") > 0 && line("'\"") <= line("$") | exe "normal g'\"" | endif

" ------ Random stuff
color darkblue
syntax on " syntax highlighting
set encoding=utf-8
set mouse=
set backspace=2
set cindent " c-style indents?
set cinkeys=0{,0},0),:,0#,o,O,e,!,!<S-Tab>
set cino=c1s
set ignorecase
set smartcase
set title
set restorescreen
set foldmethod=marker
set scrolloff=5
set incsearch
set hlsearch
set ww=<,>,[,]

set nowrap
set sidescroll=5
set nows
set shiftwidth=2
set softtabstop=2
set expandtab
set nu " print linenumbers

" Don't expand tabs in Makefiles
autocmd FileType make setlocal noexpandtab

" ??? never used it
map [17~ :cnext<CR>
map [18~ :cprevious<CR>
map [15~ :make<CR>

" toggle between .c/.cpp/.cc and .h
map ,h :e %:r.h<CR>
map ,H :e %:r.c*<CR>

" import Google Code style
source ~/.googlecodestyle.vim

" ------- Highlighting columns 81 and 82 and EOL whitespaces
"   This makes characters in the 81th and 82nd columns (or whatever the two columns are after &textwidth) white text on a red background, thus making it easy to spot lines that might fail Google coding style conventions. It does not affect files that have no textwidth (i.e., zero) set.
    function! HighlightTooLongLines()
      highlight OverLength ctermbg=red ctermfg=white guibg=#592929
      if &textwidth != 0
        exec 'syntax match OverLength /\%<' . (&textwidth + 3) . 'v.\%>' . (&textwidth + 1) . 'v/'
      endif
    endfunction

    augroup filetypedetect
    au BufNewFile,BufRead * call HighlightTooLongLines()
    augroup END

    function! HighlightEOLWS()
      highlight EolWs ctermbg=red ctermfg=white guibg=#592929
      syntax match EolWs /\s\+$/
    endfunction

    augroup filetypedetect
    au BufNewFile,BufRead * call HighlightEOLWS()
    augroup END

set ww=b,s,<,>,[,] " cursor moves across lines
" TODO ? set listchars=tab:\ \ ,trail:\ ,extends:»,precedes:«
set listchars=tab:\ \ ,extends:»,precedes:«


map ,q :%s/\s\+$//eg<CR>

set textwidth=80

" ----- open the filename under a cursor on ";f"
set path=,,.
function! Gfw()
  let b = bufnr('')
  normal mz
  let b = bufnr('')
  wincmd w
  exe "b " . b
  normal `zgF
endfun

nnoremap ;f :call Gfw()<cr>

" TODO find better colors?
highlight DiffChange cterm=none ctermfg=White ctermbg=Magenta gui=none guifg=White guibg=Magenta

" Add project-specific settings like this
:au BufNewFile,BufRead */drmemory/* setlocal shiftwidth=4 tabstop=4 softtabstop=4 expandtab textwidth=100
