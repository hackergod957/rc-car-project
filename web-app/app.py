import os
import io
from flask import Flask, request, render_template, send_file
import matplotlib.pyplot as plt
import numpy as np

app = Flask(__name__)

# Route to display the map or plot
@app.route('/map', methods=['POST'])
def get_map():
    try:
        # Handle POST request with JSON data from NodeMCU
        data = request.get_json()
        print(f"Received data: {data}")  # Log the received data

        # Ensure 'distance' is present in the data
        if 'distance' not in data:
            return {"error": "Missing 'distance' in the request body"}, 400
        
        # Extract the distance value
        distance = data['distance']
        
        # Create a simple graph (polar plot) based on the distance
        fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
        
        # Polar plot (distance data from sensor)
        ax.set_theta_zero_location('N')  # Start at the North (0 degrees)
        ax.set_theta_direction(-1)  # Clockwise
        
        # Example: use distance as the radius, plotting at different angles
        angles = np.linspace(0, 2 * np.pi, 100)
        radii = np.full_like(angles, distance)

        ax.plot(angles, radii)

        ax.set_title(f"Distance: {distance} cm")

        # Save the plot to a BytesIO object
        img = io.BytesIO()
        fig.savefig(img, format='png')
        img.seek(0)  # Rewind the image

        # Return the plot image as a response
        return send_file(img, mimetype='image/png')

    except Exception as e:
        return {"error": str(e)}, 500

# Default route for testing or displaying HTML page
@app.route('/')
def index():
    return render_template('index.html')  # Ensure you have an index.html template

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
