trap 'echo "original exit trap"' EXIT

(
    echo "Begin subshell, setting exit trap"
