import sys
from PIL import Image
import numpy as np

def load_image_and_convert_to_hex_array(file_path):
    
    # Load image
    img = Image.open(file_path)
    img = img.resize((260, 240))  # Resize, if needed
    img = img.convert('RGB')		  # Convert to RGB encoding, if needed

    # Convert each pixel to 16-bit value
    hex_array = []
    for y in range(img.height):
        for x in range(img.width):            
            r, g, b  = img.getpixel((x, y))          																			# Sample the pixel
            hex_value = rgb24_to_rgb16(r, g, b)																						# Convert it to 16-bit 5-6-5
            formatted_hex = "0X{:02X},0X{:02X}".format(hex_value & 0xFF, hex_value >> 8)  # Format as 0XFF,0XFF
            hex_array.append(formatted_hex)																								# Add it into our array
    return hex_array

# Color conversion routine    
def rgb24_to_rgb16(r, g, b):
    r_16 = int((r / 255) * 31) & 0x1F
    g_16 = int((g / 255) * 63) & 0x3F
    b_16 = int((b / 255) * 31) & 0x1F
    return (r_16 << 11) | (g_16 << 5) | b_16

# Main program.  Receive the file via the first argument    
source = sys.argv[1]

# Get the bytes
hex_array = load_image_and_convert_to_hex_array(source)
hex_string = ','.join(hex_array)

# Write to file, 15 values per line
with open("out.txt", 'w') as file:
    line = ''
    n=0
    for hex_val in hex_string.split(','):
        if(n % 15 == 0):
            file.write("\n")
        file.write(hex_val + ",")
        n+=1
