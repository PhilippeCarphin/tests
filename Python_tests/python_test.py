#!/usr/bin/python
import sys

"""

This file was to show a friend how to do basic option parsing in python.  It
should be noted that there is actually an option parsing module that does a
similar job as the getopt.c module in C that should actually be used instead of
doing things manually like this.

"""

def print_usage():
    print("This ... is how you should use this script")

if __name__ == "__main__":
    print "printing the array argv"
    for s in sys.argv:
        print s

    option1_value = "Default"
    option2_value = "" #
    option3_value = ""
    on_off_option = False

    i = 1
    # commencer i=1 parce que argv[0] c'est le nom du programme si t'as fait
    # ./monfichier.py
    # ou le nom du fichier si t'as fait
    # python monfichier.py
    # pour pouvoir faire ./monfichier.py, il faut juste mettre la ligne
    # #!/usr/bin/python comme premiere ligne du fichier
    positional_args = []
    while i < len(sys.argv):
        if sys.argv[i] == "--option1":
            option1_value = sys.argv[i + 1]
            i = i+1
        elif sys.argv[i] == "--option2":
            option2_value = sys.argv[i+1]
            i = i+1
        elif sys.argv[i] == "--option3":
            option3_value = int(sys.argv[i+1])
            i = i+1
        elif sys.argv[i] == "--on_off_option":
            on_off_option = True
            # option sans argument donc on incr/mente pas i.
        elif sys.argv[i][0:2] == "--":
            print_usage()
            # http://stackoverflow.com/questions/2052390/manually-raising-throwing-an-exception-in-python
            raise Exception("Unknown option {}.".format(sys.argv[i]))
            #ou bien quit(1)
        else:
            positional_args.append(sys.argv[i])

        i = i+1

    print "Option option1_value : " + option1_value
    print "Option option2_value : " + option2_value
    print "Option option3_value : " + str(option3_value)
    print "Positionnal arguments " + str(positional_args)

