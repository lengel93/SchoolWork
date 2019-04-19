from engel_lyndon.driverType import SlowStrategy
from engel_lyndon.driverType import NormalStrategy
from engel_lyndon.driverType import FastStrategy

"""
name: Traffic Jam
author: Lyndon Engel
class: CSC 461 Programming Languages
Language\Compiler: Python 3.7

Description:
This file holds all the logic for the program.
Bugs:

"""

"""initialize slow, normal, and fast driving styles"""
slow_driver = SlowStrategy();
normal_driver = NormalStrategy();
fast_driver = FastStrategy();
car_id = 1  # global car id so it can be incremented

"""
name: update_roads

Description:
    This function takes in the block list and then updates the distances
    traveled for every car and also stop light in the list. It then checks
    if any cars can move to a new block.

param:
    blockList - list of all blocks
"""


def update_roads(blockList):
    temp = blockList
    block_index = 0

    for i in temp:
        """Updates the distance of all cars in block and light"""
        i.update()


    for i in temp:

        """handles uplist removal"""

        if temp.blockList[block_index].light.on:
            """Checking if any cars in uplist can go through light"""
            for car in i.upList:
                if car.location > i.length or car.wait_light:
                    if block_index == 0:
                        i.upList.remove(car)
                    else:
                        car.location = 0
                        car.wait_light = False
                        temp.blockList[block_index - 1].upList.append(car)
                        i.upList.remove(car)
                    break
        fix_distance(i.upList, i.length)

        """handles downlist removal"""
        try:
            if temp.blockList[block_index + 1].light.on:
                """Checking if any cars in downlist can go through light"""
                for car in i.downList:
                    if car.location > i.length or car.wait_light:
                        car.location = 0;
                        car.wait_light = False
                        temp.blockList[block_index + 1].downList.append(car)
                        i.downList.remove(car)
                        break
        except IndexError:
            """Checking if any cars in downlist can go through light"""
            for car in i.downList:
                if car.location > i.length or car.wait_light:
                    car.wait_light = False
                    i.downList.remove(car)
                    break
        fix_distance(i.downList, i.length)

        block_index += 1


def fix_distance(current_list, length):
    for car in current_list:
        if car.location > length:
            car.location = length
            car.wait_light = True


"""
name: show_road

Description:
    This function takes in the blockList and prints out the current state
    of each block. Starting with the stop light and time until it turns. Then
    number of cars in the up and down lane.

param:
    blockList - list of all blocks
"""


def show_road(blockList):
    temp = blockList
    index = 0

    print("Entry\Exit")

    """iterator through blocklist"""
    for i in temp:
        if index > 0:
            if i.light.on:
                print("On " + str(i.light.time_until_turn) + "")
            else:
                print("Off " + str(i.light.time_until_turn) + "")

        print("Up: " + str(len(i.upList)) + " Down: " + str(len(i.downList)) + "")
        index += 1

    print("Entry\Exit")


"""
name: show_car

Description:
    This function takes in the block list and then prints out the cars in each
    block followed by their current distanct in the block.

param:
    blockList - list of all blocks
"""


def show_car(blockList):
    temp = blockList
    i = 0

    for v in temp:
        print("Block " + str(i) + "-------------------")
        v.display_cars()
        i += 1


"""
name: add_block

Description:
    This function takes in the block list and then appends a new block to it
    based on the users specificatons.

param:
    blockList - list of all blocks
"""


def add_block(blockList):
    light = input("Length of cycle: ")
    try:
        cycle = float(light)*60
        if float(light) < 1:
            print("Invalid option\n")
            return
        if (cycle % 30) != 0:
            print("Invalid option\n")
            return
    except ValueError:
        print("Invalid option\n")
        return

    length = input("Length of block in miles: ")
    try:
        if float(length) < .5:
            print("Invalid option\n")
            return
    except ValueError:
        print("Invalid option\n")
        return

    speed = input("Speed limit of block in mph: ")
    try:
        if int(speed) < 1:
            print("Invalid option\n")
            return
    except ValueError:
        print("Invalid option\n")
        return

    blockList.blockList.append(Block(length, speed, light))


"""
name: add_car

Description:
    This function takes in the block list and then appends a new car based
    on user specidication to either the top of the list or bottom of the list.

param:
    blockList - list of all blocks
"""


def add_car(blockList):
    """Initializes global carID, gets user input, and number of blocks in list"""
    global car_id
    location = input("Which end: 0) top 1) bottom: ")
    driver_type = input("Which type: 0) slow 1) norm 2) fast: ")

    if driver_type != 0 or driver_type != 1 or driver_type != 2:
        print("Invalid option, using normal driver")
        driver_type = '1'

    size = len(blockList.blockList)

    """sets driver type"""
    if driver_type == '0':
        driver_type = slow_driver
    elif driver_type == '1':
        driver_type = normal_driver
    elif driver_type == '2':
        driver_type = fast_driver

    """appends car at bottom or top of list depending on user input"""
    if location == '0':
        current_block = blockList.blockList[0]
        current_block.downList.append(Car(car_id, 0, driver_type))
    elif location == '1':
        current_block = blockList.blockList[size - 1]
        current_block.upList.append(Car(car_id, 0, driver_type))
    car_id += 1


