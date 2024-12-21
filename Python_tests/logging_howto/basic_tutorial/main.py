import logging
import argparse
import mylib

def main():
    p = argparse.ArgumentParser()
    p.add_argument("--log-level", choices=["debug", "info", "warning", "error"], default='warning')
    args = p.parse_args()
    fmt = "[%(asctime)s %(levelname)-7s] %(message)s'"
    datefmt = '%Y-%m-%d:%H:%M:%S'
    logging.basicConfig(format=fmt, datefmt=datefmt, level=getattr(logging,args.log_level.upper()))

    mylib.do_something()

    logging.debug('This message should go to the log file')
    logging.info('So should this')
    logging.warning('And this, too')

if __name__ == '__main__':
    main()




