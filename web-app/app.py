import math
import cv2
import numpy as np
from flask import Flask, render_template, request, send_file

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')  # Display the webpage

@app.route('/map', methods=['POST'])
def get_map():
    # Get real data (distances from 3 ultrasonic sensors) from POST request
    data = request.json
    distance1 = data['distance1']  # Distance from sensor 1
    distance2 = data['distance2']  # Distance from sensor 2
    distance3 = data['distance3']  # Distance from sensor 3
    
    # Fixed car position (in the center of the map)
    map_size = 500
    car_pos = (map_size // 2, map_size - 30)
    
    # Calculate obstacle positions based on distances
    # Assume that each sensor is placed at an angle relative to the car
    angle1 = 0  # Sensor 1 facing right (0 degrees)
    angle2 = 90  # Sensor 2 facing 120 degrees
    angle3 = 270  # Sensor 3 facing 240 degrees
    
    # Calculate obstacle positions
    def calculate_obstacle_position(distance, angle):
        x = int(car_pos[0] + distance * math.cos(math.radians(angle)))
        y = int(car_pos[1] - distance * math.sin(math.radians(angle)))
        return x, y
    
    # Get positions of obstacles from each sensor
    obstacle1_pos = calculate_obstacle_position(distance1, angle1)
    obstacle2_pos = calculate_obstacle_position(distance2, angle2)
    obstacle3_pos = calculate_obstacle_position(distance3, angle3)
    
    # Create a blank white map
    img = np.ones((map_size, map_size, 3), dtype=np.uint8) * 255
    
    # Draw the car (blue dot)
    cv2.circle(img, car_pos, 5, (255, 0, 0), -1)  # Blue dot for car
    
    # Draw obstacles (red dots)
    cv2.circle(img, obstacle1_pos, 5, (0, 0, 255), -1)  # Red dot for obstacle from sensor 1
    cv2.circle(img, obstacle2_pos, 5, (0, 0, 255), -1)  # Red dot for obstacle from sensor 2
    cv2.circle(img, obstacle3_pos, 5, (0, 0, 255), -1)  # Red dot for obstacle from sensor 3
    
    # Save the image to a temporary file
    cv2.imwrite("map.jpg", img)
    
    # Return the image as a response
    return send_file("map.jpg", mimetype='image/jpeg')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
