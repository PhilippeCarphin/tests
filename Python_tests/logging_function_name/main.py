import logging

#
# From https://stackoverflow.com/a/20112491/5795941
#
# Looking for a way to leave debug messages that contain the function name.
# The typical way to answer this question is to look for "get name of current
# function" which gives answers like
# https://stackoverflow.com/questions/5067604/determine-function-name-from-within-that-function
# involving the inspect module.
#
# However, the logging package can do this using the 'funcName' marker in the
# format string.
#

logger = logging.getLogger(__name__)
FORMAT = "[(%(levelname)s) (%(asctime)s) %(process)d:%(filename)s:%(lineno)3s - %(funcName)20s() ] %(message)s"
logging.basicConfig(format=FORMAT)
logger.setLevel(logging.DEBUG)

def phil():
    logger.debug("HELLO")

def paul():
    logger.debug("HELLO")

def main():
    phil()
    paul()

main()
