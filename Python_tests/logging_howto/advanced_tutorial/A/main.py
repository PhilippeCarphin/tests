import logging
import mylib
import argparse


# Create a formatter
fmt = "[%(asctime)s %(levelname)-7s] %(message)s'"
datefmt = '%Y-%m-%d:%H:%M:%S'
f = logging.Formatter(fmt=fmt, datefmt=datefmt, style='%')

# Create a handler with f as its formatter
file_handler = logging.FileHandler(filename='example.log')
file_handler.setFormatter(f)

# Create another handler
stream_handler = logging.StreamHandler()
stream_handler.setFormatter(f)

# Create a logger
logger = logging.getLogger(__name__)

# Add the handler
logger.addHandler(file_handler)
logger.addHandler(stream_handler)

def main():
    p = argparse.ArgumentParser()
    p.add_argument("--log-level", choices=["debug", "info", "warning", "error"], default='warning')
    args = p.parse_args()
    # logging.basicConfig(format=fmt, datefmt=datefmt, level=getattr(logging,args.log_level.upper()))
    logging.basicConfig()

    mylib.do_something()
    mylib.do_exception()

    logger.debug('This message should go to the log file')
    logger.info('So should this')
    logger.warning('And this, too')

if __name__ == '__main__':
    main()




