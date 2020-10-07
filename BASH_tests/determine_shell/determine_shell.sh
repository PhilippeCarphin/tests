if ((${#BASH_SOURCE[@]})) ; then
	echo ${BASH_SOURCE[@]}
	echo "The BASH_SOURCE array has at least one element: we are BASH"
elif ((${#KSH_VERSION[@]})) ; then
	echo ${KSH_VERSION[@]}
	echo "The KSH_VERSION array has at least one element: We are KSH"
fi

test_if_double_parens(){
	if (($1)) ; then
		echo "if (($1)) goes into the if"
	else
		echo "if (($1)) goes into the else"
	fi
}
echo ==================================
echo "Arithmetic context 'succeeds' if expression inside evaluates to non-zero value"
test_if_double_parens 0
test_if_double_parens 42
test_if_double_parens -30

return_func(){
	return $1
}

test_return_func(){
	if (exit $1) ; then
		echo "if (exit $1) goes into the if"
	else
		echo "if (exit $1) goes into the else"
	fi
}
echo ==================================
test_return_func 0
test_return_func 42

