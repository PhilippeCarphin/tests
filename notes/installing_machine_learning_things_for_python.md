  # Without sudo I was getting errors of the permission-denied variety
  777  pip upgrade
  778  pip install theano
  779  pip install --upgrade pip

  # Worked
  780  sudo pip install --upgrade pip
  781  sudo pip install theano
  784  sudo pip install keras

  # Did not work g++ error:/usr/lib/rpm/redhat/redhat-hardened-cc1: No such file
  # or directory
  785  sudo pip install matplotlib

  # But stack overflow
  # http://stackoverflow.com/questions/34624428/g-error-usr-lib-rpm-redhat-redhat-hardened-cc1-no-such-file-or-directory
  789  sudo dnf install redhat-rpm-config

  # Now it worked
  790  sudo pip install matplotlib
  791  python
  792  sudo pip install tensorflow
  793  python
  794  history >> ../notes/installing_machine_learning_things_for_python.md
