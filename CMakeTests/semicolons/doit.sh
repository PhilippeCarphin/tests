cd -P $(dirname $0)
rm -fv test*

cmake -S . -B build
show(){
    echo ==== $1 ====
    cat $1
}

for t in test*; do
    show $t
done
