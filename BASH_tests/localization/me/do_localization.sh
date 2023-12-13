#!/bin/bash
set -eEuo pipefail

#
# Creates a file with all $"..." strings
#
bash --dump-po-strings localized.sh > localized.sh.po.template

#
# For each language, in this case we're just doing French and Spanish, create a file
#
mkdir -p new
mkdir -p prev
fr_new=new/localized.sh.fr.po
cp localized.sh.po.template ${fr_new}

#
# Now the human labor part, we have to do the translations
#
read -p "Now add the French translations"
vim ${fr_new}

#
# Finally, we create the files that will be read by BASH when it evaluates our
# $"..." strings.
#
fr_prev=prev/localized.sh.fr.po
fr_mo=locale/fr/LC_MESSAGES/localized.sh.mo
if [[ -e ${fr_prev} ]] ; then
    # Merge INTO ${fr_prev}
    msgmerge --update ${fr_prev} ${fr_new}
else
    mkdir -p $(dirname ${fr_mo})
fi
msgfmt -o ${fr_mo} ${fr_prev}

# We can do the same for spanish
# cp localized.sh.po.template tmp/localized.sh.es.po
# read -p "Now add the Espagnol translations"
# vim tmp/localized.sh.es.po
# es=locale/fr/LC_MESSAGES/localized.sh.mo
# if [[ -e ${es} ]] ; then
#     msgmerge --update ${es} tmp/localized.sh.es.po
# else
#     mkdir -p $(dirname ${es})
#     msgfmt -o ${es} tmp/localized.sh.es.po
# fi




