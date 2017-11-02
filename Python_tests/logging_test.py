import logging

logging.basicConfig(filename = "./logging_test.log")
logger = logging.getLogger()
logger.level = 1
logger.info("logger.info() is used to write info messages")

def phil(x):
    logger.info("logger.info called in phil()")

phil(8)

