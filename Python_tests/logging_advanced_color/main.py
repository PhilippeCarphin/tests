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
    f = logging.Formatter(fmt=fmt, datefmt=datefmt, style='{')

    # Create a handler
    h = ColoredLevelNamesHandler(check_tty=False)
    h.setFormatter(f)
    h.setColors(log_colors)

    # Use our handler
    root.addHandler(h)

    # Take it for a spin
    logging.critical('this is a critical message')
    logging.error('this is an error message')
    logging.warning('this is a warning')
    logging.info('this is an info message')
    logging.debug('this is a debug message')

class ColoredLevelNamesHandler(logging.StreamHandler):
    def __init__(self, check_tty=True, *args, **kwargs):
        self.output_color = True
        self.colormap = {}
        super().__init__(*args, **kwargs)
        if check_tty:
            self.output_color = self.stream.isatty()

    def check_output_is_tty(self):
        return self.stream.isatty()

    def setColors(self, d: dict):
        self.colormap.update(d)

    def emit(self, record):
        message = self.format(record)
        self.stream.write(message + '\n')
        self.flush()

    def format(self, record: logging.LogRecord):
        colorlevelname = None
        if self.output_color and record.levelno in self.colormap:
            levelname = record.levelname
            levelcolor = self.colormap[record.levelno]
            coloredlevelname = levelcolor + record.levelname + '\033[0m'
            record.levelname = coloredlevelname

        message = self.formatter.format(record) \
                  if self.formatter \
                  else super().format(record)

        if colorlevelname:
            record.levelname = levelname

        return message


if __name__ == '__main__':
    main()
