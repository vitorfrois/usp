import logging

class LoggerHelper:
    def get_logger(name: str):
        FORMAT = '|%(asctime)s| %(message)s'
        logging.basicConfig(level = logging.INFO, format=FORMAT)
        return logging.getLogger(name)