
echo "=== DOESNT_EXIST"
if $DOESNT_EXIST ; then
    echo "IN THE IF"
else
    echo "IN THE ELSE"
fi

echo "=== EMPTY_STRING_VAR"
EMPTY_STRING_VAR=""
if $EMPTY_STRING_VAR ; then
    echo "IN THE IF"
else
    echo "IN THE ELSE"
fi

echo "=== EMPTY_VAR"
EMPTY_VAR=
if $EMPTY_VAR ; then
    echo "IN THE IF"
else
    echo "IN THE ELSE"
fi

echo "=== EMPTY STRING LITTERAL"
if "" ; then
    echo "IN THE IF"
else
    echo "IN THE ELSE"
fi

echo "=== Completely empty if"
if  ; then
    echo "IN THE IF"
else
    echo "IN THE ELSE"
fi