"""
name: Block

Description:
    This class holds all the information about a block. Blocks contain a
    length in miles, speed in mph, stoplight, and a uplist/downlist. Its
    personal functions let you display cars in the block and update the block.

param:
"""


class Block:
    """
    name: __init__

    Description:
        Initializes the block

    param:
        self - block
        length - how long the block is in .5 mile increments
        speed - speedlimit for block
        light - how often the stop light changes
    """

    def __init__(self, length, speed, light):
        self.length = float(length)
        self.speed = int(speed)
        self.light = Light(light, False)
        self.upList = []
        self.downList = []

    """
    name: display_cars

    Description:
        This function goes through the uplist and downlist printing off all
        the cars in each list along with their current location in the block.

    param:
        self - block
    """

    def display_cars(self):
        print("Up----")
        for i in self.upList:
            print(str(i.id) + ": " + str(i.location))
            print("...")

        print("Down---")
        for i in self.downList:
            print(str(i.id) + ": " + str(i.location))
            print("...")

    """
    name: update

    Description:
        This function starts by updating light status and then goes through the
        uplist and downlist updating every cars location.

    param:
        self - block
    """

    def update(self):
        self.light.update()

        """updating position of each car in uplist"""
        for i in self.upList:
            driver_speed = i.drive_strategy.driveStyle(self.speed)
            updated_location = (driver_speed / 3600) * 30
            updated_location += i.location

            if i.location == self.length:
                i.wait_light = True
            elif updated_location > self.length:
                i.location = updated_location
            else:
                i.location = updated_location

        """updating position of each car in downlist"""
        for i in self.downList:
            driver_speed = i.drive_strategy.driveStyle(self.speed)
            updated_location = (driver_speed / 3600) * 30
            updated_location += i.location

            if i.location == self.length:
                i.wait_light = True
            elif updated_location > self.length:
                i.location = updated_location
            else:
                i.location = updated_location


"""
name: Car

Description:
    This class holds all the information about a car. Each car has an id
    starting at 1, a location, and a driving style

param:
"""


class Car:
    """
    name: __init__

    Description:
        Initializes car

    param:
        self - car
        id - identifies cars
        location - distance through block
        drive_strategy - fast, slow, normal
    """

    def __init__(self, id, location, drive_strategy):
        self.id = int(id)
        self.location = float(location)
        self.drive_strategy = drive_strategy
        self.wait_light = False

    """
    name: update

    Description:
        returns driver speed
    param:
    """

    def update(self):
        self.drive_strategy.driveStyle()


"""
name: Light

Description:
    This class holds all the information about a stop light. Each stop light
    has a cycletime, current status, and time until it turns. Also elapsed time.

param:
"""


class Light:
    """
    name: __init__

    Description:
        initialize stop light

    param:
        self - Light
        cycleTime - Time it takes to swtich states
        on - boolean value of whether the light is on
    """

    def __init__(self, cycleTime, on):
        self.cycleTime = float(cycleTime)
        self.on = on
        self.time_until_turn = float(cycleTime)
        self.total_time = 0

    """
    name: update

    Description:
        Updates the light state depending on its cycle time and total time that
        has passed.

    param:
        self - light
    """

    def update(self):
        """increments total time by 30, turns cycle time into seconds"""
        self.total_time += 30
        turn_time = self.cycleTime * 60

        """checks if its time to switch light on or off"""
        if self.total_time == turn_time:
            if self.on:
                self.on = False
            else:
                self.on = True
            """reset total time"""
            self.total_time = 0

        """calculates time until state change in minutes"""
        self.time_until_turn = (turn_time - self.total_time) / 60


"""
name: Street

Description:
    This class holds information about a street. Which in this case is a list
    of blocks that creates the street.

param:
"""


class Street:
    blockList = []

    """
    name: __init__

    Description:
        Intalizes street with a block

    param:
        self - Street
        block - user created block they want to add to street
    """

    def __init__(self, block):
        self.blockList.append(block)

    """
    name: __iter__

    Description:
        iterator through blocklist

    param:
        self - Street
    """

    def __iter__(self):
        self.index = -1
        return self

    """
    name: __next__

    Description:
        returns block from block list until it reaches the end of the list.

    param:
        self - Street
    """

    def __next__(self):
        try:
            self.index += 1
            return self.blockList[self.index]
        except:
            raise StopIteration()
