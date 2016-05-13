#!/bin/ksh
fullnode=/gdps_verif/SCORES_VS_ANALYSIS/gdps_2.5deg_burp_db
nodeWithExt=/path/to/node/nodename.+12+0
lots_o_periods=/sample_module/Loop_Examples/outerloop/innerloop/has.period.in.name.2.5km.48.9psi.29kg.1729.+0+11

# the node coming in has the following pattern
# full_nodepath.ext_value...we separate the node from
# the extension value
parsePath() {
   echo =================
   fullnode=$1
   expected_ext=$2

   # Parse $fullnode into nodeContainer, nodeLeaf, and nodeExt
   # fullnode has the form /path/to/node/nodeLeaf.ext where ext is defined by ext_re :
subext_re='\(+[0-9A-Za-z^_]\+\)'                                        # plus sign followed by a number
ext_re='\.'$subext_re'\+$'                                      # a dot followed by one or more subextensions at end of string
nodeContainer=${fullnode%/*}                                    # Everything until the last slash
nodeLeafWithExt=${fullnode##*/}                                 # Everything after the last slash
nodeExt=$(echo $nodeLeafWithExt | grep --only-matching $ext_re) # Part of nodeLeaf matching ext_re
nodeExt=${nodeExt#.}                                            # Remove the dot
nodeLeaf=$(echo $nodeLeafWithExt | sed s/$ext_re//)             # nodeLeaf with extension removed.

   echo fullnode      = $fullnode
   # echo nodeContainer = $nodeContainer
   # echo nodeLeaf      = $nodeLeaf
   echo nodeExt       = $nodeExt
   if [[ "$nodeExt" == "$expected_ext" ]] ; then
      echo TEST PASSED
   else
      echo TEST FAILED: Ext should be \"$expected_ext\"
   fi
   echo =================

}

parsePath $fullnode
# parsePath $nodeWithExt
# parsePath $lots_o_periods

# With period in a loop
node=/sample_module/Loop_Examples/outerloop/innerloop/has.period.in.name.2.5km.48.9psi.29kg.1729.+0+7
# Without period inside a loop
node2=/sample_module/Loop_Examples/outerloop/innerloop/innerloopTask.+0+7
# With period (not in a loop)
node3=/sample_module/Different_Hosts/I.have.aperiod.in.my.name
# Without period
node4=/sample_module/Different_Hosts/LinuxHosts/PolluxTask

parsePath $node +0+7
parsePath $node2 +0+7
parsePath $node3 ""
parsePath $node4 ""

NPassTask=/take/me/down/to/the_ball_game.+9th_inning
parsePath $NPassTask +9th_inning

filename=/ah/que/la/neige_a_neige.ma_vitre_est_un_jardin_de_givre
parsePath $filename ""

with_carret=/facing/the/animal/ye-eah/lost_in_a_ritual.+^carret_098
parsePath $with_carret "+^carret_098"
