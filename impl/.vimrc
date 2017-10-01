" Setting impl files as cpp files too
au BufNewFile,BufRead *.impl set filetype=cpp

let g:ycm_confirm_extra_conf=0

" YCM only for Diagnostics
"
let g:ycm_enable_diagnostic_signs = 1
let g:ycm_enable_diagnostic_highlighting = 0
let g:ycm_always_populate_location_list = 1 "default 0
let g:ycm_open_loclist_on_ycm_diags = 1 "default 1

let g:ycm_server_use_vim_stdout = 0 "default 0 (logging to console)
let g:ycm_server_log_level = 'info' "default info
let g:ycm_goto_buffer_command = 'horizontal-split'
  \ "[ 'same-buffer', 'horizontal-split', 'vertical-split', 'new-tab' ]
let g:ycm_filetype_whitelist = { '*': 1 }


let g:ycm_register_as_syntastic_checker = 1 "default 1
let g:Show_diagnostics_ui = 1 "default 1




nnoremap <F6> :YcmForceCompileAndDiagnostics <CR>
nnoremap <F7> :YcmDiags <CR>
map <F9> :YcmCompleter FixIt<CR>


