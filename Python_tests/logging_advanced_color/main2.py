import copy
import logging

#
# This demonstrates a simple handler that manipulates the record
# to add color to the level name.
#
# Notes:
# - In the format method, we change the records levelname to a string
#   containing ANSI codes.  Since this is a reference to a record that
#   can be passed to other handlers, we copy it so only that changing
#   the level name does not affect other code that receives it.

def main():
    root = logging.getLogger()
    root.setLevel(logging.DEBUG)


    log_colors = {
            logging.DEBUG: "\033[36m",
            logging.INFO: "\033[35m",
            logging.WARNING: "\033[33m",
            logging.ERROR: "\033[31m",
            logging.CRITICAL: "\033[37;41m"
    }

    # Create a formatter
    fmt='[{levelname} {asctime}] {message}'
    datefmt = '%Y-%m-%d:%H:%M:%S'

    # Create a handler
    h = logging.StreamHandler()
    if h.stream.isatty():
        f = ColoredLevelNamesFormatter(fmt=fmt, datefmt=datefmt, style='{')
        f.setColors(log_colors)
    else:
        f = logging.Formatter(fmt=fmt, datefmt=datefmt, style='{')
    h.setFormatter(f)

    # Use our handler
    root.addHandler(h)

    # Take it for a spin
    logging.critical('this is a critical message')
    logging.error('this is an error message')
    logging.warning('this is a warning')
    logging.info('this is an info message')
    logging.debug('this is a debug message')

class ColoredLevelNamesFormatter(logging.Formatter):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.colormap = {}
    def setColors(self, colormap):
        self.colormap = colormap
    def format(self, record):
        levelname = record.levelname
        record.levelname = self.colormap[record.levelno] \
                           + levelname + '\033[0m'
        message = super().format(record)
        record.levelname = levelname
        return message

if __name__ == '__main__':
    main()
