vundle_code="
================= VUNDLE STUFF ( KEEP AT START OF FILE ) =======================
set nocompatible              \" be iMproved, required
filetype off                  \" required

\" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'

\" All of your Plugins must be added before the following line
call vundle#end()            \" required
filetype plugin indent on    \" required
============================ END VUNDLE STUFF ==================================
"
# clone vundle
if [ ! -e $HOME/.vim/bundle/Vundle.vim ] ; then
   git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
fi

# Check if vundle code is already there
if [ "$(grep "vundle#begin" "$HOME/.vimrc" 2>/dev/null)" != "" ] ; then
   echo Vundle code is already in vimrc file
   exit 0
fi

# move vimrc to backup
if [ -f $HOME/.vimrc ] ; then
   mv $HOME/.vimrc $HOME/.vimrc.bak
fi

# create new vimrc with vundle stuff
echo "$vundle_code" > $HOME/.vimrc

# append old vimrc to new one
if [ -f $HOME/.vimrc.bak ] ; then
   cat $HOME/.vimrc.bak >> $HOME/.vimrc
fi

