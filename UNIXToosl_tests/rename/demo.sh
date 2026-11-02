if command -v ci-decorate &>/dev/null ; then
    { ci-decorate | bash ; } <<-EOF
		ls
		rename .md .txt *.md
		ls
		rename .txt .md *.txt
		ls
	EOF
else
    rename .md .txt *.md
    ls
    rename .txt .md *.txt
    ls
fi

