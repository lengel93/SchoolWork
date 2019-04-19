import abc  # Python's built-in abstract class library
"""
name: Traffic Jam
author: Lyndon Engel
class: CSC 461 Programming Languages
Language\Compiler: Python 3.7

Description:
This file holds the driving style strategy pattern
Bugs:

"""

"""
name: driveStrategy

Description:
    Interface for drive style

param:
    object - what drivestyle is chosen
"""
class driveStrategy(object):
    """You do not need to know about metaclasses.
    Just know that this is how you define abstract
    classes in Python."""
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def driveStyle(self, speed_limit):
        """Required Method"""

"""
name: SlowStrategy

Description:
    set driver speed to 5 below speedlimit

param:
    object - driveStratefy object
"""
class SlowStrategy(driveStrategy):
    def driveStyle(self, speed_limit):
        return int(speed_limit) - 5

"""
name: NormalStrategy

Description:
    set driver speed to speedlimit

param:
    object - driveStrategy object
"""
class NormalStrategy(driveStrategy):
    def driveStyle(self, speed_limit):
        return int(speed_limit)

"""
name: FastStrategy

Description:
    set driver speed to 5 above speedlimit

param:
    object - driveStratefy object
"""
class FastStrategy(driveStrategy):
    def driveStyle(self, speed_limit):
        return int(speed_limit) + 5
