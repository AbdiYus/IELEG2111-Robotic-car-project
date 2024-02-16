import rospy
from std_msgs.msg import Int32
from evdev import InputDevice, categorize, ecodes

# Initialize the ROS node
rospy.init_node('keyboard_publisher')

# Create a publisher
pub = rospy.Publisher('keyboard', Int32, queue_size=10)

# Change /dev/input/event1 to the event file of your keyboard
dev = InputDevice('/dev/input/event3')  # /dev/input/event2 is the event file of my keyboard

# Map the arrow keys to specific int_32 values
key_map = {
    'KEY_RIGHT': 3,
    'KEY_LEFT': 4,
    'KEY_UP': 1,
    'KEY_DOWN': 2,
}

try:
    for event in dev.read_loop():
        if rospy.is_shutdown():
            print("ROS shutdown request received. Exiting program...")
            break

        if event.type == ecodes.EV_KEY:
            key_event = categorize(event)
            if key_event.keystate == key_event.key_down:
                # Convert the keycode to its corresponding int_32 value
                key_value = key_map.get(key_event.keycode, 0)
                # Publish the key value
                pub.publish(key_value)
            elif key_event.keystate == key_event.key_up:
                # Convert the keycode to its corresponding int_32 value
                key_value = key_map.get(key_event.keycode, 0)
                key_value = 0
                # Publish the key value
                pub.publish(key_value)
except KeyboardInterrupt:
    print("Keyboard interrupt received. Exiting program...")
