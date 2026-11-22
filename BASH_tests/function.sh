shopt -s expand_aliases
alias hello=+
alias bonjour=+
alias function=bingbong

hello() {
   echo "body of function hello()"
}

function bonjour() {
   echo "body of function bonjour()"
}

:(){
   echo "Yes, you can indeed name your function ':' in bash"
}
--(){
   echo "Yes, you can indeed name your function '__' in bash"
}

declare -fp bonjour
declare -fp hello
declare -fp +
