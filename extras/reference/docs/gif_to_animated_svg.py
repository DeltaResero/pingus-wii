#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
#
# Pingus - A free Lemmings clone
# Copyright (C) 2026 DeltaResero
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

"""
GIF to Animated SVG Converter

Converts animated GIF files to CSS-animated SVG files by using CSS keyframes.

Usage:
    python gif_to_svg.py input.gif [-o output.svg] [-d 0.08]

    # Batch convert all GIFs in current directory
    for gif in *.gif; do python gif_to_svg.py "$gif" -d 0.08; done

Requirements:
    - Python 3.6+
    - Pillow (PIL): Install with 'pip install Pillow' or 'sudo pacman -S python-pillow'
"""

import sys
import base64
import argparse
import importlib.util
from io import BytesIO
from pathlib import Path


def check_dependencies():
    """Check if required dependencies are installed."""
    # Use importlib to check for module existence without importing it
    if importlib.util.find_spec("PIL"):
        return True
    else:
        print("ERROR: Pillow (PIL) is not installed.", file=sys.stderr)
        print("\nInstall it with one of these commands:", file=sys.stderr)
        print("  pip install Pillow", file=sys.stderr)
        print("  sudo pacman -S python-pillow  # Arch Linux", file=sys.stderr)
        print("  sudo apt install python3-pil   # Debian/Ubuntu", file=sys.stderr)
        return False


def get_gif_metrics(img, delay_override=None):
    """Calculate frame count and total duration from the GIF."""
    # Count frames
    frame_count = 0
    try:
        while True:
            img.seek(frame_count)
            frame_count += 1
    except EOFError:
        pass

    if frame_count == 0:
        # We cannot print the filename here easily, so we raise an error
        raise ValueError("GIF has no frames")

    # Get delay from GIF or use override
    img.seek(0)
    if delay_override:
        frame_delay = delay_override
    else:
        frame_delay = img.info.get('duration', 100) / 1000.0  # Convert ms to seconds

    total_duration = frame_delay * frame_count
    return frame_count, frame_delay, total_duration


def generate_css(frame_count, total_duration):
    """Generate the CSS styles and keyframes for the animation."""
    svg_parts = []
    # Add CSS animation
    svg_parts.append('  <style>')
    svg_parts.append('    image {')
    svg_parts.append('      position: absolute;')
    svg_parts.append('      opacity: 0;')
    svg_parts.append('    }')

    # Create keyframes for each frame
    for i in range(frame_count):
        start_pct = (i / frame_count) * 100
        end_pct = ((i + 1) / frame_count) * 100

        svg_parts.append(f'    #frame{i} {{')
        svg_parts.append(f'      animation: show{i} {total_duration}s step-end infinite;')
        svg_parts.append('    }')

        svg_parts.append(f'    @keyframes show{i} {{')
        svg_parts.append(f'      {start_pct:.4f}% {{ opacity: 1; }}')
        svg_parts.append(f'      {end_pct:.4f}% {{ opacity: 0; }}')
        svg_parts.append('    }')

    svg_parts.append('  </style>')
    return svg_parts


def generate_encoded_frames(img, frame_count, width, height):
    """Generate the Base64 encoded image elements."""
    svg_parts = []
    # Embed each frame as base64-encoded PNG
    for i in range(frame_count):
        img.seek(i)

        buffer = BytesIO()
        frame = img.convert('RGBA')
        frame.save(buffer, format='PNG', optimize=True)

        png_b64 = base64.b64encode(buffer.getvalue()).decode('ascii')

        svg_parts.append(f'  <image id="frame{i}" x="0" y="0" '
                         f'width="{width}" height="{height}" '
                         f'xlink:href="data:image/png;base64,{png_b64}"/>')
    return svg_parts


def gif_to_animated_svg(gif_path, output_path=None, delay_override=None):
    """
    Convert an animated GIF to an SVG with CSS keyframe animation.

    Args:
        gif_path: Path to input GIF file
        output_path: Path to output SVG file (default: same name with .svg extension)
        delay_override: Override frame delay in seconds (default: use GIF timing)

    Returns:
        Path to created SVG file
    """
    from PIL import Image

    # Open the GIF
    try:
        img = Image.open(gif_path)
    except Exception as e:
        print(f"ERROR: Could not open '{gif_path}': {e}", file=sys.stderr)
        sys.exit(1)

    # Get dimensions
    width, height = img.size

    try:
        frame_count, frame_delay, total_duration = get_gif_metrics(img, delay_override)
    except ValueError as e:
        print(f"ERROR: '{gif_path}': {e}", file=sys.stderr)
        sys.exit(1)

    # Build SVG
    svg_parts = []
    svg_parts.append(f'<svg xmlns="http://www.w3.org/2000/svg" '
                     f'xmlns:xlink="http://www.w3.org/1999/xlink" '
                     f'width="{width}" height="{height}" '
                     f'viewBox="0 0 {width} {height}">')

    svg_parts.extend(generate_css(frame_count, total_duration))
    svg_parts.extend(generate_encoded_frames(img, frame_count, width, height))

    svg_parts.append('</svg>')

    # Determine output path
    if output_path is None:
        output_path = Path(gif_path).with_suffix('.svg')

    # Write SVG file
    try:
        with open(output_path, 'w') as f:
            f.write('\n'.join(svg_parts))
    except Exception as e:
        print(f"ERROR: Could not write '{output_path}': {e}", file=sys.stderr)
        sys.exit(1)

    print(f"✓ Created {output_path}")
    print(f"  ({frame_count} frames, {frame_delay:.2f}s delay, "
          f"{total_duration:.2f}s total duration)")

    return output_path


def main():
    parser = argparse.ArgumentParser(
        description='Convert animated GIF to CSS-animated SVG for GitHub',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  %(prog)s basher.gif
  %(prog)s input.gif -o output.svg
  %(prog)s animation.gif -d 0.08

  # Batch convert all GIFs
  for gif in *.gif; do %(prog)s "$gif" -d 0.08; done
        """
    )

    parser.add_argument('input',
                        help='Input GIF file')
    parser.add_argument('-o', '--output',
                        help='Output SVG file (default: input name with .svg extension)')
    parser.add_argument('-d', '--delay',
                        type=float,
                        help='Override frame delay in seconds (default: use GIF timing)')

    args = parser.parse_args()

    # Check dependencies
    if not check_dependencies():
        sys.exit(1)

    # Convert GIF to SVG
    gif_to_animated_svg(args.input, args.output, args.delay)


if __name__ == '__main__':
    main()

# EOF
