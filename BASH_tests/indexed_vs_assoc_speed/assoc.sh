_ord_soumet_options=(
    -addstep -altcfgdir -args -as -c -clone -cm -coschedule -cpus
    -custom -d -display -e -epilog -firststep -geom -image -immediate -iojob -jn
    -jobcfg -jobfile -jobtar -keep -l -laststep -listing -m -mach -mail -mpi
    -node -noendwrap -norerun -norset -nosubmit -notify -o -op -p -postfix -ppid
    -preempt -prefix -prio -project -prolog -q -queue -rerun -resid -rsrc
    -retries -seqno -share -shell -smt -splitstd -sq -ssmuse -step -sys -t -tag
    -threads -tmpfs -v -w -waste -with -wrapdir -xterm
)

declare -gA _ord_soumet_option_descriptions=(
    [-addstep]="add co-scheduled step"
    [-altcfgdir]="alternate config dir"
    [-args]="arguments for job script"
    [-as]="submit job as another user"
    [-c]="same as cpus"
    [-clone]="max number of clones (0=none) "
    [-cm]="memory (K/M/G bytes)"
    [-coschedule]="coscheduled job"
    [-cpus]="processes(MxN) and cpus/process(O) MxNxO "
    [-cpuspernode]="override CpusPerNode from the machine config file "
    [-custom]="custom parameter for sys config"
    [-d]="synonym for mach "
    [-display]="X windows display"
    [-e]="controls -e flag"
    [-epilog]="job epilog"
    [-exceednc]="allow exceeding the original node count"
    [-firststep]="sum of previous job steps"
    [-geom]="MPI geometry file"
    [-gpus]="number of GPUs per node"
    [-image]="OS image to run job (if supported)"
    [-immediate]="do not batch, use ssh with batch environment"
    [-iojob]="IO weight (0-9) 0=none, 9=IO hog"
    [-jn]="job name"
    [-jobcfg]="job configuration commands"
    [-jobfile]="name of file to submit"
    [-jobtar]="name of tar file from nosubmit"
    [-keep]="keep job and script file at end of run"
    [-l]="job already has wrappers"
    [-laststep]="last co-scheduled step"
    [-listing]=" directory for listings "
    [-m]="same as cm"
    [-mach]=" target machine "
    [-mail]="email address"
    [-mpi]=" MPI job "
    [-node]="job addressing"
    [-noendwrap]="job end signal not required"
    [-norerun]="declare that the job is not rerunnable"
    [-norset]="do not use cpu resource sets for task binding (LoadLeveler only)"
    [-nosubmit]=" do not submit "
    [-notify]=""
    [-o]="same as args"
    [-op]="job is operational flag"
    [-p]="same as mpi"
    [-postfix]="listing postfix"
    [-ppid]=""
    [-preempt]="allow job to be preempted"
    [-prefix]="listing prefix"
    [-prio]="batch system specific job priority"
    [-project]="batch system specific project"
    [-prolog]="job prolog"
    [-q]="same as queue"
    [-qos]="quality of service (Slurm only)"
    [-queue]="specify a specific queue/class or queue:project if project otherwise undefined"
    [-rerun]="declare that the job is rerunnable"
    [-resid]="LoadLeveler reservation id"
    [-rsrc]="set of needed resources"
    [-retries]="set of maximum number of retries"
    [-seqno]="sequence number of first job (clones) "
    [-share]="can share node and/or be split across nodes e|s|p"
    [-shell]="job shell for batch job"
    [-smt]="smt factor"
    [-splitstd]="split stderr/stdout in listings"
    [-sq]="alternate queue for submission"
    [-ssmuse]="add extra environment"
    [-step]="job step name"
    [-sys]="system mode"
    [-t]="job execution time (seconds)"
    [-tag]="job tracking tag"
    [-threads]="number of threads per cpu(sge only)"
    [-tmpfs]="fast temporary space (MB)"
    [-v]="verbose"
    [-w]="same as t but in mins"
    [-warnexpire]="send e-mail warning that many seconds before wallclock expires"
    [-waste]="acceptable percentage of wasted cpus"
    [-with]="batch subsystem to use (GridEngine LoadLeveler UnixBatch)"
    [-wrapdir]="job wrapper directories"
    [-xterm]="start an xterm in job"
)

for((j=0;j<1000;j++));do
    for((i=0;i<${#_ord_soumet_options[@]};i++));do
        c=${_ord_soumet_options[i]}
        d=${_ord_soumet_option_descriptions[$c]}
    done
done
