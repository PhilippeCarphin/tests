printf "Select process to attach to\n"
psline=$(pgrep -u $USER "$@" | xargs -r ps -f | tui-selector)
pid=$(echo ${psline} | awk '{print $2}')

if [[ -n ${pid} ]] ; then
    gdb -q -tui -p ${pid}
fi

