# Engine Technical Notes

## Rendering Layers (Z-Position)

The engine uses Z-positions to determine drawing order (painters algorithm).

* **-100**: Background objects (drawn first, behind everything).
* **0**: Ground (The main playfield).
* **75**: Pingus (The characters).
* **100**: Foreground objects (Liquids, weather, etc).

## Physics Logic

### Wall Detection

Pingus can step over obstacles up to 2 pixels high. Obstacles 3 pixels or higher
act as a wall and cause them to reverse direction.

## Font Generation

The game fonts were originally generated using `fontgen`.

### Tools

* **fontgen**: https://github.com/Grumbel/fontgen

### Source Fonts

* **Pingus Main Font**: Based on `ExpletiveDeletedEnhanced.ttf`

### Chalk Effect (GIMP Workflow)

The "Chalk" style fonts require manual post-processing after generation to
achieve their look. The original workflow using GIMP on the generated `.pgm`
(Portable Gray Map) file is:

1. Add Alpha channel.
2. Select white, delete.
3. Invert selection, delete.
4. Fill with white.
5. Apply Blur.
6. Save as PNG.

*Note: The current assets have been optimized and repacked to contain only ASCII
characters to reduce texture size and memory usage.*
