import engel_lyndon.TrafficSim

"""
name: main

Description:
This is the main function it handles the menu output and user input for the program.

param:
"""

def main():
    ans = True
    """Intializes the road"""
    block_list = engel_lyndon.TrafficSim.Street(engel_lyndon.TrafficSim.Block(.5, 30, 1000))
    block_list.blockList[0].light.on = True

    """loop through menu"""
    while ans:
        print("""0) show road\n1) update\n2) add car\n3) add block\n4) show cars\n5) quit""")
        ans = input("\nChoice: ")
        if ans == "0":
            engel_lyndon.TrafficSim.show_road(block_list)
        elif ans == "1":
            engel_lyndon.TrafficSim.update_roads(block_list)
            engel_lyndon.TrafficSim.show_road(block_list)
        elif ans == "2":
            engel_lyndon.TrafficSim.add_car(block_list)
        elif ans == "3":
            engel_lyndon.TrafficSim.add_block(block_list)
            #show_road(block_list)
        elif ans == "4":
            engel_lyndon.TrafficSim.show_car(block_list)
        elif ans == "5":
            ans = None
        else:
            print("Invalid Option")


# END main

if __name__ == '__main__':
    main()
