


while getopts "yf:v:" the_opt "$@" ; do
    echo "========== the_opt=${the_opt} ==========="
    echo "========== \$@ = $@ ============="
    echo "========== OPTIND = ${OPTIND} =========="
    case ${the_opt} in
        f)
            echo "Fruit = ${OPTARG}"
            ;;
        v)  echo "Vegetable = ${OPTARG}"
            ;;
        ?)
            echo "Unknown option"
            exit 12
            ;;
    esac
done
