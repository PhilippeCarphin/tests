import logging
import sys

#
# Change the name strings to colored ones so that the name (%(levelname) or
# {levelname} in the format string puts colored words
#
if sys.stderr.isatty():
    logging.addLevelName( logging.WARNING, "\033[0;33m%s\033[1;0m" % logging.getLevelName(logging.WARNING))
    logging.addLevelName( logging.ERROR,   "\033[0;31m%s\033[1;0m" % logging.getLevelName(logging.ERROR))
    logging.addLevelName( logging.INFO,    "\033[0;35m%s\033[1;0m" % logging.getLevelName(logging.INFO))
    logging.addLevelName( logging.DEBUG,   "\033[1;00m%s\033[1;0m" % logging.getLevelName(logging.DEBUG))

logger = logging.getLogger(__name__)
FORMAT = "[{levelname:20} ({asctime}) {process}:{filename}:{lineno} - {funcName}()] {message}"
logging.basicConfig(format=FORMAT, style='{')
logger.setLevel(logging.DEBUG)

def phil():
    logger.error("This is an error")
    logger.info("This is an info")

def paul():
    logger.debug("This is a debug msg")
    logger.warn("This is a warning")

def main():
    phil()
    paul()

main()
