#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Chinese font conversion script
Convert font data from chinese.txt to C struct array format
"""

import re
import os

def parse_chinese_txt(file_path):
    """
    Parse chinese.txt file, extract character names and font data
    """
    characters = []
    with open(file_path, 'r', encoding='gb2312') as f:
        content = f.read()

    # Match pattern: hex data followed by /*"character",index*/
    # The format is: hex_data/*"char_name",index*/
    pattern = r'((?:0x[0-9A-Fa-f]{2},?\s*)+)/\*"([^"]+)",\d+\*/'

    matches = re.findall(pattern, content)

    for hex_text, char_name in matches:
        # Extract hex data
        hex_data = extract_hex_data(hex_text)
        if hex_data:
            characters.append({
                'name': char_name.strip(),
                'data': hex_data
            })

    return characters

def extract_hex_data(data_text):
    """
    Extract hex data from text
    """
    # Match all hex values (starting with 0x)
    hex_pattern = r'0x[0-9A-Fa-f]{2}'
    hex_matches = re.findall(hex_pattern, data_text)

    return hex_matches

def format_hex_data(hex_data, bytes_per_line=16):
    """
    Format hex data for multi-line display
    """
    lines = []
    for i in range(0, len(hex_data), bytes_per_line):
        line_data = hex_data[i:i + bytes_per_line]
        line = '            ' + ','.join(line_data) + ','
        lines.append(line)

    return lines

def generate_c_struct_array(characters, output_file):
    """
    Generate C struct array code
    """
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write('static const font_chinese_t chinese_model[] =\n')
        f.write('{\n')

        for i, char in enumerate(characters):
            f.write('    {\n')
            f.write(f'        .name = "{char["name"]}",\n')
            f.write('        .model = (const uint8_t[]) {\n')

            # Format hex data
            formatted_lines = format_hex_data(char['data'])
            for line in formatted_lines:
                f.write(line + '\n')

            f.write('        }\n')
            f.write('    },\n')

        # Add empty struct as end marker
        f.write('    {}\n')
        f.write('};\n\n')

def main():
    """
    Main function
    """
    # Input file path
    input_file = 'chinese.txt'
    # Output file path
    output_file = 'chinese_model.txt'

    # Check if input file exists
    if not os.path.exists(input_file):
        print(f"Error: Input file {input_file} not found")
        return

    try:
        # Parse input file
        print(f"Parsing file {input_file}...")
        characters = parse_chinese_txt(input_file)
        print(f"Successfully parsed {len(characters)} characters")

        # Generate output file
        print(f"Generating output file {output_file}...")
        generate_c_struct_array(characters, output_file)
        print(f"Successfully generated output file {output_file}")

        # Display parsed characters
        print("\nParsed characters:")
        for i, char in enumerate(characters):
            print(f"  {i}: {char['name']} ({len(char['data'])} bytes)")

    except Exception as e:
        print(f"Error during processing: {e}")

if __name__ == "__main__":
    main()
