#!/bin/bash
################################################################################
# Will check branch develop on all repos of repo_home unless repos is set
   repo_home=/home/ops/afsi/phc/Documents/GitCMC
   repos="maestro maestro-manager maestro-utils xflow"
#
# supply argument "short" to get only the summary of commits by which origin is
# behind or ahead.
#
# TODO Supply repo_home and repos as options
################################################################################
log_cmd="log --oneline --graph --decorate -15"

git_fetch_branches(){
   directory=$1
   cd $directory
   for remote in $(git remote) ; do
      for branch in master develop ; do
         git fetch $remote $branch
      done
   done
   cd ..
}
git_check(){
   directory=$1
   printf "\033[1;31m\n==================== $directory status ===================\033[0m\n"
   cd $directory
   git status
   git $log_cmd
   cd ..
}

git_status_develop(){
   directory=$1
   printf "==================== $directory status ===================\n"
   cd $directory
   pop_stash=0
   branch="$(git symbolic-ref HEAD)"
   branch="${branch##refs/heads/}"

   # Checkout develop, save to stash if necessary
   if [ "$branch" != develop ] ; then
      var="$(git checkout develop 2>&1)"
      if [ "$?" = 1 ] ; then
         git stash save > /dev/null 2>&1
         pop_stash=1
         git checkout develop > /dev/null 2>&1
      fi
   fi

   # show status of branch develop
   status="$(git status)"
   state="$( echo $status | grep up-to-date --only-matching )"
   info="$( echo $status | grep 'Your branch .* commits\?\.' --only-matching )"
   number="$( echo $status | grep '[0-9]\+' --only-matching )"
   info=${info/"Your branch"/Local branch develop}
   if [ "$state" = up-to-date ] ; then
      echo Local branch develop is up to date
   else
      echo $info
      git log --oneline --decorate --graph -$(($number + 1))
   fi

   # Pop from stash and checkout previous branch
   if [ "$branch" != develop ] ; then
      git checkout $branch > /dev/null 2>&1
      if [ "$pop_stash" = 1 ] ; then
         git stash pop > /dev/null 2>&1
      fi
   fi
   cd ..
}

get_repos() {
   repo_home=$1
   directories="$( ls -d $repo_home/*/ )"

   for dir in $directories ; do
      cd $dir && git status > /dev/null 2>&1
      if [ "$?" = 0 ] ; then
         repos="$repos $dir"
      fi
   done
}

if [ "$repos" = "" ] ; then
   get_repos $repo_home
fi

cd $repo_home


echo -n "Fetching remote branches ..."
for repo in $repos ; do
   git_fetch_branches $repo >/dev/null 2>&1
done
echo

if [ "$1" = long ] ; then
   for repo in $repos ; do
      git_check $repo
      read -n1 -p"Press any key to continue"
   done
   printf "\033[1;35m\n==================== SUMMARY  ===================\033[0m\n"
fi


for repo in $repos ; do
   git_status_develop $repo
done

