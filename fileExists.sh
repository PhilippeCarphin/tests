# Just a little test of this way of testing the existence of a file.
if [ -e $HOME/.vim/bundle/Vundle.vim ] ; then
   echo FILE EXISTS
else
   echo FILE DOESN\'T EXIST
fi

if [ -e $HOME/.vim/bundle/asdfasdf.vim ] ; then
   echo FILE EXISTS
else
   echo FILE DOESN\'T EXIST
fi

if [ ! -e $HOME/.vim/bundle/asdfasdf.vim ] ; then
   echo not FILE EXISTS
else
   echo not FILE DOESN\'T EXIST
fi
