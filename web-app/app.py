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
    # Get real data (distance from one ultrasonic sensor) from POST request
    data = request.json
    distance1 = data['distance1']  # Distance from the single sensor
    
    # Fixed car position (in the center of the map)
    map_size = 500
    car_pos = (map_size // 2, map_size - 30)
    
    # Sensor facing forward (angle = 0 degrees)
    angle1 = 0  
    
    # Calculate obstacle position based on the sensor reading
    def calculate_obstacle_position(distance, angle):
        x = int(car_pos[0] + distance * math.cos(math.radians(angle)))
        y = int(car_pos[1] - distance * math.sin(math.radians(angle)))
        return x, y
    
    # Get the obstacle position
    obstacle1_pos = calculate_obstacle_position(distance1, angle1)
    
    # Create a blank white map
    img = np.ones((map_size, map_size, 3), dtype=np.uint8) * 255
    
    # Draw the car (blue dot)
    cv2.circle(img, car_pos, 5, (255, 0, 0), -1)  # Blue dot for car
    
    # Draw the single obstacle (red dot)
    cv2.circle(img, obstacle1_pos, 5, (0, 0, 255), -1)  # Red dot for obstacle
    
    # Save the image to a temporary file
    cv2.imwrite("map.jpg", img)
    
    # Return the image as a response
    return send_file("map.jpg", mimetype='image/jpeg')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
