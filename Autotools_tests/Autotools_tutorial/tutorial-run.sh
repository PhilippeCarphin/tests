
runcmd(){
    printf "\033[1;32m==> Running '\033[1;37m%s\033[1;32m'\033[0m\n" "$*"
    "$@"
}
runcmd autoreconf --install

runcmd ./configure --prefix=$PWD/localinstall

runcmd make install
