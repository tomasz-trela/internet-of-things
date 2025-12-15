#!/usr/bin/env python3
import time
import smbus2
import bme280
from PIL import Image, ImageDraw, ImageFont
import lib.oled.SSD1331 as SSD1331  # Using the provided library [cite: 41]

# --- BME280 Configuration ---
PORT = 1
ADDRESS = 0x76 # Common address for BME280 (might be 0x77)
bus = smbus2.SMBus(PORT)

# --- Drawing Functions for Pictograms  ---
def draw_thermometer(draw, x, y, color):
    # Bulb
    draw.ellipse((x, y + 10, x + 8, y + 18), outline=color, fill=color)
    # Stem
    draw.rectangle((x + 2, y, x + 6, y + 12), outline=color, fill=color)

def draw_droplet(draw, x, y, color):
    # Polygon for top point
    draw.polygon([(x + 4, y), (x, y + 8), (x + 8, y + 8)], outline=color, fill=color)
    # Ellipse for bottom round part
    draw.pieslice((x, y + 4, x + 8, y + 12), 0, 360, outline=color, fill=color)

def main():
    # Initialize Display
    disp = SSD1331.SSD1331()
    disp.Init()
    disp.clear()

    # Load Fonts
    try:
        font_large = ImageFont.truetype('./lib/oled/Font.ttf', 14)
        font_small = ImageFont.truetype('./lib/oled/Font.ttf', 10)
    except IOError:
        font_large = ImageFont.load_default()
        font_small = ImageFont.load_default()

    print("Starting OLED Environment Monitor...")

    try:
        while True:
            # 1. Read REAL data from BME280 
            calibration_params = bme280.load_calibration_params(bus, ADDRESS)
            data = bme280.sample(bus, ADDRESS, calibration_params)
            
            temp = data.temperature
            hum = data.humidity
            pres = data.pressure

            # 2. Create blank image (RGB)
            image = Image.new("RGB", (disp.width, disp.height), "BLACK")
            draw = ImageDraw.Draw(image)

            # 3. Draw Interface
            # Temperature (Red)
            draw_thermometer(draw, 5, 5, "RED")
            draw.text((20, 5), f"{temp:.1f} C", font=font_large, fill="RED")

            # Humidity (Blue)
            draw_droplet(draw, 5, 25, "BLUE")
            draw.text((20, 25), f"{hum:.1f} %", font=font_large, fill="BLUE")

            # Pressure (White, smaller text)
            draw.text((5, 45), f"P: {pres:.1f} hPa", font=font_small, fill="WHITE")

            # 4. Push to Display [cite: 122]
            disp.ShowImage(image, 0, 0)

            time.sleep(1)

    except KeyboardInterrupt:
        print("\nExiting...")
        disp.clear()
        disp.reset()

if __name__ == "__main__":
    main()