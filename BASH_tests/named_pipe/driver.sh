
tmpdir=$(mktemp -d)
stderr=${tmpdir}/stderr_fifo
mkfifo ${stderr}

./main.sh 2>${stderr} | ./filter.sh ${stderr}

echo "tmpdir=${tmpdir}"
rm -rf "${tmpdir}"

