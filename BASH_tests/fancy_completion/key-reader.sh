#!/usr/bin/env -S bash -o errexit -o nounset -o errtrace -o pipefail -O inherit_errexit -O nullglob -O extglob


while read -s -N 1 b ; do
    printf "(((%q))) %d\n" "${b}" "${#b}"
    case "$b" in
        $'\020') printf "[C-p]-bing-bong\n" ;;
        $'\e')
            read -r -s -t 0.1 -n 2 bing || true
            printf "<<<%q>>>\n" "${bing}"
            case "$bing" in
                '[A') printf "up-arrow-bing-bong\n" ;;
                '[B') printf "down-arrow-bing-bong\n" ;;
                '') printf "escape-BING-BONG\n" ;;
            esac
            ;;
    esac
done
