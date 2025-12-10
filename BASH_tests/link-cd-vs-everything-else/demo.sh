#!/usr/bin/env bash

main(){
	local this_dir=$(cd -P $(dirname $0) && pwd)
	local p=a/lc/d
	local x=../../b

	section "tree of directory ${this_dir##*/}"
	cd ${this_dir}
	tree a
	printf "\n"

	section "Question"
	cat <<-EOF
		When we cd to '$p', what does '../..' mean relative to that?
		Is it 'a' because each '..' cancels out one token of '$p' or
		is it 'a/b' because it is the parent of the parent of the
		directory we find ourselves in?
	EOF
	cd $p


	explanation

	demonstration

}

explanation(){
	section "EXPLANATION"

	reldir=a/lc
	real_dir=$(cd -P . && pwd)
	real_reldir=${real_dir#${this_dir}/}
	printf "We are in ${reldir} but really we are in '${real_reldir}' since lc -> c/b\n"

	dot_dot_fs=$(realpath $PWD/../..)
	dot_dot_cd=$(cd ../.. && pwd)
	cat <<-EOF

		The directory we are in only has one parent and that is 'c', which only has
		one parent and that parent is 'b':

		        ls ../..' lists the content of '${dot_dot_fs/"${this_dir}"/'${this_dir}'}'"

		But if we do 'cd a/lc', we kinda want 'cd ..' to bring us back to 'a'. So
		'cd' cares about 'how we got there' and PWD=${PWD/"${this_dir}"/'${this_dir}'}
		has this information.

		'cd' works only by string manipulation on \$PWD where '..' simply "consumes" or
		cancels out the preceding path component \$PWD (unless we use 'cd -P')

		        'cd ../..' goes to '${dot_dot_cd/"${this_dir}"/'${this_dir}'}'"
	EOF
}

demonstration(){
	section "DEMONSTRATIONS"


	printf "\n==> ls ../..\n"
	ls ../..
	printf "Note: does not contain 'b' (cause it *is* b)\n"


	printf "\n==> (cd ../.. ; ls)\n"
	(cd ../..;  ls)
	printf "Note: does yes contain 'b'\n"


	printf "\n==> [[ -d $x ]]\n"
	[[ -d $x ]] ; result $?
	printf "Note: [[ -d ]] does filesystem resolution\n"


	# man realpath: "All but the last component must exist"
	# realpath $x gives ${this_dir}/a/b/b and since only the last component doesn
	# exist, realpath doesn't fail, but the [[ ==>d ]] fails.
	printf "\n==> [[ -d \$(realpath $x) ]]\n"
	[[ -d $(realpath $x) ]] ; result $?
	printf "Note: realpath does filesystem resolution\n"


	printf "\n==> (cd $x)\n"
	(cd $x) ; result $?
	printf "Note: cd does string manipulation\n"


	printf "\n==> [[ -d \$(bash_normpath \$PWD/$x) ]]\n"
	[[ -d $(bash_normpath $PWD/$x) ]] ; result $?
	pwd_x=$PWD/$x
	normpath_pwd_x=$(bash_normpath ${PWD}/$x)
	cat <<-EOF
		Note: bash_normpath does string manipulation\n"
		        \$(bash_normpath ${pwd_x/"${this_dir}"/'${this_dir}'})\n"
		        -> ${normpath_pwd_x/"${this_dir}"/'${this_dir}'}\n"
		      After that we have a path without '..'s and [[ -d ]] can't be confused\n"
	EOF


	printf "\n==> [[ -d \$(cd $x && pwd) ]]\n"
	[[ -d $(cd $x && pwd) ]] ; result $?
}

result(){
	if (($1 == 0)) ; then printf "SUCCESS\n" ; else printf "FAIL\n" ; fi
}
section(){
	local title line
	printf -v title "${1}"
	printf -v line "%${#title}s" ""
		printf "\n%s\n%s\n\n" "${title}" "${line// /=}"
	}
# BASH implementation of python's os.path.normpath function.
bash_normpath(){
	local start_sep
	case "${1}" in
		///*) start_sep='/' ;;
		//*)  start_sep='//' ;;
		/*)   start_sep='/' ;;
	esac

	local IFS='/'
	local new_tokens=()
	local i=0

	for tok in ${1} ; do
		if [[ "${tok}" == '.' ]] || [[ "${tok}" == "" ]] ; then
			continue
		fi
		if [[ "${tok}" != '..' ]] \
		   || ( [[ -z "${start_sep}" ]] && (( i == 0 )) ) \
		   || (  (( ${#new_tokens[@]} >= 1)) \
		         && [[ ${new_tokens[i-1]} == '..' ]] ) ; then
			new_tokens[i++]=${tok}
		elif (( i >= 1 )) ; then
			((i--))
			# See nullglob.bash for why there are quotes here
			unset 'new_tokens[i]'
		fi
	done
	# Note this works because IFS='/'.  the ${arr[*]} joins
	# the elements of the array 'arr' using the first char of IFS.
	final="${start_sep}${new_tokens[*]}"
	printf "${final:-.}\n"
}

main "$@" >&2
