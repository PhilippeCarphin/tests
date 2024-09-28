the_coproc(){
    while read cmd arg ; do
        case ${cmd} in
            sleep*) echo "(INFO) ${FUNCNAME[0]} sleeping ${arg}" >&2 ; sleep ${arg} ;;
            end) echo "(INFO) ${FUNCNAME[0]} returning ${arg}" >&2 ; return ${arg} ;;
            echo) echo "${FUNCNAME[0]} ${arg}" >&1 ;;
        esac
    done
    echo "(INFO) ${FUNCNAME[0]}(${BASHPID}): My stdin was closed" >&2
}

coproc macaroons { the_coproc ; }

echo "(INFO) The coprocess array: ${macaroons[@]}"
echo "(INFO) The PID of the coprocess is ${macaroons_PID}"
echo "(INFO) This process is ${BASHPID}"
# Read the output off the first file descriptor of the array.
while read -p "Enter a command (sleep N, close, echo 'message', 'end [N]') > " cmd arg ; do
    # read resp <&${macaroons[0]}
    # echo "resp='${resp}'"
    case ${cmd} in
    # Tell the coproc to end by sending it 'end' which it will react to by
    # doing 'return'
    end) echo ${cmd} ${arg} >&${macaroons[1]} ; break ;;
    # Tell the coproc to end by closing its input file descriptor
    # which will stop the loop the next time it tries to read
    close) exec {macaroons[1]}>&- ; break ;;
    sleep) echo ${cmd} ${arg} >&${macaroons[1]} ;;
    echo) echo ${cmd} ${arg} >&${macaroons[1]}
          read resp <&${macaroons[0]}
          echo "resp = '${resp}'"
          ;;
    esac
    sleep 0.2
done

echo "(INFO) Waiting for coproc to finish"
wait ${macaroons_PID}
echo "(INFO) Main: coproc returned $?"
