import random

def generate_temperature():
    return random.uniform(20, 40)  # Generate temperature between 20°C and 40°C

def generate_humidity():
    return random.uniform(40, 70)  # Generate humidity between 40% and 70%

def check_alarm(temperature, humidity):
    if temperature > 30:
        print("High temperature detected! Playing alarm sound.")
        # Add code to play the alarm sound here

    if humidity > 60:
        print("High humidity detected! Playing alarm sound.")
        # Add code to play the alarm sound here

# Generate temperature and humidity values
temperature = generate_temperature()
humidity = generate_humidity()

# Display the generated values
print("Temperature:", temperature, "°C")
print("Humidity:", humidity, "%")

# Check for alarm conditions
check_alarm(temperature, humidity)
