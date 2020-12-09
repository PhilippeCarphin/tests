export ORDENV_SITE_PROFILE=20190814
export ORDENV_COMM_PROFILE=eccc/20191002
export ORDENV_GROUP_PROFILE=eccc/cmc/1.8
source /fs/ssm/main/env/ordenv-boot-20200204.sh
. ssmuse-sh -x hpco/exp/jobsubi/jobsubi-0.3

jobsubi $@
