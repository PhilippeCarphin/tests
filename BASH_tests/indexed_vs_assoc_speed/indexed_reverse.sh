
_ord_soumet_options=(
    -addstep -altcfgdir -args -as -c -clone -cm -coschedule -cpus
    -custom -d -display -e -epilog -firststep -geom -image -immediate -iojob -jn
    -jobcfg -jobfile -jobtar -keep -l -laststep -listing -m -mach -mail -mpi
    -node -noendwrap -norerun -norset -nosubmit -notify -o -op -p -postfix -ppid
    -preempt -prefix -prio -project -prolog -q -queue -rerun -resid -rsrc
    -retries -seqno -share -shell -smt -splitstd -sq -ssmuse -step -sys -t -tag
    -threads -tmpfs -v -w -waste -with -wrapdir -xterm
)

declare -ga _ord_soumet_option_descriptions=(
    "add co-scheduled step"
    "alternate config dir"
    "arguments for job script"
    "submit job as another user"
    "same as cpus"
    "max number of clones (0=none) "
    "memory (K/M/G bytes)"
    "coscheduled job"
    "processes(MxN) and cpus/process(O) MxNxO "
    "override CpusPerNode from the machine config file "
    "custom parameter for sys config"
    "synonym for mach "
    "X windows display"
    "controls -e flag"
    "job epilog"
    "allow exceeding the original node count"
    "sum of previous job steps"
    "MPI geometry file"
    "number of GPUs per node"
    "OS image to run job (if supported)"
    "do not batch, use ssh with batch environment"
    "IO weight (0-9) 0=none, 9=IO hog"
    "job name"
    "job configuration commands"
    "name of file to submit"
    "name of tar file from nosubmit"
    "keep job and script file at end of run"
    "job already has wrappers"
    "last co-scheduled step"
    " directory for listings "
    "same as cm"
    " target machine "
    "email address"
    " MPI job "
    "job addressing"
    "job end signal not required"
    "declare that the job is not rerunnable"
    "do not use cpu resource sets for task binding (LoadLeveler only)"
    " do not submit "
    ""
    "same as args"
    "job is operational flag"
    "same as mpi"
    "listing postfix"
    ""
    "allow job to be preempted"
    "listing prefix"
    "batch system specific job priority"
    "batch system specific project"
    "job prolog"
    "same as queue"
    "quality of service (Slurm only)"
    "specify a specific queue/class or queue:project if project otherwise undefined"
    "declare that the job is rerunnable"
    "LoadLeveler reservation id"
    "set of needed resources"
    "set of maximum number of retries"
    "sequence number of first job (clones) "
    "can share node and/or be split across nodes e|s|p"
    "job shell for batch job"
    "smt factor"
    "split stderr/stdout in listings"
    "alternate queue for submission"
    "add extra environment"
    "job step name"
    "system mode"
    "job execution time (seconds)"
    "job tracking tag"
    "number of threads per cpu(sge only)"
    "fast temporary space (MB)"
    "verbose"
    "same as t but in mins"
    "send e-mail warning that many seconds before wallclock expires"
    "acceptable percentage of wasted cpus"
    "batch subsystem to use (GridEngine LoadLeveler UnixBatch)"
    "job wrapper directories"
    "start an xterm in job"
)

n=${#_ord_soumet_options[@]}
for((j=0;j<1000;j++));do
    # for((i=0;i<${n};i++));do
    for((i=$((n-1));i>=0;i--));do
        c=${_ord_soumet_options[i]}
        d=${_ord_soumet_option_descriptions[i]}
    done
done

