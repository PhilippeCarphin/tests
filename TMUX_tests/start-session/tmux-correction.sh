groups=$(ls ./INF2705-TP4--266788)
for g in $groups ; do
	pushd ./INF2705-TP4--266788/$g
	tmux new-session \; source-file ../../tmux-session.tmux
	popd
	if [ -e ./stop.m ] ; then
		exit 1
	fi
done
