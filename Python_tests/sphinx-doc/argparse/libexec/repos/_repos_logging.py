
import logging
import sys
import os

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


logger = logging.getLogger(os.path.basename(sys.argv[0]))
logger.setLevel(logging.INFO)

log_colors = {
        logging.DEBUG: "\033[36m",
        logging.INFO: "\033[35m",
        logging.WARNING: "\033[33m",
        logging.ERROR: "\033[31m",
        logging.CRITICAL: "\033[37;41m"
}

# Create a formatter
fmt='[{name} {levelname}] {message}'
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
logger.addHandler(h)


